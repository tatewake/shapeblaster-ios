#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class ColorUtil
{
public:

    static tVector3f ColorToHSV(const tColor4f& color);
    static tColor4f HSVToColor(const tVector3f& hsv);
    static tColor4f HSVToColor(float h, float s, float v);
};

