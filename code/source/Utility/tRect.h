#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class tRectf
{
public:
    tVector2f location;
    tVector2f size;

    //Comparison / relational operators
    bool operator ==(const tRectf& b) const { return (location == b.location) && (size == b.size); }
    bool operator !=(const tRectf& b) const { return !(*this == b); }

public:
    tRectf() { }
    tRectf(float nx, float ny, float nw, float nh) : location(nx, ny), size(nw, nh) { }
    tRectf(float nx, float ny, const tVector2f& nd) : location(nx, ny), size(nd) { }
    tRectf(const tVector2f& np, float nw, float nh) : location(np), size(nw, nh) { }
    tRectf(const tVector2f& np, const tVector2f& nd) : location(np), size(nd) { }

    bool contains(const tVector2f& newPt) const
    {
        return  newPt.x >= location.x &&
                newPt.y >= location.y &&
                newPt.x < (location.x + size.width) &&
                newPt.y < (location.y + size.height);
    }
};
