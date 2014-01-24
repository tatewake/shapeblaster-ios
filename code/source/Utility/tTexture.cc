#include "Utility/package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

tTexture::tTexture(const tSurface& newSurface)
{
    //TODO: optimize this-- we're potentially doing a copy operation we don't need to do in most cases.
    tSurface s1(tDimension2f(tMath::roundPow2(newSurface.getSize().width), tMath::roundPow2(newSurface.getSize().height)));

    memset(s1.mPtr, 0, (size_t)(s1.mSize.height * s1.mBytesPerRow));

    for(size_t j = 0; j < (size_t)newSurface.getSize().height; j++)
    {
        memcpy(&s1.mPtr[j * s1.mBytesPerRow], &newSurface.mPtr[j * newSurface.mBytesPerRow], newSurface.mBytesPerRow);
    }

    mSurfaceSize = newSurface.mSize;
    mTextureSize = s1.mSize;

    glGenTextures(1, &mTextureID);

    assert(mTextureID != 0);

    glBindTexture (GL_TEXTURE_2D, mTextureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, (GLint)GL_RGBA, (GLsizei)s1.mSize.width, (GLsizei)s1.mSize.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, s1.mPtr);

    glBindTexture(GL_TEXTURE_2D, 0);
}

tTexture::~tTexture()
{
    glDeleteTextures(1, &mTextureID);
}

tDimension2f tTexture::getSize() const
{
    return mTextureSize;
}

tDimension2f tTexture::getSurfaceSize() const
{
    return mSurfaceSize;
}

