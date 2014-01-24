#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class EnemySpawner
: public tSingleton<EnemySpawner>
{
protected:
    float mInverseSpawnChance;

protected:
    tVector2f GetSpawnPosition();

protected:
    EnemySpawner();

public:
    void update();
    void reset();

    friend class tSingleton<EnemySpawner>;
};

