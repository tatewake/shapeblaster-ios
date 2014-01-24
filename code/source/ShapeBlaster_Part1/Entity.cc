#include "Utility/package.h"

#include "Entity.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

Entity::Entity()
:   mImage(NULL),
mColor(1,1,1,1),
mPosition(0,0),
mVelocity(0,0),
mOrientation(0),
mRadius(20),
mIsExpired(false),
mKind(kDontCare)
{
}

Entity::~Entity()
{

}

tDimension2f Entity::getSize() const
{
    return (mImage == NULL) ? tDimension2f(0,0) : mImage->getSurfaceSize();
}

void Entity::draw(tSpriteBatch* spriteBatch)
{
    spriteBatch->draw(1, mImage, tPoint2f((int32_t)mPosition.x, (int32_t)mPosition.y), tOptional<tRectf>(), mColor,
                     mOrientation, getSize() / 2, tVector2f(1,1));
}

tPoint2f Entity::getPosition() const
{
    return mPosition;
}

tVector2f Entity::getVelocity() const
{
    return mVelocity;
}

void Entity::setVelocity(const tVector2f& nv)
{
    mVelocity = nv;
}

float    Entity::getRadius() const
{
    return mRadius;
}

bool Entity::isExpired() const
{
    return mIsExpired;
}

Entity::Kind Entity::getKind() const
{
    return mKind;
}

void Entity::setExpired()
{
    mIsExpired = true;
}
