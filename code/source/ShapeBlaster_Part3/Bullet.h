#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class Bullet
: public Entity
{
public:
    Bullet(const tPoint2f& position, const tVector2f& velocity);

    void update();
};
