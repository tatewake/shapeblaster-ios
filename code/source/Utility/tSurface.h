#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class tTexture;

class tSurface
{
protected:
    tDimension2f    mSize;
    uint16_t        mBytesPerRow;
    uint8_t*        mPtr;

public:
    tSurface& operator=(const tSurface& origSurface);

public:
    tSurface(const std::string& file);
    tSurface(const tDimension2f& newSize);
    tSurface(const tSurface& origSurface);
    ~tSurface();

    tDimension2f    getSize() const;

    friend class tTexture;
};

