#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class tSound;

class Sound
: public tSingleton<Sound>
{
protected:
    tSound* mMusic;
    std::vector<tSound*> mExplosions;
    std::vector<tSound*> mShots;
    std::vector<tSound*> mSpawns;

protected:
    Sound();

public:
    tSound* getMusic() const;
    tSound* getExplosion() const;
    tSound* getShot() const;
    tSound* getSpawn() const;

    friend class tSingleton<Sound>;
};

