#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class tSpriteBatch
{
public:
    class Value
    {
    public:
        std::vector<tPoint2f>       mVerts;
        std::vector<tTexCoord2f>    mTexCoords;
        std::vector<tColor4f>       mColors;
        std::vector<uint16_t>       mIndices;

    public:
        Value() { }
    };

protected:
    std::map<std::pair<uint8_t, tTexture*>, Value> mSteps;
    tMatrix4x4f mProjection;
    tProgram*   mDefaultProgram;

protected:
    void FourPoints(std::vector<tPoint2f>& v, const tRectf& four);
    void SixIndices(std::vector<uint16_t>& v, uint16_t start);

public:
    tSpriteBatch();
    virtual ~tSpriteBatch() { }

    void setProjection(const tMatrix4x4f& newOrtho);

    void draw(uint8_t z, tTexture* t, const tRectf& dest, const tOptional<tRectf>& src, const tColor4f& c = tColor4f(1,1,1,1));
    void draw(uint8_t z, tTexture* t, const tPoint2f& dest, const tOptional<tRectf>& src, const tColor4f& c = tColor4f(1,1,1,1)); //x
    void draw(uint8_t z, tTexture* t, const tRectf& dest, const tOptional<tRectf>& src, const tColor4f& c,
             float rotz, const tPoint2f& origin);
    void draw(uint8_t z, tTexture* t, const tPoint2f& dest, const tOptional<tRectf>& src, const tColor4f& c,
             float rotz, const tPoint2f& origin, const tVector2f& scale); //x

    void drawString(uint8_t z, const tSpriteFont& f, const std::string& str, const tPoint2f& pos, const tColor4f& c = tColor4f(1,1,1,1));
    void drawString(uint8_t z, const tSpriteFont& f, const std::string& str, const tPoint2f& pos, const tColor4f& c,
                   float rotz, const tPoint2f& origin, const tVector2f& scale);

    void end();
};

