#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class tKeyboardEvent;
class tTouchEvent;

class Input
:   public tSingleton<Input>
{
protected:
    tPoint2f    mMouseState;
    tPoint2f    mLastMouseState;
    tPoint2f    mFreshMouseState;
    std::vector<bool>   mKeyboardState;
    std::vector<bool>   mLastKeyboardState;
    std::vector<bool>   mFreshKeyboardState;
    bool        mIsAimingWithMouse;
    uint8_t      mLeftEngaged;
    uint8_t      mRightEngaged;

public:
    enum KeyType
    {
        kUp = 0,
        kLeft,
        kDown,
        kRight,
        kW,
        kA,
        kS,
        kD,
    };

protected:
    tVector2f GetMouseAimDirection() const;

protected:
    Input();

public:
    tPoint2f getMousePosition() const;

    void update();

    // Checks if a key was just pressed down
    bool wasKeyPressed(KeyType) const;
    tVector2f getMovementDirection() const;
    tVector2f getAimDirection() const;

    void onKeyboard(const tKeyboardEvent& msg);
    void onTouch(const tTouchEvent& msg);

    friend class tSingleton<Input>;
    friend class VirtualGamepad;
};
