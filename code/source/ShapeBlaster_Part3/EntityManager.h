#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class Bullet;
class Enemy;
class BlackHole;

class EntityManager
: public tSingleton<EntityManager>
{
protected:
    std::list<Entity*>      mEntities;
    std::list<Enemy*>       mEnemies;
    std::list<Entity*>      mAddedEntities;
    std::list<Bullet*>      mBullets;
    std::list<BlackHole*>   mBlackHoles;
    bool mIsUpdating;

protected:
    void KillPlayer();

protected:
    EntityManager();

public:
    int getCount() const;
    int getBlackHoleCount() const;

    std::list<BlackHole*>   getBlackHoles() const;

    void add(Entity* entity);
    void addEntity(Entity* entity);

    void update();
    void draw(tSpriteBatch* spriteBatch);

    void handleCollisions();
    bool isColliding(Entity* a, Entity* b);

    std::list<Entity*> getNearbyEntities(const tPoint2f& pos, float radius);

    friend class tSingleton<EntityManager>;
};

