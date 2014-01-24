#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

#include "Utility/package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

void tSpriteBatch::FourPoints(std::vector<tPoint2f>& v, const tRectf& four)
{
    v.push_back(tPoint2f(four.location.x, four.location.y));
    v.push_back(tPoint2f(four.location.x + four.size.width, four.location.y));
    v.push_back(tPoint2f(four.location.x + four.size.width, four.location.y + four.size.height));
    v.push_back(tPoint2f(four.location.x, four.location.y + four.size.height));
}

void tSpriteBatch::SixIndices(std::vector<uint16_t>& v, uint16_t start)
{
    v.push_back(start + 0);
    v.push_back(start + 2);
    v.push_back(start + 1);

    v.push_back(start + 0);
    v.push_back(start + 3);
    v.push_back(start + 2);
}

tSpriteBatch::tSpriteBatch()
:   mProjection(tMatrix4x4f::ortho(0, 2, 2, 0)),
    mDefaultProgram(NULL)
{
    std::string vert, frag;

    std::string vertPath = std::string([[[NSBundle mainBundle] resourcePath] UTF8String]) + std::string("/spritebatch.vert");
    std::string fragPath = std::string([[[NSBundle mainBundle] resourcePath] UTF8String]) + std::string("/spritebatch.frag");
    if ([[NSFileManager defaultManager] fileExistsAtPath:[NSString stringWithUTF8String:vertPath.c_str()]] &&
        [[NSFileManager defaultManager] fileExistsAtPath:[NSString stringWithUTF8String:vertPath.c_str()]])
    {
        vert = [[NSString stringWithContentsOfFile:[NSString stringWithUTF8String:vertPath.c_str()] encoding:NSUTF8StringEncoding error:nil] UTF8String];
        frag = [[NSString stringWithContentsOfFile:[NSString stringWithUTF8String:fragPath.c_str()] encoding:NSUTF8StringEncoding error:nil] UTF8String];
    }

    assert(!vert.empty() && !frag.empty());

    mDefaultProgram = new tProgram(tShader(tShader::kVertexShader, vert), tShader(tShader::kFragmentShader, frag));
}

void tSpriteBatch::setProjection(const tMatrix4x4f& newOrtho)
{
    mProjection = newOrtho;
}

void tSpriteBatch::draw(uint8_t z, tTexture* t, const tRectf& dest, const tOptional<tRectf>& src, const tColor4f& c)
{
    std::pair<uint8_t, tTexture*> key(z, t);
    Value& ref = mSteps[key];
    size_t curIndex = ref.mVerts.size();

    //Calculate position coords
    FourPoints(ref.mVerts, dest);

    //Calculate texture coords
    if (src)
    {
        tDimension2f texSize = tDimension2f(t->getSize().x, t->getSize().y);
        FourPoints(ref.mTexCoords,
                   tRectf((float)src->location.x / texSize.width,
                          (float)src->location.y / texSize.height,
                          (float)src->size.width / texSize.width,
                          (float)src->size.height / texSize.height));
    }
    else
    {
        FourPoints(ref.mTexCoords, tRectf(0, 0,
                                          (float)t->getSurfaceSize().width / (float)t->getSize().width,
                                          (float)t->getSurfaceSize().height / (float)t->getSize().height));
    }

    //Calculate colors
    ref.mColors.push_back(c); ref.mColors.push_back(c);
    ref.mColors.push_back(c); ref.mColors.push_back(c);

    //Calculate indices
    SixIndices(ref.mIndices, (uint16_t)curIndex);

}

void tSpriteBatch::draw(uint8_t z, tTexture* t, const tPoint2f& dest, const tOptional<tRectf>& src, const tColor4f& c)
{
    if (src)
    {
        draw(z, t, tRectf(dest, src->size), src, c);
    }
    else
    {
        draw(z, t, tRectf(dest, t->getSurfaceSize()), src, c);
    }
}

