#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class Bullet;
class Enemy;

class EntityManager
: public tSingleton<EntityManager>
{
protected:
    std::list<Entity*>      mEntities;
    std::list<Entity*>      mAddedEntities;
    std::list<Bullet*>      mBullets;
    bool mIsUpdating;

protected:
    EntityManager();

public:
    int getCount() const;

    void add(Entity* entity);
    void addEntity(Entity* entity);

    void update();
    void draw(tSpriteBatch* spriteBatch);

    bool isColliding(Entity* a, Entity* b);

    friend class tSingleton<EntityManager>;
};

