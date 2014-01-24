#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class PlayerShip
:   public Entity,
    public tSingleton<PlayerShip>
{
protected:
    static const int kCooldownFrames;

    int mCooldowmRemaining;
    int mFramesUntilRespawn;

protected:
    PlayerShip();

public:
    void update();
    void draw(tSpriteBatch* spriteBatch);

    bool getIsDead();
    void kill();

    friend class tSingleton<PlayerShip>;
};

