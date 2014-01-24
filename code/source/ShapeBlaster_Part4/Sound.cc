#include "Utility/package.h"
#include "Sound.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

Sound::Sound()
{
    char buf[80];
    mMusic = new tSound("music.mp3");

    for (int i = 1; i <= 8; i++)
    {
        sprintf(buf, "explosion-0%d.wav", i);
        mExplosions.push_back(new tSound(buf));

        if (i <= 4)
        {
            sprintf(buf, "shoot-0%d.wav", i);
            mShots.push_back(new tSound(buf));
        }

        sprintf(buf, "spawn-0%d.wav", i);
        mSpawns.push_back(new tSound(buf));
    }
}

tSound* Sound::getMusic() const
{
    return mMusic;
}
tSound* Sound::getExplosion() const
{
    size_t i = size_t(tMath::random() * (float)mExplosions.size()) % mExplosions.size();
    return mExplosions[i];
}

tSound* Sound::getShot() const
{
    size_t i = size_t(tMath::random() * (float)mShots.size()) % mShots.size();
    return mShots[i];
}

tSound* Sound::getSpawn() const
{
    size_t i = size_t(tMath::random() * (float)mSpawns.size()) % mSpawns.size();
    return mSpawns[i];
}

