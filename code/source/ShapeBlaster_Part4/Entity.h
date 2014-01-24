#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class Entity
{
public:
    enum Kind
    {
        kDontCare = 0,
        kBullet,
        kEnemy,
        kBlackHole,
    };
protected:
    tTexture*   mImage;
    tColor4f    mColor;

    tPoint2f    mPosition;
    tVector2f   mVelocity;
    float       mOrientation;
    float       mRadius;
    bool        mIsExpired;
    Kind        mKind;

public:
    Entity();
    virtual ~Entity();

    tDimension2f getSize() const;
    virtual void update() = 0;

    virtual void draw(tSpriteBatch* spriteBatch);

    tPoint2f    getPosition() const;
    tVector2f   getVelocity() const;
    void        setVelocity(const tVector2f& nv);
    float       getRadius() const;
    bool isExpired() const;
    Kind getKind() const;

    void setExpired();
};
