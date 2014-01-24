#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

const float PlayerStatus::kMultiplierExpiryTime = 0.8f;
const int   PlayerStatus::kMaxMultiplier = 20;
const std::string PlayerStatus::kHighScoreFilename("highscore.txt");

void CreatePathIfNonExistant2(const std::string& newPath);
void CreatePathIfNonExistant2(const std::string& newPath)
{
    @autoreleasepool
    {
        // Create the path if it doesn't exist
        NSError *error;
        [[NSFileManager defaultManager]
         createDirectoryAtPath:[NSString stringWithUTF8String:newPath.c_str()]
         withIntermediateDirectories:YES
         attributes:nil
         error:&error];
    }
}

std::string GetExecutableName2();
std::string GetExecutableName2()
{
    return [[[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleExecutable"] UTF8String];
}

std::string GetPreferencePath2(const std::string& file);
std::string GetPreferencePath2(const std::string& file)
{
    std::string result = std::string([[NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES) objectAtIndex:0] UTF8String]) + "/" +
    GetExecutableName2() + "/";
    CreatePathIfNonExistant2(result);

    return result + file;
}

int     PlayerStatus::LoadHighScore()
{
    int score = 0;

    std::string fstring;

    if ([[NSFileManager defaultManager] fileExistsAtPath:[NSString stringWithUTF8String:GetPreferencePath2(kHighScoreFilename).c_str()]])
    {
        fstring = [[NSString stringWithContentsOfFile:[NSString stringWithUTF8String:GetPreferencePath2(kHighScoreFilename).c_str()]
                                                        encoding:NSUTF8StringEncoding error:nil] UTF8String];
        if (!fstring.empty())
        {
            sscanf(fstring.c_str(), "%d", &score);
        }
    }

    return score;
}

void    PlayerStatus::SaveHighScore(int score)
{
    char buf[20];
    sprintf(buf, "%d", score);

    [[NSString stringWithUTF8String:buf] writeToFile:[NSString stringWithUTF8String:GetPreferencePath2(kHighScoreFilename).c_str()] atomically:YES
                                                                           encoding:NSUTF8StringEncoding error:nil];
}

PlayerStatus::PlayerStatus()
{
    mScore = 0;
    mHighScore = LoadHighScore();
    reset();

    mLastTime = tTimer::getTimeMS();
}

void    PlayerStatus::reset()
{
    if (mScore > mHighScore)
    {
        mHighScore = mScore;
        SaveHighScore(mHighScore);
    }

    mScore = 0;
    mMultiplier = 1;
    mLives = 4;
    mScoreForExtraLife = 2000;
    mMultiplierTimeLeft = 0;
}

void    PlayerStatus::update()
{
    if (mMultiplier > 1)
    {
        mMultiplierTimeLeft -= float(tTimer::getTimeMS() - mLastTime) / 1000.0f;

        if (mMultiplierTimeLeft <= 0)
        {
            mMultiplierTimeLeft = kMultiplierExpiryTime;
            resetMultiplier();
        }
    }

    mLastTime = tTimer::getTimeMS();
}

void    PlayerStatus::addPoints(int basePoints)
{
    if (!PlayerShip::getInstance()->getIsDead())
    {
        mScore += basePoints * mMultiplier;
        while (mScore >= mScoreForExtraLife)
        {
            mScoreForExtraLife += 2000;
            mLives++;
        }
    }
}

void    PlayerStatus::increaseMultiplier()
{
    if (!PlayerShip::getInstance()->getIsDead())
    {
        mMultiplierTimeLeft = kMultiplierExpiryTime;

        if (mMultiplier < kMaxMultiplier)
        {
            mMultiplier++;
        }
    }
}

void    PlayerStatus::resetMultiplier()
{
    mMultiplier = 1;
}

void    PlayerStatus::removeLife()
{
    mLives--;
}

int     PlayerStatus::getLives() const
{
    return mLives;
}

int     PlayerStatus::getScore() const
{
    return mScore;
}

int     PlayerStatus::getHighScore() const
{
    return mHighScore;
}

int     PlayerStatus::getMultiplier() const
{
    return mMultiplier;
}

bool    PlayerStatus::getIsGameOver() const
{
    return mLives == 0;
}

