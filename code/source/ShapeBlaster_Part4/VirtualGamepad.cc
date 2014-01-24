#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

VirtualGamepad::VirtualGamepad()
:   mLeftStick(kCenter),
    mRightStick(kCenter)
{
    mLeftPoint  = tPoint2f(int(3.0f/80.0f * 800.0f), 600 - int(21.0f/160.0f * 600.0f) - 128);
    mRightPoint = tPoint2f(800 - int(3.0f/80.0f * 800.0f) - 128, 600 - int(21.0f/160.0f * 600.0f) - 128);
}

void VirtualGamepad::DrawStickAtPoint(tSpriteBatch* spriteBatch, const tPoint2f& point, State state)
{
    tPoint2f offset = tPoint2f(18, 18);
    spriteBatch->draw(10, Art::getInstance()->getVPadBottom(), point, tOptional<tRectf>());

    switch (state)
    {
        case kCenter:       offset += tPoint2f(0, 0); break;

        case kTopLeft:      offset += tPoint2f(-13, -13); break;
        case kTop:          offset += tPoint2f(  0, -18); break;
        case kTopRight:     offset += tPoint2f( 13, -13); break;
        case kRight:        offset += tPoint2f( 18,   0); break;
        case kBottomRight:  offset += tPoint2f( 13,  13); break;
        case kBottom:       offset += tPoint2f(  0,  18); break;
        case kBottomLeft:   offset += tPoint2f(-13,  13); break;
        case kLeft:         offset += tPoint2f(-18,   0); break;
    }

    spriteBatch->draw(11, Art::getInstance()->getVPadTop(), point + offset, tOptional<tRectf>());
}

void VirtualGamepad::UpdateBasedOnKeys()
{
    Input* inp = Input::getInstance();

    mLeftStick  = kCenter;

    if (inp->mFreshKeyboardState[Input::kA])
    {
        mLeftStick |= kLeft;
    }
    else if (inp->mFreshKeyboardState[Input::kD])
    {
        mLeftStick |= kRight;
    }
    if (inp->mFreshKeyboardState[Input::kW])
    {
        mLeftStick |= kTop;
    }
    else if (inp->mFreshKeyboardState[Input::kS])
    {
        mLeftStick |= kBottom;
    }

    mRightStick = kCenter;

    if (inp->mFreshKeyboardState[Input::kLeft])
    {
        mRightStick |= kLeft;
    }
    else if (inp->mFreshKeyboardState[Input::kRight])
    {
        mRightStick |= kRight;
    }
    if (inp->mFreshKeyboardState[Input::kUp])
    {
        mRightStick |= kTop;
    }
    else if (inp->mFreshKeyboardState[Input::kDown])
    {
        mRightStick |= kBottom;
    }
}

void VirtualGamepad::draw(tSpriteBatch* spriteBatch)
{
    DrawStickAtPoint(spriteBatch, mLeftPoint, (State)mLeftStick);
    DrawStickAtPoint(spriteBatch, mRightPoint, (State)mRightStick);
}

void VirtualGamepad::update(const tKeyboardEvent &msg)
{
#pragma unused(msg)
    UpdateBasedOnKeys();
}

void VirtualGamepad::update(const tTouchEvent& msg)
{
#pragma unused(msg)
    UpdateBasedOnKeys();
}


