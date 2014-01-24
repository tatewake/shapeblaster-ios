#include "Utility/package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

const float tMath::PI        = 3.141592653589793f;    // A mathematical constant for the ratio of the circumference of a circle to its diameter, expressed as pi, with a value of 3.141592653589793.

static bool randomInit = false;
float tMath::random()
{
    if (!randomInit)
    {
        srand((uint32_t)time(NULL));
        randomInit = true;
    }
    return (float)::rand() / (float)RAND_MAX;
}
