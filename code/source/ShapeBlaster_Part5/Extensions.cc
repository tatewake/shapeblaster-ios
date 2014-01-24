#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

float Extensions::toAngle(const tVector2f& vector)
{
    return (float)atan2f(vector.y, vector.x);
}

tVector2f Extensions::scaleTo(const tVector2f& vector, float length)
{
    return vector * (length / vector.length());
}

tPoint2f Extensions::toPoint(const tVector2f& vector)
{
    return tPoint2f((int)vector.x, (int)vector.y);
}

float Extensions::nextFloat(float minValue, float maxValue)
{
    return (float)tMath::random() * (maxValue - minValue) + minValue;
}

tVector2f Extensions::nextVector2(float minLength, float maxLength)
{
    float theta = tMath::random() * 2.0f * tMath::PI;
    float length = nextFloat(minLength, maxLength);
    return tVector2f(length * (float)cosf(theta), length * (float)sinf(theta));
}

tColor4f Extensions::colorLerp(const tColor4f& a, const tColor4f& b, float alpha)
{
    return tColor4f(tMath::mix(a.r, b.r, alpha),
                    tMath::mix(a.g, b.g, alpha),
                    tMath::mix(a.b, b.b, alpha),
                    tMath::mix(a.a, b.a, alpha));
}

void Extensions::drawLine(tSpriteBatch* spriteBatch, const tVector2f& start, const tVector2f& end, const tColor4f& color, float thickness)
{
    tVector2f delta = end - start;

    spriteBatch->draw(0, Art::getInstance()->getPixel(), tPoint2f((int32_t)start.x, (int32_t)start.y), tOptional<tRectf>(), color,
                     toAngle(delta), tPoint2f(0, 0), tVector2f(delta.length(), thickness));
}