void tSpriteBatch::draw(uint8_t z, tTexture* t, const tRectf& dest, const tOptional<tRectf>& src, const tColor4f& c,
                             float rotz, const tPoint2f& origin)
{
    std::pair<uint8_t, tTexture*> key(z, t);
    Value& ref = mSteps[key];
    size_t curIndex = ref.mVerts.size();

    //Calculate position coords
    FourPoints(ref.mVerts, dest);

    float co = cosf(rotz);
    float s = sinf(rotz);
    tMatrix2x2f rotMatrix(tVector2f( co, -s),
                          tVector2f( s, co));

    for (size_t i = 0; i < 4; i++)
    {
        tVector2f in = ref.mVerts[curIndex + i] - tVector2f(dest.location.x, dest.location.y) - tVector2f(origin.x, origin.y);
        tVector2f out = in * rotMatrix;
        ref.mVerts[curIndex + i] = out + tVector2f(dest.location.x, dest.location.y);
    }

    //Calculate texture coords
    if (src)
    {
        tDimension2f texSize = tDimension2f(t->getSize().x, t->getSize().y);
        FourPoints(ref.mTexCoords,
                   tRectf((float)src->location.x / texSize.width,
                          (float)src->location.y / texSize.height,
                          (float)src->size.width / texSize.width,
                          (float)src->size.height / texSize.height));
    }
    else
    {
        FourPoints(ref.mTexCoords, tRectf(0, 0,
                                          (float)t->getSurfaceSize().width / (float)t->getSize().width,
                                          (float)t->getSurfaceSize().height / (float)t->getSize().height));
    }

    //Calculate colors
    ref.mColors.push_back(c); ref.mColors.push_back(c);
    ref.mColors.push_back(c); ref.mColors.push_back(c);

    //Calculate indices
    SixIndices(ref.mIndices, (uint16_t)curIndex);
}

void tSpriteBatch::draw(uint8_t z, tTexture* t, const tPoint2f& dest, const tOptional<tRectf>& src, const tColor4f& c,
                             float rotz, const tPoint2f& origin, const tVector2f& scale)
{
    tPoint2f newOrigin(int(origin.x * scale.x), int(origin.y * scale.y));

    if (src)
    {
        draw(z, t, tRectf(dest, int(src->size.x * scale.x), int(src->size.y * scale.y)), src, c, rotz, newOrigin);
    }
    else
    {
        draw(z, t, tRectf(dest, int(t->getSurfaceSize().x * scale.x), int(t->getSurfaceSize().y * scale.y)), src, c, rotz, newOrigin);
    }
}

void tSpriteBatch::drawString(uint8_t z, const tSpriteFont& f, const std::string& str, const tPoint2f& pos, const tColor4f& c)
{
    tPoint2f iterPoint = pos;
    uint32_t iter, size;
    char    theChar;
    uint8_t  maxCol = uint8_t(f.mTextSheet.mSrcRect.size.width / f.mTextSheet.mSpriteSize.width);

    size = (uint32_t)str.length();

    for(iter = 0; iter < size; iter++)
    {
        theChar = str[iter];

        if (theChar != '\n')
        {
            uint8_t index = (uint8_t)(theChar - f.mTextSheet.mFirstChar);
            uint8_t i = index % maxCol;
            uint8_t j = index / maxCol;

            assert(i < f.mTextSheet.mSrcRect.size.width / f.mTextSheet.mSpriteSize.width && j < f.mTextSheet.mSrcRect.size.height / f.mTextSheet.mSpriteSize.height);

            draw(z, f.mTexture, tPoint2f(iterPoint),
                tRectf(f.mTextSheet.mSrcRect.location.x + i * f.mTextSheet.mSpriteSize.width,
                       f.mTextSheet.mSrcRect.location.y + j * f.mTextSheet.mSpriteSize.height,
                       f.mTextSheet.mSpriteSize),
                c);

            iterPoint.x += f.mTextSheet.mTextSpacing.width;
        }
        else
        {
            iterPoint.x = pos.x;
            iterPoint.y += f.mTextSheet.mTextSpacing.height;
        }
    }
}

