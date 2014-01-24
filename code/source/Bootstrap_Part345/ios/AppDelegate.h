#import <UIKit/UIKit.h>
#import "OpenGLView.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

@class ViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    bool mSuspended;
    bool mRunning;
}

@property (strong, nonatomic) UIWindow*         window;
@property (strong, nonatomic) ViewController*   viewController;

@end
