#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class tTexture;

class tTextSheet
{
public:
    tRectf          mSrcRect;
    tDimension2f    mSpriteSize;
    tDimension2f    mTextSpacing;
    char            mFirstChar;
    char            mLastChar;

public:
    tTextSheet(const tRectf& newSrcRect, const tDimension2f& newSpriteSize, const tDimension2f& newTextSpacing, char firstChar, char lastChar);

    tDimension2f getTextSize(const std::string& message) const;
};

class tSpriteFont
{
protected:
    tTexture*   mTexture;
    tTextSheet  mTextSheet;

public:
    tSpriteFont(tTexture* t, const tTextSheet& newSheet);

    tTexture* getTexture() const;
    tDimension2f getTextSize(const std::string& message) const;

    friend class tSpriteBatch;
};
