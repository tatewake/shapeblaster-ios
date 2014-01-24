#include "ViewController.h"
#include "OpenGLView.h"

#include "Utility/package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

extern tAutosizeViewport* gAutosizeViewport;

@interface ViewController()
{
}
@property (strong, nonatomic) OpenGLView *glView;
@end

@implementation ViewController
@synthesize glView = _glView;

#pragma mark Construction / Destruction
- (void)viewDidLoad
{
    [super viewDidLoad];

    self.view.autoresizesSubviews = YES;

    self.glView = [[[OpenGLView alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    self.glView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;

    [self.view addSubview: self.glView];
}

- (void)viewDidUnload
{    
    [super viewDidUnload];
}

- (void)dealloc
{
    [super dealloc];
}

#pragma mark iOS 7.0
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

#pragma mark tOrientationType generation
- (void)viewWillLayoutSubviews
{
    [self willRotateToInterfaceOrientation:self.interfaceOrientation duration:0];
    [self didRotateFromInterfaceOrientation:self.interfaceOrientation];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
#pragma unused(interfaceOrientation)
    [UIView setAnimationsEnabled:NO];

    switch(interfaceOrientation)
    {
        case UIInterfaceOrientationLandscapeLeft:
        case UIInterfaceOrientationLandscapeRight:
            return YES;
            break;
    }

    return NO;
}

- (void)sendOrientationChangedMessage:(UIInterfaceOrientation)toInterfaceOrientation
{
    tOrientationType type = kPortrait;

    switch(toInterfaceOrientation)
    {
        default:
        case UIInterfaceOrientationPortrait:            type = kPortrait; break;
        case UIInterfaceOrientationPortraitUpsideDown:  type = kPortraitUpsidedown; break;
        case UIInterfaceOrientationLandscapeLeft:       type = kLandscapeLeft; break;
        case UIInterfaceOrientationLandscapeRight:      type = kLandscapeRight; break;
    }

    gAutosizeViewport->onRotate(type);
}

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
#pragma unused(duration)
    [UIView setAnimationsEnabled:NO];

    [self sendOrientationChangedMessage:toInterfaceOrientation];
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
#pragma unused(fromInterfaceOrientation)
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];
    [UIView setAnimationsEnabled:YES];

    tDimension2f newSize(int32_t([self.glView bounds].size.width * self.glView.contentScaleFactor),
                         int32_t([self.glView bounds].size.height * self.glView.contentScaleFactor));

    gAutosizeViewport->onResize(newSize);
    tView::getInstance()->onResize(newSize);
}

@end
