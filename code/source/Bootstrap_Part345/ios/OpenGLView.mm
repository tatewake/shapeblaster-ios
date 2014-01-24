#import "OpenGLView.h"

#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

extern tAutosizeViewport* gAutosizeViewport;
extern GameRoot* gApp;

//TODO: clean this up (gFrameBuffer)
GLuint gFrameBuffer;

@implementation OpenGLView

#pragma mark Required for OpenGL ES 2.0 Rendering
+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

#pragma mark Constructor / Destructor
- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {        
        [self SetupLayer];
        [self SetupRetina];
        [self SetupContext];
        [self SetupDepthBuffer];
        [self SetupRenderBuffer];
        [self SetupFrameBuffer];
        
        self.multipleTouchEnabled = YES;
        memset(mTouchPtr, 0, sizeof(mTouchPtr));
        

        gApp->onInitView();
        //TODO: Casting really necessary here?

        tDimension2f newSize(int32_t([self bounds].size.width * self.contentScaleFactor),
                             int32_t([self bounds].size.height * self.contentScaleFactor));

        gAutosizeViewport->onResize(newSize);
        tView::getInstance()->onResize(newSize);

        [self createDisplayLink];
    }
    return self;
}

- (void)dealloc
{
    [self destroyDisplayLink];
    [mEAGLContext release];
    mEAGLContext = nil;
    [super dealloc];
}

#pragma mark Redraw / rendering
- (void)render:(CADisplayLink*)displayLink
{
#pragma unused(displayLink)
    gApp->onRedrawView(tTimer::getTimeMS());
    
    [mEAGLContext presentRenderbuffer:GL_RENDERBUFFER];
}

#pragma mark Setting up OpenGL ES 2.0 on iOS

- (void)SetupLayer
{
    mEAGLLayer = (CAEAGLLayer*) self.layer;
    mEAGLLayer.opaque = YES;
}

//Based on http://stackoverflow.com/questions/3504173/detect-retina-display
- (void)SetupRetina
{
    if ([[UIScreen mainScreen] respondsToSelector:@selector(displayLinkWithTarget:selector:)] &&
        [UIScreen mainScreen].scale == 2.0f)
    {
        self.contentScaleFactor = [UIScreen mainScreen].scale;
        mEAGLLayer.contentsScale = [UIScreen mainScreen].scale;
    }
}

- (void)SetupContext
{
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    mEAGLContext = [[EAGLContext alloc] initWithAPI:api];
    if (!mEAGLContext) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext:mEAGLContext]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
}

- (void)SetupDepthBuffer
{
    glGenRenderbuffers(1, &mDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16,
                          (GLsizei)(self.frame.size.width * self.contentScaleFactor),
                          (GLsizei)(self.frame.size.height * self.contentScaleFactor));
}

- (void)SetupRenderBuffer {
    glGenRenderbuffers(1, &mColorBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mColorBuffer);        
    [mEAGLContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:mEAGLLayer];    
}

- (void)SetupFrameBuffer {    
    glGenFramebuffers(1, &gFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gFrameBuffer);   
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, mColorBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);
}

#pragma mark DisplayLink Management

- (void)createDisplayLink
{
    mDisplayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
    [mDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];    
}

- (void)destroyDisplayLink
{
    [mDisplayLink removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}
- (void)pauseDisplayLink
{
    mDisplayLink.paused = YES;
}

- (void)resumeDisplayLink
{
    mDisplayLink.paused = NO;
}

#pragma mark tTouchEvent management

- (bool) AddTouch:(UITouch*)newTouch
{
    for(uint8_t i = 0; i < 13; i++)
    {
        if (!mTouchPtr[i])
        {
            mTouchPtr[i] = newTouch;
            return true;
        }
    }

    return false;
}

- (bool) RemoveTouch:(UITouch*)newTouch
{
    for(uint8_t i = 0; i < 13; i++)
    {
        if (mTouchPtr[i] == newTouch)
        {
            mTouchPtr[i] = NULL;
            return true;
        }
    }

    return false;
}

- (uint8_t) GetTouch:(UITouch*)newTouch
{
    for(uint8_t i = 0; i < 13; i++)
    {
        if (mTouchPtr[i] == newTouch)
        {
            return i;
        }
    }

    return 0;
}

#pragma mark tTouchEvent generation

- (tPoint2f)CalculateLocation:(UITouch *)touch
{
    CGPoint loc = [self convertPoint:[touch locationInView:self] fromView:self];// [touch locationInView:self];

    //TODO: Casting ncessary here?
    tPoint2f calculatedLoc(loc.x, loc.y);
    tRectf viewPort = tView::getInstance()->getViewportRect();
    tDimension2f original = tView::getInstance()->getOriginalSize();

    //TODO: Is all of this casting necessary?
    calculatedLoc  -= tPoint2f(viewPort.location.width, viewPort.location.height) / self.contentScaleFactor;
    calculatedLoc.x = (calculatedLoc.x / viewPort.size.width * original.width);
    calculatedLoc.y = (calculatedLoc.y / viewPort.size.height * original.height);
    calculatedLoc  *= self.contentScaleFactor;
    
    return tPoint2f((int32_t)calculatedLoc.x, (int32_t)calculatedLoc.y);
}

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
#pragma unused(event)

    NSEnumerator* enumerator = [touches objectEnumerator];
    UITouch* touch = [enumerator nextObject];

    while (touch)
    {
        tPoint2f    touchPoint  = [self CalculateLocation:touch];

        if ([self AddTouch:touch])
        {
            uint8_t      touchID     = [self GetTouch:touch];

            Input::getInstance()->onTouch(tTouchEvent(tTouchEvent::kTouchBegin,
                                                     tPoint2f(touchPoint.x, touchPoint.y), touchID));

            VirtualGamepad::getInstance()->update(tTouchEvent(tTouchEvent::kTouchBegin,
                                                              tPoint2f(touchPoint.x, touchPoint.y), touchID));
        }

        touch = [enumerator nextObject];
    }
}

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
#pragma unused(event)
    NSEnumerator* enumerator = [touches objectEnumerator];
    UITouch* touch = [enumerator nextObject];

    while (touch)
    {
        tPoint2f    touchPoint  = [self CalculateLocation:touch];
        uint8_t      touchID     = [self GetTouch:touch];

        //TODO: Don't cast this
        Input::getInstance()->onTouch(tTouchEvent(tTouchEvent::kTouchMove,
                                                 tPoint2f(touchPoint.x, touchPoint.y), touchID));
        VirtualGamepad::getInstance()->update(tTouchEvent(tTouchEvent::kTouchMove,
                                                          tPoint2f(touchPoint.x, touchPoint.y), touchID));
        touch = [enumerator nextObject];
    }
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
#pragma unused(event)
    NSEnumerator* enumerator = [touches objectEnumerator];
    UITouch* touch = [enumerator nextObject];

    while (touch)
    {
        tPoint2f    touchPoint  = [self CalculateLocation:touch];
        uint8_t      touchID     = [self GetTouch:touch];

        if ([self RemoveTouch:touch])
        {
            //TODO: Don't cast this
            Input::getInstance()->onTouch(tTouchEvent(tTouchEvent::kTouchEnd,
                                                     tPoint2f(touchPoint.x, touchPoint.y), touchID));
            VirtualGamepad::getInstance()->update(tTouchEvent(tTouchEvent::kTouchEnd,
                                                              tPoint2f(touchPoint.x, touchPoint.y), touchID));
        }

        touch = [enumerator nextObject];
    }
}

- (void) touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self touchesEnded:touches withEvent:event];
}

@end
