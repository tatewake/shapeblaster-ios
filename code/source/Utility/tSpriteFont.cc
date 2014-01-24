#include "Utility/package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

tTextSheet::tTextSheet(const tRectf& newSrcRect, const tDimension2f& newSpriteSize, const tDimension2f& newTextSpacing, char firstChar, char lastChar)
: mSrcRect(newSrcRect), mSpriteSize(newSpriteSize), mTextSpacing(newTextSpacing), mFirstChar(firstChar), mLastChar(lastChar)
{
    assert(firstChar < lastChar);
    assert(newTextSpacing.width > 0 && newTextSpacing.height > 0);
}

tDimension2f tTextSheet::getTextSize(const std::string& message) const
{
    uint32_t maxCols = 1;    // Maximum number of columns of all rows
    uint32_t curCols = 0;    // Current number of columns in this line
    uint32_t numRows = 1;    // Number of lines
    size_t i, size;

    size = message.length();

    for (i = 0; i < size; i++)
    {
        curCols++;

        if (message[i] == '\n')
        {
            if (curCols > maxCols)
            {
                maxCols = curCols - 1;
            }

            curCols = 0;
            numRows++;
        }
    }

    if (curCols > maxCols)
    {
        maxCols = curCols;
    }

    //TODO: Casting really a good idea here?
    return tDimension2f((int32_t)maxCols * mTextSpacing.width, (int32_t)numRows * mTextSpacing.height);
}


tSpriteFont::tSpriteFont(tTexture* t, const tTextSheet& newSheet)
:   mTexture(t),
    mTextSheet(newSheet)
{
}

tTexture* tSpriteFont::getTexture() const
{
    return mTexture;
}

tDimension2f tSpriteFont::getTextSize(const std::string& message) const
{
    return mTextSheet.getTextSize(message);
}

