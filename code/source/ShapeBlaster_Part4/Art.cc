#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

Art::Art()
{
    mPlayer         = new tTexture(tSurface("player.png"));
    mSeeker         = new tTexture(tSurface("seeker.png"));
    mWanderer       = new tTexture(tSurface("wanderer.png"));
    mBullet         = new tTexture(tSurface("bullet.png"));
    mPointer        = new tTexture(tSurface("pointer.png"));
    mBlackHole      = new tTexture(tSurface("blackhole.png"));

    mLineParticle   = new tTexture(tSurface("laser.png"));
    mGlow           = new tTexture(tSurface("glow.png"));

    mFontTexture    = new tTexture(tSurface("font.png"));

    mVPadTop        = new tTexture(tSurface("vpad_top.png"));
    mVPadBottom     = new tTexture(tSurface("vpad_bot.png"));
}

tTexture* Art::getPlayer() const
{
    return mPlayer;
}

tTexture* Art::getSeeker() const
{
    return mSeeker;
}

tTexture* Art::getWanderer() const
{
    return mWanderer;
}

tTexture* Art::getBullet() const
{
    return mBullet;
}

tTexture* Art::getPointer() const
{
    return mPointer;
}

tTexture* Art::getBlackHole() const
{
    return mBlackHole;
}

tTexture* Art::getLineParticle() const
{
    return mLineParticle;
}

tTexture* Art::getGlow() const
{
    return mGlow;
}

tTexture* Art::getVPadBottom() const
{
    return mVPadBottom;
}

tTexture* Art::getVPadTop() const
{
    return mVPadTop;
}

tSpriteFont Art::getFont() const
{
    return tSpriteFont(mFontTexture, tTextSheet(tRectf(   0,   0, 256,  36), tDimension2f(   8,  12), tDimension2f(6, 10), ' ', '~'));
}

