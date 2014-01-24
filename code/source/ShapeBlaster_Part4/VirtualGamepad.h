#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class VirtualGamepad
:   public tSingleton<VirtualGamepad>
{
public:
    enum State
    {
        kCenter         = 0x00,

        kTop            = 0x01,
        kBottom         = 0x02,
        kLeft           = 0x04,
        kRight          = 0x08,

        kTopLeft        = 0x05,
        kTopRight       = 0x09,
        kBottomLeft     = 0x06,
        kBottomRight    = 0x0a,
    };

protected:
    tPoint2f mLeftPoint;
    tPoint2f mRightPoint;

    int mLeftStick;
    int mRightStick;

protected:
    VirtualGamepad();

    void DrawStickAtPoint(tSpriteBatch* spriteBatch, const tPoint2f& point, State state);

    void UpdateBasedOnKeys();

public:
    void draw(tSpriteBatch* spriteBatch);

    void update(const tKeyboardEvent& msg);
    void update(const tTouchEvent& msg);

    friend class tSingleton<VirtualGamepad>;
    friend class Input;
};

