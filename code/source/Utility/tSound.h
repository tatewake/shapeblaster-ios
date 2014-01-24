#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

#ifdef __OBJC__
#import <AVFoundation/AVFoundation.h>
#else
#define AVAudioPlayer void
#endif

class tSound
{
public:
    void OnCompleteCallback();
    
protected:
    AVAudioPlayer*  mAvaudioplayer;
    void*           mAppleAVPlayerDelegate;

    bool            mIsPlaying;
    bool            mIsPaused;

    static uint8_t                  mAvailable;
    static std::list<tSound*>       mPausedSounds;
    static std::list<tSound*>       mAllSounds;
    static bool                     mPaused;

protected:
    void RegisterSound(tSound* newSound);
    void UnregisterSound(tSound* newSound);

public:
    static void OnSuspend();
    static void OnResume();

public:
    explicit tSound(const std::string& filename);
    ~tSound();
    
    bool    isPlaying();
    bool    isPaused();

    bool    play(float startTimeMS = 0, uint32_t nloops = 0);
    void    pause();
    bool    resume();
    void    stop();
};

