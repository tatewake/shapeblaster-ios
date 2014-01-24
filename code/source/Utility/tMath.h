#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class tMath
{
public:
    static const float PI;       // A mathematical constant for the ratio of the circumference of a circle to its diameter, expressed as pi, with a value of 3.141592653589793.

public:
    // Angle and trigonometric functions
    static float radians(const float &degrees)
    {
        return degrees * (PI / 180.0f);
    }

    static float degrees(const float &radians)
    {
        return radians * (180.0f / PI);
    }

    // Exponential functions
    static float roundPow2(const float &x)
    {
        if (x > 0)
        {
            return 1 << uint32_t(log2(float(x - 1)) + 1);
        }
        
        return 1;
    }

    // Common functions
    static float min(const float &x, const float &y)
    {
        return (x < y) ? x : y;
    }
    static float max(const float &x, const float &y)
    {
        return (x > y) ? x : y;
    }
    static float clamp(const float &x, const float &minVal, const float &maxVal)
    {
        return max(min(x, maxVal), minVal);
    }
    static float mix(float const & x, float const & y, float const & a)
    {
        return float(float(x) + a * float(y - x));
    }

    static float random();
};
