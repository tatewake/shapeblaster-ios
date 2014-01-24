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
    tPoint2f leftPoint  = VirtualGamepad::getInstance()->mLeftPoint - tPoint2f(18, 18);
    tPoint2f rightPoint = VirtualGamepad::getInstance()->mRightPoint - tPoint2f(18, 18);

    tPoint2f intPoint((int)msg.mLocation.x, (int)msg.mLocation.y);

    bool mouseDown = (msg.mEvent == tTouchEvent::kTouchBegin) || (msg.mEvent == tTouchEvent::kTouchMove);

    if (!mouseDown)
    {
        if (msg.mID == mLeftEngaged)
        {
            mFreshKeyboardState[kA] = false;
            mFreshKeyboardState[kD] = false;
            mFreshKeyboardState[kW] = false;
            mFreshKeyboardState[kS] = false;
        }
        else if (msg.mID == mRightEngaged)
        {
            mFreshKeyboardState[kUp]    = false;
            mFreshKeyboardState[kDown]  = false;
            mFreshKeyboardState[kLeft]  = false;
            mFreshKeyboardState[kRight] = false;
        }
    }

    if (mouseDown && tRectf(leftPoint, 164, 164).contains(intPoint))
    {
        mLeftEngaged = msg.mID;

        mFreshKeyboardState[kA] = false;
        mFreshKeyboardState[kD] = false;
        mFreshKeyboardState[kW] = false;
        mFreshKeyboardState[kS] = false;

        if (tRectf(leftPoint, 72, 164).contains(intPoint))
        {
            mFreshKeyboardState[kA] = true;
            mFreshKeyboardState[kD] = false;
        }
        else if (tRectf(leftPoint + tPoint2f(128, 0), 72, 164).contains(intPoint))
        {
            mFreshKeyboardState[kA] = false;
            mFreshKeyboardState[kD] = true;
        }

        if (tRectf(leftPoint, 164, 72).contains(intPoint))
        {
            mFreshKeyboardState[kW] = true;
            mFreshKeyboardState[kS] = false;
        }
        else if (tRectf(leftPoint + tPoint2f(0, 128), 164, 72).contains(intPoint))
        {
            mFreshKeyboardState[kW] = false;
            mFreshKeyboardState[kS] = true;
        }
    }

    if (mouseDown && tRectf(rightPoint, 164, 164).contains(intPoint))
    {
        mRightEngaged = msg.mID;

        mFreshKeyboardState[kUp]    = false;
        mFreshKeyboardState[kDown]  = false;
        mFreshKeyboardState[kLeft]  = false;
        mFreshKeyboardState[kRight] = false;

        if (tRectf(rightPoint, 72, 164).contains(intPoint))
        {
            mFreshKeyboardState[kLeft]  = true;
            mFreshKeyboardState[kRight] = false;
        }
        else if (tRectf(rightPoint + tPoint2f(128, 0), 72, 164).contains(intPoint))
        {
            mFreshKeyboardState[kLeft]  = false;
            mFreshKeyboardState[kRight] = true;
        }

        if (tRectf(rightPoint, 164, 72).contains(intPoint))
        {
            mFreshKeyboardState[kUp]    = true;
            mFreshKeyboardState[kDown]  = false;
        }
        else if (tRectf(rightPoint + tPoint2f(0, 128), 164, 72).contains(intPoint))
        {
            mFreshKeyboardState[kUp]    = false;
            mFreshKeyboardState[kDown]  = true;
        }
    }

    if (!tRectf(leftPoint, 164, 164).contains(intPoint) && !tRectf(rightPoint, 164, 164).contains(intPoint))
    {
        mFreshMouseState = tPoint2f((int32_t)msg.mLocation.x, (int32_t)msg.mLocation.y);
    }
}
