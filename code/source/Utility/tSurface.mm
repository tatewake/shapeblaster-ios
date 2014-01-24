#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <UIKit/UIImage.h>
#endif

#include "Utility/package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

tSurface& tSurface::operator=(const tSurface& origSurface)
{
    if (this != &origSurface)
    {
        delete [] mPtr;

        mSize           = origSurface.mSize;
        mBytesPerRow    = origSurface.mBytesPerRow;

        mPtr = new uint8_t[(int32_t)(origSurface.mSize.height * mBytesPerRow)];

        assert(mPtr);

        memcpy(mPtr, origSurface.mPtr, (size_t)(origSurface.mSize.height * mBytesPerRow));
    }

    return *this;
}

tSurface::tSurface(const std::string& filename)
: mSize(0,0), mPtr(NULL)
{
    @autoreleasepool
    {
        //From: http://www.david-amador.com/2011/03/loading-images-into-opengl-in-iphone/

        UIImage* baseImage = [UIImage imageNamed:[NSString stringWithCString:filename.c_str() encoding:NSUTF8StringEncoding]];

        assert(baseImage);

        // Get Image size
        mSize.width     = (int32_t)CGImageGetWidth(baseImage.CGImage);
        mSize.height    = (int32_t)CGImageGetHeight(baseImage.CGImage);
        mBytesPerRow    = uint16_t(4 * mSize.width);

        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

        // Allocate memory for image
        uint8_t* imageData = (uint8_t*)malloc( size_t(mSize.height * mBytesPerRow) );
        CGContextRef imgcontext = CGBitmapContextCreate( imageData, (size_t)mSize.width, (size_t)mSize.height, 8, mBytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big );
        CGColorSpaceRelease( colorSpace );
        CGContextClearRect( imgcontext, CGRectMake( 0, 0, mSize.width, mSize.height ) );
        CGContextTranslateCTM( imgcontext, 0, 0 );
        CGContextDrawImage( imgcontext, CGRectMake( 0, 0, mSize.width, mSize.height ), baseImage.CGImage );

        //	We have to copy that raw data one row at a time….yay
        mPtr = new uint8_t[(int32_t)(mSize.height * mBytesPerRow)];

        memcpy(mPtr, imageData, size_t(mSize.height * mBytesPerRow));

        // Release context
        CGContextRelease(imgcontext);
        // Free Stuff
        free(imageData);
    }

    assert((mSize.width != 0) && (mSize.height != 0) && (mPtr));
}

//TODO: This might be okay, I dunno?!
tSurface::tSurface(const tDimension2f& newSize)
: mSize(newSize)
{
    assert(newSize.width > 0 && newSize.height > 0);

    mBytesPerRow = uint16_t(4 * newSize.width);
    if ((mBytesPerRow & 0x3) != 0)
    {
        mBytesPerRow = (mBytesPerRow & ~0x3) + 4;
    }
    
    mPtr = new uint8_t[(int32_t)(newSize.height * mBytesPerRow)];
    
    assert(mPtr);
}

tSurface::tSurface(const tSurface& origSurface)
: mSize(origSurface.mSize), mBytesPerRow(origSurface.mBytesPerRow)
{
    mPtr = new uint8_t[(int32_t)(origSurface.mSize.height * mBytesPerRow)];

    assert(mPtr);
    
    memcpy(mPtr, origSurface.mPtr, (size_t)(origSurface.mSize.height * mBytesPerRow));
}

tSurface::~tSurface()
{
    if (mPtr)
    {
        delete[] mPtr;
    }
}

tDimension2f tSurface::getSize() const
{
    return mSize;
}