void tSpriteBatch::drawString(uint8_t z, const tSpriteFont& f, const std::string& str, const tPoint2f& pos, const tColor4f& c,
                                   float rotz, const tPoint2f& origin, const tVector2f& scale)
{
    tVector2f newScale = scale;

    tPoint2f iterPoint = pos;
    uint32_t iter, size;
    char    theChar;
    uint8_t  maxCol = uint8_t(f.mTextSheet.mSrcRect.size.width / f.mTextSheet.mSpriteSize.width);

    size = (uint32_t)str.length();

    for(iter = 0; iter < size; iter++)
    {
        theChar = str[iter];

        if (theChar != '\n')
        {
            uint8_t index = (uint8_t)(theChar - f.mTextSheet.mFirstChar);
            uint8_t i = index % maxCol;
            uint8_t j = index / maxCol;

            assert(i < f.mTextSheet.mSrcRect.size.width / f.mTextSheet.mSpriteSize.width && j < f.mTextSheet.mSrcRect.size.height / f.mTextSheet.mSpriteSize.height);

            draw(z, f.mTexture, pos,
                tRectf(f.mTextSheet.mSrcRect.location.x + i * f.mTextSheet.mSpriteSize.width,
                       f.mTextSheet.mSrcRect.location.y + j * f.mTextSheet.mSpriteSize.height,
                       f.mTextSheet.mSpriteSize),
                c, rotz, origin + pos - iterPoint, newScale);

            iterPoint.x += f.mTextSheet.mTextSpacing.width;
        }
        else
        {
            iterPoint.x = pos.x;
            iterPoint.y += f.mTextSheet.mTextSpacing.height;
        }
    }
}

void tSpriteBatch::end()
{

    if (!mSteps.empty())
    {
        glUseProgram(mDefaultProgram->mProgramID);

        GLint location;

        location = glGetUniformLocation(mDefaultProgram->mProgramID, "mMVP");
        assert(location != -1);

        glUniformMatrix4fv(location, 1, false, (float*)&mProjection.value[0]);

        //For each in map
        for(std::map<std::pair<uint8_t, tTexture*>, Value>::iterator iter = mSteps.begin(); iter != mSteps.end(); iter++)
        {
            if (!(*iter).second.mVerts.empty())
            {
                glActiveTexture(GL_TEXTURE0);

                glBindTexture(GL_TEXTURE_2D, (*iter).first.second->mTextureID);

                location = glGetAttribLocation(mDefaultProgram->mProgramID, "mVerts");
                assert((GLint)location != -1);

                glEnableVertexAttribArray((GLuint)location);
                glVertexAttribPointer((GLuint)location, 2, GL_FLOAT, GL_TRUE, 0, &(*iter).second.mVerts[0]);

                location = glGetAttribLocation(mDefaultProgram->mProgramID, "mTexCoords");
                assert((GLint)location != -1);

                glEnableVertexAttribArray((GLuint)location);
                glVertexAttribPointer((GLuint)location, 2, GL_FLOAT, GL_TRUE, 0, &(*iter).second.mTexCoords[0]);

                location = glGetAttribLocation(mDefaultProgram->mProgramID, "mColors");
                assert((GLint)location != -1);

                glEnableVertexAttribArray((GLuint)location);
                glVertexAttribPointer((GLuint)location, 4, GL_FLOAT, GL_TRUE, 0, &(*iter).second.mColors[0]);

                glDrawElements(GL_TRIANGLES, int32_t((*iter).second.mIndices.size()), GL_UNSIGNED_SHORT, &(*iter).second.mIndices[0]);

                (*iter).second.mVerts.clear();
                (*iter).second.mTexCoords.clear();
                (*iter).second.mColors.clear();
                (*iter).second.mIndices.clear();
            }
        }
    }
}
