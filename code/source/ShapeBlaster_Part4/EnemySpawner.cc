#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

tVector2f EnemySpawner::GetSpawnPosition()
{
    tVector2f pos;
    do
    {
        pos = tVector2f(tMath::random() * GameRoot::getInstance()->getViewportSize().width,
                        tMath::random() * GameRoot::getInstance()->getViewportSize().height);
    }
    while (pos.distanceSquared(PlayerShip::getInstance()->getPosition()) < 250 * 250);

    return pos;
}

EnemySpawner::EnemySpawner()
:   mInverseSpawnChance(90),
    mInverseBlackHoleChance(600)
{

}

void EnemySpawner::update()
{
    if (!PlayerShip::getInstance()->getIsDead() && EntityManager::getInstance()->getCount() < 200)
    {
        if (int32_t(tMath::random() * mInverseSpawnChance) == 0)
        {
            EntityManager::getInstance()->add(Enemy::createSeeker(GetSpawnPosition()));
        }

        if (int32_t(tMath::random() * mInverseSpawnChance) == 0)
        {
            EntityManager::getInstance()->add(Enemy::createWanderer(GetSpawnPosition()));
        }

        if (EntityManager::getInstance()->getBlackHoleCount() < 2 && int32_t(tMath::random() * mInverseBlackHoleChance) == 0)
        {
            EntityManager::getInstance()->add(new BlackHole(GetSpawnPosition()));
        }
    }

    if (mInverseSpawnChance > 30)
    {
        mInverseSpawnChance -= 0.005f;
    }
}

void EnemySpawner::reset()
{
    mInverseSpawnChance = 90;
}

