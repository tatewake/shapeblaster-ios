#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class tVector4f;
class tMatrix2x2f;
class tMatrix4x4f;

class tVector2f
{
public:
    union
    {
        float value[2];
        struct { float x, y; };
        struct { float r, g; };
        struct { float s, t; };
        struct { float width, height; };
    };

    //Array subscript operator
	float& operator [](const size_t i) { assert(i < 2); return value[i]; }
	const float& operator [](const size_t i) const { assert(i < 2); return value[i]; }

    //Arithmetic operators
    tVector2f operator +(const tVector2f& b) const { return tVector2f(x + b.x, y + b.y); }
    tVector2f operator -(const tVector2f& b) const { return tVector2f(x - b.x, y - b.y); }
    tVector2f operator *(const tVector2f& b) const { return tVector2f(x * b.x, y * b.y); }
    tVector2f operator /(const tVector2f& b) const { return tVector2f(x / b.x, y / b.y); }
    tVector2f operator -() const /* Unary minus */ { return tVector2f(-x, -y); }
    tVector2f operator *(const float& b) const { return tVector2f(x * b, y * b); }
    tVector2f operator /(const float& b) const { return tVector2f(x / b, y / b); }

    bool operator ==(const tVector2f& b) const { return (x == b.x) && (y == b.y); }
    bool operator !=(const tVector2f& b) const { return !(*this == b); }

    //Arithmetic assignment operators
    tVector2f& operator +=(const tVector2f& b) { *this = *this + b; return *this; }
    tVector2f& operator -=(const tVector2f& b) { *this = *this - b; return *this; }
    tVector2f& operator *=(const tVector2f& b) { *this = *this * b; return *this; }
    tVector2f& operator /=(const tVector2f& b) { *this = *this / b; return *this; }
    tVector2f& operator *=(const float& b) { *this = *this * b; return *this; }
    tVector2f& operator /=(const float& b) { *this = *this / b; return *this; }

public:
    explicit tVector2f() : x(0), y(0) { }
    explicit tVector2f(const float& n) : x(n), y(n) { }
    explicit tVector2f(const float& nx, const float& ny) : x(nx), y(ny) { }

public:
    // Geometric functions
    float         length() const;
    float         lengthSquared() const;
    float         distance(const tVector2f &p1) const;
    float         distanceSquared(const tVector2f &p1) const;
    float         dot(const tVector2f &v2) const;
    tVector2f     normalize() const;
};

tVector2f operator* (const float &s, const tVector2f &v);

class tVector3f
{
public:
    union
    {
        float value[3];
        struct { float x, y, z; };
        struct { float r, g, b; };
        struct { float s, t, p; };
        struct { float width, height, depth; };
    };

    //Array subscript operator
	float& operator [](const size_t i) { assert(i < 3); return value[i]; }
	const float& operator [](const size_t i) const { assert(i < 3); return value[i]; }

    //Arithmetic operators
    tVector3f operator +(const tVector3f& b) const { return tVector3f(x + b.x, y + b.y, z + b.z); }
    tVector3f operator -(const tVector3f& b) const { return tVector3f(x - b.x, y - b.y, z - b.z); }
    tVector3f operator *(const tVector3f& b) const { return tVector3f(x * b.x, y * b.y, z * b.z); }
    tVector3f operator /(const tVector3f& b) const { return tVector3f(x / b.x, y / b.y, z / b.z); }
    tVector3f operator -() const /* Unary minus */ { return tVector3f(-x, -y, -z); }
    tVector3f operator *(const float& b) const { return tVector3f(x * b, y * b, z * b); }
    tVector3f operator /(const float& b) const { return tVector3f(x / b, y / b, z / b); }
    
    bool operator ==(const tVector3f& b) const { return (x == b.x) && (y == b.y) && (z == b.z); }
    bool operator !=(const tVector3f& b) const { return !(*this == b); }
    
