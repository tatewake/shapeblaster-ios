#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class MathUtil
{
public:
    static tVector2f fromPolar(float angle, float magnitude);

    static float catmullRom(const float value1, const float value2, const float value3, const float value4, float amount);
    static tVector2f catmullRom(const tVector2f& value1, const tVector2f& value2, const tVector2f& value3, const tVector2f& value4, float amount);
};

