#include "Utility/package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

uint8_t              tSound::mAvailable   = 0;
std::list<tSound*>  tSound::mPausedSounds;
std::list<tSound*>  tSound::mAllSounds;
bool                tSound::mPaused      = false;

@interface appleAVAudioPlayerDelegate : NSObject<AVAudioPlayerDelegate>
{
@public
    tSound* parent;
}
- (void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player error:(NSError *)error;
- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag;
@end

@implementation appleAVAudioPlayerDelegate

- (void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player error:(NSError *)error
{
#pragma unused(player, error)
}

- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag
{
#pragma unused(player, flag)

    parent->OnCompleteCallback();
}

@end

void tSound::OnCompleteCallback()
{
    if (mIsPlaying)
    {
        mIsPlaying = false;
    }
}

void tSound::RegisterSound(tSound* newSound)
{
    if (tSound::mAvailable != 0)
    {
        assert(newSound);
        assert(find(mAllSounds.begin(), mAllSounds.end(), newSound) == mAllSounds.end());

        mAllSounds.push_back(newSound);
    }
}

void tSound::UnregisterSound(tSound* newSound)
{
    if (tSound::mAvailable != 0)
    {
        assert(newSound);
        assert(find(mAllSounds.begin(), mAllSounds.end(), newSound) != mAllSounds.end());

        mAllSounds.remove(newSound);
        mPausedSounds.remove(newSound);
    }
}

void tSound::OnSuspend()
{
    std::list<tSound*>::iterator iter;

    for(iter = mAllSounds.begin(); iter != mAllSounds.end(); iter++)
    {
        if ((*iter)->isPlaying())
        {
            (*iter)->pause();

            mPausedSounds.push_back(*iter);
        }
    }
}

void tSound::OnResume()
{
    std::list<tSound*>::iterator iter;

    for(iter = mPausedSounds.begin(); iter != mPausedSounds.end(); iter++)
    {
        if ((*iter)->isPaused())
        {
            (*iter)->resume();
        }
    }

    mPausedSounds.clear();
}

tSound::tSound(const std::string& filename)
:   mAvaudioplayer(NULL),
    mIsPlaying(false),
    mIsPaused(false)
{
    tSound::mAvailable++;
    RegisterSound(this);

    NSError* err;

    @autoreleasepool
    {
        mAvaudioplayer = [[AVAudioPlayer alloc] initWithContentsOfURL:
                          [NSURL fileURLWithPath:
                           [NSString stringWithFormat:@"%@/%s",
                            [[NSBundle mainBundle] resourcePath], filename.c_str()]]
                                                                error:&err];
    }

    assert(mAvaudioplayer);

    mAppleAVPlayerDelegate = [[appleAVAudioPlayerDelegate alloc] init];
    ((appleAVAudioPlayerDelegate*)mAppleAVPlayerDelegate)->parent = this;

    mAvaudioplayer.delegate = (appleAVAudioPlayerDelegate*)mAppleAVPlayerDelegate;

    [mAvaudioplayer prepareToPlay];
}

tSound::~tSound()
{
    stop();

    assert(mAvaudioplayer);
    [mAvaudioplayer release];
    [(appleAVAudioPlayerDelegate*)mAppleAVPlayerDelegate release];

    UnregisterSound(this);

    if (tSound::mAvailable)
    {
        tSound::mAvailable--;
    }
}

bool    tSound::isPlaying()
{
    return mIsPlaying;
}

bool    tSound::isPaused()
{
    return mIsPaused;
}

bool   tSound::play(float startTimeMS, uint32_t nloops)
{
    if (!mIsPlaying && !mIsPaused)
    {
        assert(mAvaudioplayer);

        mAvaudioplayer.numberOfLoops = nloops;

        mIsPlaying = [mAvaudioplayer playAtTime:mAvaudioplayer.deviceCurrentTime + startTimeMS / 1000.0f];

        return mIsPlaying;
    }
    
    return false;
}
void    tSound::pause()
{
    if (mIsPlaying && !mIsPaused)
    {
        assert(mAvaudioplayer);

        [mAvaudioplayer pause];

        mIsPaused = true;
    }
}

bool   tSound::resume()
{
    if (mIsPlaying && mIsPaused)
    {
        assert(mAvaudioplayer);

        mIsPaused = false;

        mIsPlaying = (bool)[mAvaudioplayer play];

        return mIsPlaying;
    }
    
    return false;
}

void    tSound::stop()
{
    if (mIsPlaying)
    {
        assert(mAvaudioplayer);

        mIsPlaying    = false;
        mIsPaused     = false;

        [mAvaudioplayer stop];
        mAvaudioplayer.currentTime = 0.0f;
    }
}