    //Arithmetic assignment operators
    tVector3f& operator +=(const tVector3f& b) { *this = *this + b; return *this; }
    tVector3f& operator -=(const tVector3f& b) { *this = *this - b; return *this; }
    tVector3f& operator *=(const tVector3f& b) { *this = *this * b; return *this; }
    tVector3f& operator /=(const tVector3f& b) { *this = *this / b; return *this; }
    tVector3f& operator *=(const float& b) { *this = *this * b; return *this; }
    tVector3f& operator /=(const float& b) { *this = *this / b; return *this; }
    
public:
    explicit tVector3f() : x(0), y(0), z(0) { }
    explicit tVector3f(const float& n) : x(n), y(n), z(n) { }
    explicit tVector3f(const float& nx, const float& ny, const float& nz) : x(nx), y(ny), z(nz) { }

public:
    // Geometric functions
	float       length() const;
    float       lengthSquared() const;
    float       distanceSquared(const tVector3f &p1) const;
	float       distance(const tVector3f &p1) const;
    float       dot(const tVector3f &v2) const;
    tVector3f   cross(const tVector3f &y) const;
	tVector3f   normalize() const;
};

tVector3f operator* (const float &s, const tVector3f &v);

class tVector4f
{
public:
    union
    {
        float value[4];
        struct { float x, y, z, w; };
        struct { float r, g, b, a; };
        struct { float s, t, p, q; };
    };

    //Array subscript operator
	float& operator [](const size_t i) { assert(i < 4); return value[i]; }
	const float& operator [](const size_t i) const { assert(i < 4); return value[i]; }

    //Arithmetic operators
    tVector4f operator +(const tVector4f& b) const { return tVector4f(x + b.x, y + b.y, z + b.z, w + b.w); }
    tVector4f operator -(const tVector4f& b) const { return tVector4f(x - b.x, y - b.y, z - b.z, w - b.w); }
    tVector4f operator *(const tVector4f& b) const { return tVector4f(x * b.x, y * b.y, z * b.z, w * b.w); }
    tVector4f operator /(const tVector4f& b) const { return tVector4f(x / b.x, y / b.y, z / b.z, w / b.w); }
    tVector4f operator -() const /* Unary minus */ { return tVector4f(-x, -y, -z, -w); }
    tVector4f operator *(const float& b) const { return tVector4f(x * b, y * b, z * b, w * b); }
    tVector4f operator /(const float& b) const { return tVector4f(x / b, y / b, z / b, w / b); }
    
    bool operator ==(const tVector4f& b) const { return (x == b.x) && (y == b.y) && (z == b.z) && (w == b.w); }
    bool operator !=(const tVector4f& b) const { return !(*this == b); }
    
    //Arithmetic assignment operators
    tVector4f& operator +=(const tVector4f& b) { *this = *this + b; return *this; }
    tVector4f& operator -=(const tVector4f& b) { *this = *this - b; return *this; }
    tVector4f& operator *=(const tVector4f& b) { *this = *this * b; return *this; }
    tVector4f& operator /=(const tVector4f& b) { *this = *this / b; return *this; }
    tVector4f& operator *=(const float& b) { *this = *this * b; return *this; }
    tVector4f& operator /=(const float& b) { *this = *this / b; return *this; }
    
public:
    explicit tVector4f() : x(0), y(0), z(0), w(0) { }
    explicit tVector4f(const float& n) : x(n), y(n), z(n), w(n) { }
    explicit tVector4f(const float& nx, const float& ny, const float& nz, const float& nw) : x(nx), y(ny), z(nz), w(nw) { }
    explicit tVector4f(const tVector3f& v, const float& nw) : x(v.x), y(v.y), z(v.z), w(nw) { }

public:
    // Geometric functions
	float       length() const;
    float       lengthSquared() const;
	float       distance(const tVector4f &p1) const;
    float       distanceSquared(const tVector4f &p1) const;
    float       dot(const tVector4f &v2) const;
	tVector4f   normalize() const;
};

tVector4f operator* (const float &s, const tVector4f &v);

typedef tVector2f tPoint2f;
typedef tVector3f tPoint3f;
typedef tVector4f tPoint4f;

typedef tVector2f tTexCoord2f;

typedef tVector3f tColor3f;
typedef tVector4f tColor4f;

typedef tVector2f tDimension2f;

