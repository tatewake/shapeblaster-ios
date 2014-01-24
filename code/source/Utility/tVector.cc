#include "Utility/package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

tVector2f operator* (const float &s, const tVector2f &v) { return v * s; }
tVector3f operator* (const float &s, const tVector3f &v) { return v * s; }
tVector4f operator* (const float &s, const tVector4f &v) { return v * s; }

float tVector2f::length() const { return sqrtf(lengthSquared()); }
float tVector3f::length() const { return sqrtf(lengthSquared()); }
float tVector4f::length() const { return sqrtf(lengthSquared()); }

float tVector2f::lengthSquared() const { return dot(*this); }
float tVector3f::lengthSquared() const { return dot(*this); }
float tVector4f::lengthSquared() const { return dot(*this); }

float tVector2f::distance(const tVector2f &p1) const { return sqrtf((*this).distanceSquared(p1)); }
float tVector3f::distance(const tVector3f &p1) const { return sqrtf((*this).distanceSquared(p1)); }
float tVector4f::distance(const tVector4f &p1) const { return sqrtf((*this).distanceSquared(p1)); }

float tVector2f::distanceSquared(const tVector2f &p1) const { return (p1 - (*this)).lengthSquared(); }
float tVector3f::distanceSquared(const tVector3f &p1) const { return (p1 - (*this)).lengthSquared(); }
float tVector4f::distanceSquared(const tVector4f &p1) const { return (p1 - (*this)).lengthSquared(); }

float tVector2f::dot(const tVector2f &v2) const { return x * v2.x + y * v2.y; }
float tVector3f::dot(const tVector3f &v2) const { return x * v2.x + y * v2.y + z * v2.z; }
float tVector4f::dot(const tVector4f &v2) const { return x * v2.x + y * v2.y + z * v2.z + w * v2.w; }

tVector3f tVector3f::cross(const tVector3f &v2) const
{
    return tVector3f(y * v2.z - z * v2.y,
                     z * v2.x - x * v2.z,
                     x * v2.y - y * v2.x);
}

tVector2f tVector2f::normalize() const { return (*this) / length(); }
tVector3f tVector3f::normalize() const { return (*this) / length(); }
tVector4f tVector4f::normalize() const { return (*this) / length(); }

