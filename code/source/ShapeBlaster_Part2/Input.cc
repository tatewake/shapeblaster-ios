#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

tVector2f Input::GetMouseAimDirection() const
{
    tVector2f direction = tVector2f(mMouseState.x, mMouseState.y) - PlayerShip::getInstance()->getPosition();

    if (direction == tVector2f(0,0))
    {
        return tVector2f(0,0);
    }

    return direction.normalize();
}

Input::Input()
:   mMouseState(-1,-1),
    mLastMouseState(-1,-1),
    mIsAimingWithMouse(false),
    mLeftEngaged(255),
    mRightEngaged(255)
{
    mKeyboardState.resize(8);
    mLastKeyboardState.resize(8);
    mFreshKeyboardState.resize(8);

    for(size_t i = 0; i < 8; i++)
    {
        mKeyboardState[i] = false;
        mLastKeyboardState[i] = false;
        mFreshKeyboardState[i] = false;
    }
}

tPoint2f Input::getMousePosition() const
{
    return mMouseState;
}

void Input::update()
{
    mLastKeyboardState  = mKeyboardState;
    mLastMouseState     = mMouseState;

    mKeyboardState      = mFreshKeyboardState;
    mMouseState         = mFreshMouseState;

    if (mKeyboardState[kLeft] || mKeyboardState[kRight] || mKeyboardState[kUp] || mKeyboardState[kDown])
    {
        mIsAimingWithMouse = false;
    }
    else if (mMouseState != mLastMouseState)
    {
        mIsAimingWithMouse = true;
    }
}

// Checks if a key was just pressed down
bool Input::wasKeyPressed(KeyType key) const
{
    return !mLastKeyboardState[key] && mKeyboardState[key];
}

tVector2f Input::getMovementDirection() const
{
    tVector2f direction(0,0);

    if (mKeyboardState[kA])
    {
        direction.x -= 1;
    }
    if (mKeyboardState[kD])
    {
        direction.x += 1;
    }
    if (mKeyboardState[kW])
    {
        direction.y -= 1;
    }
    if (mKeyboardState[kS])
    {
        direction.y += 1;
    }

    if (direction.lengthSquared() > 1)
    {
        direction.normalize();
    }

    return direction;
}

tVector2f Input::getAimDirection() const
{
    if (!mIsAimingWithMouse)
    {
        tVector2f direction(0,0);

        if (mKeyboardState[kLeft])
        {
            direction.x -= 1;
        }
        if (mKeyboardState[kRight])
        {
            direction.x += 1;
        }
        if (mKeyboardState[kUp])
        {
            direction.y -= 1;
        }
        if (mKeyboardState[kDown])
        {
            direction.y += 1;
        }

        if (direction == tVector2f(0,0))
        {
            return tVector2f(0,0);
        }
        else
        {
            return direction.normalize();
        }
    }

    return GetMouseAimDirection();
}


void Input::onKeyboard(const tKeyboardEvent& msg)
{
    switch (msg.mCharCode)
    {
        case 'w': mFreshKeyboardState[kW] = (msg.mEvent == tKeyboardEvent::kKeyDown); break;
        case 'a': mFreshKeyboardState[kA] = (msg.mEvent == tKeyboardEvent::kKeyDown); break;
        case 's': mFreshKeyboardState[kS] = (msg.mEvent == tKeyboardEvent::kKeyDown); break;
        case 'd': mFreshKeyboardState[kD] = (msg.mEvent == tKeyboardEvent::kKeyDown); break;

        case 0x00: mFreshKeyboardState[kUp]     = (msg.mEvent == tKeyboardEvent::kKeyDown); break;
        case 0x01: mFreshKeyboardState[kDown]   = (msg.mEvent == tKeyboardEvent::kKeyDown); break;
        case 0x02: mFreshKeyboardState[kLeft]   = (msg.mEvent == tKeyboardEvent::kKeyDown); break;
        case 0x03: mFreshKeyboardState[kRight]  = (msg.mEvent == tKeyboardEvent::kKeyDown); break;

        default: break;
    }
}

void Input::onTouch(const tTouchEvent& msg)
{
    mFreshMouseState = tPoint2f((int32_t)msg.mLocation.x, (int32_t)msg.mLocation.y);
}
