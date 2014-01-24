#include "Utility/package.h"

#include "MathUtil.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

tVector2f MathUtil::fromPolar(float angle, float magnitude)
{
    return magnitude * tVector2f((float)cosf(angle), (float)sinf(angle));
}

float MathUtil::catmullRom(const float value1, const float value2, const float value3, const float value4, float amount)
{
    // Using formula from http://www.mvps.org/directx/articles/catmull/
    // Internally using doubles not to lose precission
    float amountSquared = amount * amount;
    float amountCubed = amountSquared * amount;
    return (float)(0.5f * (2.0f * value2 +
                           (value3 - value1) * amount +
                           (2.0f * value1 - 5.0f * value2 + 4.0f * value3 - value4) * amountSquared +
                           (3.0f * value2 - value1 - 3.0f * value3 + value4) * amountCubed));
}

tVector2f MathUtil::catmullRom(const tVector2f& value1, const tVector2f& value2, const tVector2f& value3, const tVector2f& value4, float amount)
{
    return tVector2f(MathUtil::catmullRom(value1.x, value2.x, value3.x, value4.x, amount),
                     MathUtil::catmullRom(value1.y, value2.y, value3.y, value4.y, amount));
}

