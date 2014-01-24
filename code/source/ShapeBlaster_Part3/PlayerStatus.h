#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class PlayerStatus
: public tSingleton<PlayerStatus>
{
protected:
    static const float kMultiplierExpiryTime;
    static const int   kMaxMultiplier;
    static const std::string kHighScoreFilename;

    float   mMultiplierTimeLeft;
    int     mLives;
    int     mScore;
    int     mHighScore;
    int     mMultiplier;
    int     mScoreForExtraLife;
    uint32_t mLastTime;

protected:
    int     LoadHighScore();
    void    SaveHighScore(int score);

protected:
    PlayerStatus();

public:
    void    reset();
    void    update();
    void    addPoints(int basePoints);
    void    increaseMultiplier();
    void    resetMultiplier();
    void    removeLife();

    int     getLives() const;
    int     getScore() const;
    int     getHighScore() const;
    int     getMultiplier() const;
    bool    getIsGameOver() const;

    friend class tSingleton<PlayerStatus>;
};

