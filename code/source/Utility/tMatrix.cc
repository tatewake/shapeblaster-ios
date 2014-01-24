#include "Utility/package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

tVector2f   operator *(const tMatrix2x2f& m,  const tVector2f& rt)   { return rt * m.transpose(); }
tVector2f   operator *(const tVector2f& ct,   const tMatrix2x2f& m)  { return tVector2f(ct.dot(m[0]), ct.dot(m[1])); }
tMatrix2x2f operator *(const tMatrix2x2f& m1, const tMatrix2x2f& m2) { return tMatrix2x2f(m1 * m2[0], m1 * m2[1]); }

