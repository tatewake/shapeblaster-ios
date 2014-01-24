#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class tAutosizeViewport
{
protected:
    tDimension2f    mOriginalSize;
    tDimension2f    mViewSize;
    float           mWantedAspectRatio;
    bool            mIsOrientationPortrait;
    bool            mDirty;

protected:
    tRectf  CalculateViewPortRect() const;

public:
    tAutosizeViewport(const tDimension2f& newViewSize);

    tDimension2f getSize() const;
    
    void run();

    void onResize(const tDimension2f& newSize);
    void onRotate(tOrientationType& msg);
};

