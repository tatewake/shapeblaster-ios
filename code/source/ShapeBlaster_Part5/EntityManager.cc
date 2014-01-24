#include "Utility/package.h"

#include "Entity.h"
#include "Bullet.h"
#include "Enemy.h"
#include "BlackHole.h"

#include "EnemySpawner.h"
#include "PlayerShip.h"

#include "EntityManager.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

void EntityManager::KillPlayer()
{
    PlayerShip::getInstance()->kill();

    for (std::list<Enemy*>::iterator j = mEnemies.begin(); j != mEnemies.end(); j++)
    {
        (*j)->wasShot();
    }

    for (std::list<BlackHole*>::iterator j = mBlackHoles.begin(); j != mBlackHoles.end(); j++)
    {
        (*j)->kill();
    }

    EnemySpawner::getInstance()->reset();
}

EntityManager::EntityManager()
: mIsUpdating(false)
{

}

int EntityManager::getCount() const
{
    return (int)mEntities.size();
}

int EntityManager::getBlackHoleCount() const
{
    return (int)mBlackHoles.size();
}

std::list<BlackHole*> EntityManager::getBlackHoles() const
{
    return mBlackHoles;
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
        case Entity::kEnemy:        mEnemies.push_back((Enemy*)entity); break;
        case Entity::kBlackHole:    mBlackHoles.push_back((BlackHole*)entity); break;

        default: break;
    }
}

void EntityManager::update()
{
    mIsUpdating = true;

    handleCollisions();

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

    for(std::list<Enemy*>::iterator iter = mEnemies.begin(); iter != mEnemies.end(); iter++)
    {
        if ((*iter)->isExpired())
        {
            delete *iter;
            *iter = NULL;
        }
    }
    mEnemies.remove(NULL);

    for(std::list<BlackHole*>::iterator iter = mBlackHoles.begin(); iter != mBlackHoles.end(); iter++)
    {
        if ((*iter)->isExpired())
        {
            delete *iter;
            *iter = NULL;
        }
    }
    mBlackHoles.remove(NULL);
}

void EntityManager::handleCollisions()
{
    for (std::list<Enemy*>::iterator i = mEnemies.begin(); i != mEnemies.end(); i++)
    {
        for (std::list<Enemy*>::iterator j = mEnemies.begin(); j != mEnemies.end(); j++)
        {
            if (isColliding(*i, *j))
            {
                (*i)->handleCollision(*j);
                (*j)->handleCollision(*i);
            }
        }
    }

    // handle collisions between bullets and enemies
    for (std::list<Enemy*>::iterator i = mEnemies.begin(); i != mEnemies.end(); i++)
    {
        for (std::list<Bullet*>::iterator j = mBullets.begin(); j != mBullets.end(); j++)
        {
            if (isColliding(*i, *j))
            {
                (*i)->wasShot();
                (*j)->setExpired();
            }
        }
    }

    // handle collisions between the player and enemies
    for (std::list<Enemy*>::iterator i = mEnemies.begin(); i != mEnemies.end(); i++)
    {
        if ((*i)->getIsActive() && isColliding(PlayerShip::getInstance(), *i))
        {
            KillPlayer();
            break;
        }
    }

    // handle collisions with black holes
    for (std::list<BlackHole*>::iterator i = mBlackHoles.begin(); i != mBlackHoles.end(); i++)
    {
        for (std::list<Enemy*>::iterator j = mEnemies.begin(); j != mEnemies.end(); j++)
        {
            if ((*j)->getIsActive() && isColliding(*i, *j))
            {
                (*j)->wasShot();
            }
        }

        for (std::list<Bullet*>::iterator j = mBullets.begin(); j != mBullets.end(); j++)
        {
            if (isColliding(*i, *j))
            {
                (*j)->setExpired();
                (*i)->wasShot();
            }
        }

        if (isColliding(PlayerShip::getInstance(), *i))
        {
            KillPlayer();
            break;
        }
    }
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

std::list<Entity*> EntityManager::getNearbyEntities(const tPoint2f& pos, float radius)
{
    std::list<Entity*> result;
    for(std::list<Entity*>::iterator iter = mEntities.begin(); iter != mEntities.end(); iter++)
    {
        if (*iter)
        {
            if (pos.distanceSquared((*iter)->getPosition()) < radius * radius)
            {
                result.push_back(*iter);
            }
        }
    }

    return result;
}

