#include "Utility/package.h"
#include "ColorUtil.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

tVector3f ColorUtil::ColorToHSV(const tColor4f& color)
{
    tVector3f c(color.r, color.g, color.b);
    float v = tMath::max(c.x, tMath::max(c.y, c.z));
    float chroma = v - tMath::min(c.x, tMath::min(c.y, c.z));

    if (chroma != 0.0f)
    {
        float s = chroma / v;

        if (c.x >= c.y && c.y >= c.z)
        {
            float h = (c.y - c.z) / chroma;

            if (h < 0)
            {
                h += 6;
            }

            return tVector3f(h, s, v);
        }
        else if (c.y >= c.z && c.y >= c.x)
        {
            return tVector3f((c.z - c.x) / chroma + 2, s, v);
        }

        return tVector3f((c.x - c.y) / chroma + 4, s, v);
    }

    return tVector3f(0, 0, v);
}

tColor4f ColorUtil::HSVToColor(const tVector3f& hsv)
{
    return HSVToColor(hsv.x, hsv.y, hsv.z);
}

tColor4f ColorUtil::HSVToColor(float h, float s, float v)
{
    if (h == 0 && s == 0)
    {
        return tColor4f(v, v, v, 1.0f);
    }

    float c = s * v;
    float x = c * (1 - abs(int32_t(h) % 2 - 1));
    float m = v - c;

    if (h < 1) return tColor4f(c + m, x + m, m, 1.0f);
    else if (h < 2) return tColor4f(x + m, c + m, m, 1.0f);
    else if (h < 3) return tColor4f(m, c + m, x + m, 1.0f);
    else if (h < 4) return tColor4f(m, x + m, c + m, 1.0f);
    else if (h < 5) return tColor4f(x + m, m, c + m, 1.0f);
    else return tColor4f(c + m, m, x + m, 1.0f);
}

