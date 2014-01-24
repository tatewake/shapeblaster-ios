#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class GameRoot
:   public tSingleton<GameRoot>
{
protected:
    tDimension2f        mViewportSize;
    tSpriteBatch* mSpriteBatch;

    tAutosizeViewport*    mViewport;

protected:
    GameRoot();

public:
    tDimension2f        getViewportSize();

    void onInitView();
    void onRedrawView(float time);

    friend class tSingleton<GameRoot>;
};

