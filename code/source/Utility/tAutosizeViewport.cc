#include "Utility/package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

tAutosizeViewport* gAutosizeViewport;

tRectf tAutosizeViewport::CalculateViewPortRect() const
{
    tDimension2f calculatedSize;
    tPoint2f midPoint;

    if ((float)mViewSize.width / (float)mViewSize.height < mWantedAspectRatio)
    {
        calculatedSize.width   = mViewSize.width;
        calculatedSize.height  = (int32_t)((float)mViewSize.width / mWantedAspectRatio);
    }
    else
    {
        calculatedSize.width   = (int32_t)((float)mViewSize.height * mWantedAspectRatio);
        calculatedSize.height  = mViewSize.height;
    }

    midPoint.x = (mViewSize.width - calculatedSize.width) / 2;
    midPoint.y = (mViewSize.height - calculatedSize.height) / 2;

    return tRectf(midPoint.x, midPoint.y, calculatedSize.width, calculatedSize.height);
}

tAutosizeViewport::tAutosizeViewport(const tDimension2f& newViewSize)
:   mOriginalSize(newViewSize),
    mViewSize(newViewSize.width, newViewSize.height),
    mWantedAspectRatio((float)newViewSize.width / (float)newViewSize.height),
    mIsOrientationPortrait(true),
    mDirty(true)
{
    gAutosizeViewport = this;
}

tDimension2f tAutosizeViewport::getSize() const
{
    return mViewSize;
}

void tAutosizeViewport::run()
{
    if (mDirty)
    {
        tRectf viewPortRect = CalculateViewPortRect();

        tView::getInstance()->setOriginalSize(mOriginalSize);

        //TODO: Do we need to re-calc this?
        tView::getInstance()->setViewportRect(CalculateViewPortRect());

        if (!mIsOrientationPortrait)
        {
            float hOverW = (float)mViewSize.height / (float)mViewSize.width;
            float wOverH = (float)mViewSize.width / (float)mViewSize.height;
            viewPortRect.location.x *= hOverW;
            viewPortRect.location.y *= wOverH;
            viewPortRect.size.width *= hOverW;
            viewPortRect.size.height *= wOverH;
        }

        glViewport((GLint)viewPortRect.location.x, (GLint)viewPortRect.location.y,
                   (GLint)viewPortRect.size.width, (GLint)viewPortRect.size.height);

        mDirty = false;
    }
}

void tAutosizeViewport::onResize(const tDimension2f& newSize)
{
    //TODO: Don't cast this
    if (mViewSize != tDimension2f((int)newSize.width, (int)newSize.height))
    {
        mViewSize = tDimension2f((int)newSize.width, (int)newSize.height);

        mDirty = true;
    }
}

void tAutosizeViewport::onRotate(tOrientationType &msg)
{
    switch (msg)
    {
        case kPortrait:
        case kPortraitUpsidedown:
            mIsOrientationPortrait = true;
            break;

        default:
            mIsOrientationPortrait = false;
            break;
    }
    mDirty = true;
}

