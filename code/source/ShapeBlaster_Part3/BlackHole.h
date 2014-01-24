#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class BlackHole
: public Entity
{
protected:
    int mHitPoints;

public:
    BlackHole(const tVector2f& position);

    void update();
    void draw(tSpriteBatch* spriteBatch);

    void wasShot();
    void kill();
};

