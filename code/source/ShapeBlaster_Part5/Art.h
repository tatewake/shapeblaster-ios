#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class Art
: public tSingleton<Art>
{
protected:
    tTexture* mPlayer;
    tTexture* mSeeker;
    tTexture* mWanderer;
    tTexture* mBullet;
    tTexture* mPointer;
    tTexture* mBlackHole;
    tTexture* mFontTexture;
    tTexture* mLineParticle;
    tTexture* mGlow;
    tTexture* mPixel;

    tTexture* mVPadBottom;
    tTexture* mVPadTop;

protected:
    Art();

public:
    tTexture* getPlayer() const;
    tTexture* getSeeker() const;
    tTexture* getWanderer() const;
    tTexture* getBullet() const;
    tTexture* getPointer() const;
    tTexture* getBlackHole() const;
    tTexture* getLineParticle() const;
    tTexture* getGlow() const;
    tTexture* getPixel() const;

    tTexture* getVPadBottom() const;
    tTexture* getVPadTop() const;

    tSpriteFont getFont() const;

    friend class tSingleton<Art>;
};

