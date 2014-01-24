#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class GameRoot
:   public tSingleton<GameRoot>
{
protected:
    ParticleManager     mParticleManager;
    tDimension2f        mViewportSize;
    tSpriteBatch* mSpriteBatch;

    tAutosizeViewport*    mViewport;

protected:
    void DrawRightAlignedString(const std::string& str, int32_t y);

protected:
    GameRoot();

public:
    tDimension2f        getViewportSize();
    ParticleManager*    getParticleManager();

    void onInitView();
    void onRedrawView(float time);

    friend class tSingleton<GameRoot>;
};

