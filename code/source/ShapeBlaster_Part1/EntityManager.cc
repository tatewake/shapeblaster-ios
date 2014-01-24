#include "Utility/package.h"

#include "Entity.h"
#include "Bullet.h"

#include "PlayerShip.h"

#include "EntityManager.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

EntityManager::EntityManager()
: mIsUpdating(false)
{

}

int EntityManager::getCount() const
{
    return (int)mEntities.size();
}

void EntityManager::add(Entity* entity)
{
    if (!mIsUpdating)
    {
        addEntity(entity);
    }
    else
    {
        mAddedEntities.push_back(entity);
    }
}

void EntityManager::addEntity(Entity* entity)
{
    mEntities.push_back(entity);

    switch (entity->getKind())
    {
        case Entity::kBullet:       mBullets.push_back((Bullet*)entity); break;

        default: break;
    }
}

void EntityManager::update()
{
    mIsUpdating = true;

    for(std::list<Entity*>::iterator iter = mEntities.begin(); iter != mEntities.end(); iter++)
    {
        (*iter)->update();
        if ((*iter)->isExpired())
        {
            *iter = NULL;
        }
    }

    mIsUpdating = false;

    for(std::list<Entity*>::iterator iter = mAddedEntities.begin(); iter != mAddedEntities.end(); iter++)
    {
        addEntity(*iter);
    }

    mAddedEntities.clear();

    mEntities.remove(NULL);

    for(std::list<Bullet*>::iterator iter = mBullets.begin(); iter != mBullets.end(); iter++)
    {
        if ((*iter)->isExpired())
        {
            delete *iter;
            *iter = NULL;
        }
    }
    mBullets.remove(NULL);
}

bool EntityManager::isColliding(Entity* a, Entity* b)
{
    float radius = a->getRadius() + b->getRadius();
    return !a->isExpired() && !b->isExpired() && a->getPosition().distanceSquared(b->getPosition()) < radius * radius;
}

void EntityManager::draw(tSpriteBatch* spriteBatch)
{
    for(std::list<Entity*>::iterator iter = mEntities.begin(); iter != mEntities.end(); iter++)
    {
        (*iter)->draw(spriteBatch);
    }
}

