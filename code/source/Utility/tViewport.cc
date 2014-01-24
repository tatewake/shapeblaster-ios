#include "Utility/package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

tView::tView()
:   mOriginalSize(1,1),
    mViewportRect(0,0,1,1),
    mLastSize(1,1),
    mSetLastSize(false)
{
}

tDimension2f    tView::getOriginalSize() const
{
    return mOriginalSize;
}

tRectf  tView::getViewportRect() const
{
    return mViewportRect;
}

void            tView::setOriginalSize(const tDimension2f& newSize)
{
    mOriginalSize = newSize;
}

void            tView::setViewportRect(const tRectf& newRect)
{
    mViewportRect = newRect;
}

void tView::onResize(const tDimension2f& newSize)
{
    mSetLastSize = true;
    mLastSize = newSize;
}
