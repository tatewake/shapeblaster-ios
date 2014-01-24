#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class tMatrix2x2f;
class tMatrix4x4f;

tMatrix2x2f operator *(const tMatrix2x2f& m1, const tMatrix2x2f& m2);

class tMatrix2x2f
{
public:
    tVector2f value[2];

public:
    //Array subscript operator
	tVector2f& operator [](const size_t i) { assert(i < 2); return value[i]; }
	const tVector2f& operator [](const size_t i) const { assert(i < 2); return value[i]; }

    // Arithmetic operators
    tMatrix2x2f operator +(const tMatrix2x2f& b) const
    {
        return tMatrix2x2f(value[0] + b[0],
                          value[1] + b[1]);
    }

    tMatrix2x2f operator +(const float& b) const
    {
        return tMatrix2x2f(value[0] + tVector2f(b),
                          value[1] + tVector2f(b));
    }

    tMatrix2x2f operator *(const float& b) const
    {
        return tMatrix2x2f(value[0] * b,
                          value[1] * b);
    }

    tMatrix2x2f operator /(const float& b) const
    {
        return tMatrix2x2f(value[0] / b,
                          value[1] / b);
    }

    // Comparison / relational operators
    bool operator ==(const tMatrix2x2f& b) const
    {
        return  (value[0] == b[0]) &&
                (value[1] == b[1]);
    }

    // Aliased Multiplication assignment rules
    tMatrix2x2f& operator *=(const tMatrix2x2f& b)    { *this = *this * b; return *this; }
    // Aliased Arithmetic and Comparison operators
    bool operator !=(const tMatrix2x2f& b) const     { return !(*this == b); }

public:
    explicit tMatrix2x2f()
    {
        value[0] = tVector2f(1, 0);
        value[1] = tVector2f(0, 1);
    }

    explicit tMatrix2x2f(const tVector2f& c0, const tVector2f& c1)  // Column constructor
    {
        value[0] = c0;
        value[1] = c1;
    }

    explicit tMatrix2x2f(const float& n)  // Diagonal constructor
    {
        value[0] = tVector2f(n, 0);
        value[1] = tVector2f(0, n);
    }

public:
    // Matrix functions
    tMatrix2x2f   transpose() const
    {
        return tMatrix2x2f(tVector2f(value[0].x, value[1].x),
                           tVector2f(value[0].y, value[1].y));
    }
	float determinant() const
    {
        return value[0].x * value[1].y - value[0].y * value[1].x;
    }

	tMatrix2x2f   inverse() const
    {
        return tMatrix2x2f(tVector2f( value[1].y, -value[0].y),
                           tVector2f(-value[1].x,  value[0].x)) / determinant();
    }
};

tVector2f   operator *(const tMatrix2x2f& m,  const tVector2f& rt);
tVector2f   operator *(const tVector2f& ct,   const tMatrix2x2f& m);
tMatrix2x2f operator *(const tMatrix2x2f& m1, const tMatrix2x2f& m2);

class tMatrix4x4f
{
public:
    tVector4f value[4];

public:
    //Array subscript operator
	tVector4f& operator [](const size_t i) { assert(i < 4); return value[i]; }
	const tVector4f& operator [](const size_t i) const { assert(i < 4); return value[i]; }

public:
    explicit tMatrix4x4f(const float& n)  // Diagonal constructor
    {
        value[0] = tVector4f(n, 0, 0, 0);
        value[1] = tVector4f(0, n, 0, 0);
        value[2] = tVector4f(0, 0, n, 0);
        value[3] = tVector4f(0, 0, 0, n);
    }

public:
    static tMatrix4x4f ortho(const float &left, const float &right, const float &bottom, const float &top)
    {
        tMatrix4x4f Result(1);

        Result[0][0] = 2.0f / (right - left);
        Result[1][1] = 2.0f / (top - bottom);
        Result[2][2] = - 1.0f;
        Result[3][0] = - (right + left) / (right - left);
        Result[3][1] = - (top + bottom) / (top - bottom);
        
        return Result;
    }
};

