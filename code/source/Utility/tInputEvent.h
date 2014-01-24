#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

enum tOrientationType
{
    kPortrait = 0,
    kPortraitUpsidedown,
    kLandscapeLeft,
    kLandscapeRight,
};

class tKeyboardEvent
{
public:
    enum EventType
    {
        kKeyDown,
        kKeyUp,
    };

public:
    EventType   mEvent;
    uint8_t     mCharCode;

public:
    tKeyboardEvent(EventType evt, uint8_t nc)
    : mEvent(evt), mCharCode(nc) { }
};

class tTouchEvent
{
public:
    enum EventType
    {
        kTouchBegin,
        kTouchEnd,
        kTouchMove,
    };

public:
    EventType   mEvent;
    tPoint2f    mLocation;
    uint8_t     mID;

public:
    tTouchEvent(const EventType& newEvent, const tPoint2f& newLocation, const uint8_t& newID)
    : mEvent(newEvent), mLocation(newLocation), mID(newID) { }
};
