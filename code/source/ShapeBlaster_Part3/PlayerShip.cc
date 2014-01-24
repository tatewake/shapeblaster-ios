#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

const int PlayerShip::kCooldownFrames = 6;

PlayerShip::PlayerShip()
:   mCooldowmRemaining(0),
    mFramesUntilRespawn(0)
{
    mImage = Art::getInstance()->getPlayer();
    mPosition = tPoint2f(GameRoot::getInstance()->getViewportSize().x / 2, GameRoot::getInstance()->getViewportSize().y / 2);
    mRadius = 10;
}

void PlayerShip::update()
{
    if (getIsDead())
    {
        mFramesUntilRespawn--;
        if (mFramesUntilRespawn == 0)
        {
            if (PlayerStatus::getInstance()->getLives() == 0)
            {
                PlayerStatus::getInstance()->reset();
                mPosition = tVector2f(GameRoot::getInstance()->getViewportSize().width / 2.0f,
                                      GameRoot::getInstance()->getViewportSize().height / 2.0f);
            }
        }
    }
    else
    {
        tVector2f aim = Input::getInstance()->getAimDirection();
        if (aim.lengthSquared() > 0 && mCooldowmRemaining <= 0)
        {
            mCooldowmRemaining = kCooldownFrames;
            float aimAngle = atan2f(aim.y, aim.x);

            float cosA = cosf(aimAngle);
            float sinA = sinf(aimAngle);
            tMatrix2x2f aimMat(tVector2f(cosA, sinA),
                               tVector2f(-sinA, cosA));

            float randomSpread = tMath::random() * 0.08f + tMath::random() * 0.08f - 0.08f;
            tVector2f vel = 11.0f * (tVector2f(cosA, sinA) + tVector2f(randomSpread, randomSpread));

            tVector2f offset = aimMat * tVector2f(35, -8);
            EntityManager::getInstance()->add(new Bullet(mPosition + offset, vel));

            offset = aimMat * tVector2f(35, 8);
            EntityManager::getInstance()->add(new Bullet(mPosition + offset, vel));

            tSound* curShot = Sound::getInstance()->getShot();
            if (!curShot->isPlaying())
            {
                curShot->play(0, 1);
            }
        }

        if (mCooldowmRemaining > 0)
        {
            mCooldowmRemaining--;
        }

        const float kSpeed = 8;
        mVelocity += kSpeed * Input::getInstance()->getMovementDirection();
        mPosition += mVelocity;
        mPosition = tVector2f(tMath::clamp(mPosition.x, (float)getSize().x / 2.0f, (float)GameRoot::getInstance()->getViewportSize().x - getSize().x / 2),
                              tMath::clamp(mPosition.y, (float)getSize().y / 2.0f, (float)GameRoot::getInstance()->getViewportSize().y - getSize().y / 2));
        
        if (mVelocity.lengthSquared() > 0)
        {
            mOrientation = atan2f(mVelocity.y, mVelocity.x);
        }

        mVelocity = tVector2f(0);
    }
}

void PlayerShip::draw(tSpriteBatch* spriteBatch)
{
    if (!getIsDead())
    {
        Entity::draw(spriteBatch);
    }
}

bool PlayerShip::getIsDead()
{
    return mFramesUntilRespawn > 0;
}

void PlayerShip::kill()
{
    PlayerStatus::getInstance()->removeLife();
    mFramesUntilRespawn = PlayerStatus::getInstance()->getIsGameOver() ? 300 : 120;
}

