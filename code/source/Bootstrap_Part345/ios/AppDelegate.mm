#import "AppDelegate.h"
#import "ViewController.h"

#ifdef TESTFLIGHT
#import "TestFlight.h"
#endif

#include "Utility/package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

@implementation AppDelegate

@synthesize window = mWindow;
@synthesize viewController = mViewController;

#pragma mark Constructor / Destructor

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
#pragma unused(application, launchOptions)
    mSuspended = false;
    mRunning = true;

    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    // Override point for customization after application launch.
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
    {
        if([[UIScreen mainScreen] bounds].size.height == 568)
        {
            self.viewController = [[[ViewController alloc] initWithNibName:@"ViewController_iPhone5" bundle:nil] autorelease];
        }
        else
        {
            self.viewController = [[[ViewController alloc] initWithNibName:@"ViewController_iPhone" bundle:nil] autorelease];
        }
    }
    else
    {
        self.viewController = [[[ViewController alloc] initWithNibName:@"ViewController_iPad" bundle:nil] autorelease];
    }

    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];
    return YES;
}

- (void)applicationWillTerminate:(UIApplication *)application
{
#pragma unused(application)
    [self.viewController->mOpenGLView pauseDisplayLink];
}

- (void)dealloc
{
    [mWindow release];
    [mViewController release];
    [super dealloc];
}

#pragma mark Suspend / Resume

- (void)applicationWillResignActive:(UIApplication *)application
{
#pragma unused(application)
    [self.viewController->mOpenGLView pauseDisplayLink];

    if (mRunning && !mSuspended)
    {
        mSuspended = true;

        tSound::OnSuspend();
    }
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
#pragma unused(application)
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
#pragma unused(application)
    [self.viewController->mOpenGLView resumeDisplayLink];

    if (mRunning && mSuspended)
    {
        mSuspended = false;

        tSound::OnResume();
    }
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
#pragma unused(application)
    [self.viewController->mOpenGLView resumeDisplayLink];

    if (mRunning && mSuspended)
    {
        mSuspended = false;

        tSound::OnResume();
    }
}

@end
