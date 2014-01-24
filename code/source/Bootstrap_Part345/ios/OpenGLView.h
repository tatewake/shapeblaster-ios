#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

@interface OpenGLView : UIView
{
    CAEAGLLayer*    mEAGLLayer;
    EAGLContext*    mEAGLContext;
    GLuint          mColorBuffer;
    GLuint          mDepthBuffer;
    CADisplayLink*  mDisplayLink;

    UITouch*        mTouchPtr[12];
}

- (void)createDisplayLink;
- (void)destroyDisplayLink;
- (void)pauseDisplayLink;
- (void)resumeDisplayLink;

@end
