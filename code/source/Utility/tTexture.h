#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class tSurface;

class tTexture
{
protected:
    tDimension2f    mTextureSize;
    tDimension2f    mSurfaceSize;
    GLuint          mTextureID;       //This is the 'id' we reference when we want to use it.

public:
    tTexture(const tSurface& newSurface);
    ~tTexture();

    tDimension2f getSize() const;
    tDimension2f getSurfaceSize() const;

    friend class tSurface;

    friend class tSpriteBatch;
};

