#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class tView
:   public tSingleton<tView>
{
protected:
    tDimension2f    mOriginalSize;
    tRectf          mViewportRect;
    tDimension2f    mLastSize;
    bool            mSetLastSize;

protected:
    tView();

public:
    ~tView() { }

    tDimension2f    getOriginalSize() const;
    tRectf          getViewportRect() const;
    void            setOriginalSize(const tDimension2f& newSize);
    void            setViewportRect(const tRectf& newRect);
    
//--
    void onResize(const tDimension2f& newSize);

    friend class tSingleton<tView>;
};

