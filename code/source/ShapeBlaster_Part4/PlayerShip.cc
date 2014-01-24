#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

const int PlayerShip::kCooldownFrames = 6;

void PlayerShip::MakeExhaustFire()
{
    if (mVelocity.lengthSquared() > 0.1f)
    {
        mOrientation = Extensions::toAngle(mVelocity);

        float cosA = cosf(mOrientation);
        float sinA = sinf(mOrientation);
        tMatrix2x2f rot(tVector2f(cosA, sinA),
                        tVector2f(-sinA, cosA));

        float t = tTimer::getTimeMS() / 1000.0f;

        tVector2f baseVel = Extensions::scaleTo(mVelocity, -3);

        tVector2f perpVel = tVector2f(baseVel.y, -baseVel.x) * (0.6f * (float)sinf(t * 10.0f));
        tColor4f sideColor(0.78f, 0.15f, 0.04f, 1);
        tColor4f midColor(1.0f, 0.73f, 0.12f, 1);
        tVector2f pos = mPosition + rot * tVector2f(-25, 0);	// position of the ship's exhaust pipe.
        const float alpha = 0.7f;

        // middle particle stream
        tVector2f velMid = baseVel + Extensions::nextVector2(0, 1);
        GameRoot::getInstance()->getParticleManager()->createParticle(Art::getInstance()->getLineParticle(),
                                                                      pos, tColor4f(1,1,1,1) * alpha, 60.0f, tVector2f(0.5f, 1),
                                                                      ParticleState(velMid, ParticleState::kEnemy));
        GameRoot::getInstance()->getParticleManager()->createParticle(Art::getInstance()->getGlow(), pos, midColor * alpha, 60.0f, tVector2f(0.5f, 1),
                                                                      ParticleState(velMid, ParticleState::kEnemy));

        // side particle streams
        tVector2f vel1 = baseVel + perpVel + Extensions::nextVector2(0, 0.3f);
        tVector2f vel2 = baseVel - perpVel + Extensions::nextVector2(0, 0.3f);
        GameRoot::getInstance()->getParticleManager()->createParticle(Art::getInstance()->getLineParticle(),
                                                                      pos, tColor4f(1,1,1,1) * alpha, 60.0f, tVector2f(0.5f, 1),
                                                                      ParticleState(vel1, ParticleState::kEnemy));
        GameRoot::getInstance()->getParticleManager()->createParticle(Art::getInstance()->getLineParticle(),
                                                                      pos, tColor4f(1,1,1,1) * alpha, 60.0f, tVector2f(0.5f, 1),
                                                                      ParticleState(vel2, ParticleState::kEnemy));

        GameRoot::getInstance()->getParticleManager()->createParticle(Art::getInstance()->getGlow(),
                                                                      pos, sideColor * alpha, 60.0f, tVector2f(0.5f, 1),
                                                                      ParticleState(vel1, ParticleState::kEnemy));
        GameRoot::getInstance()->getParticleManager()->createParticle(Art::getInstance()->getGlow(),
                                                                      pos, sideColor * alpha, 60.0f, tVector2f(0.5f, 1),
                                                                      ParticleState(vel2, ParticleState::kEnemy));
    }
}

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

        MakeExhaustFire();

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

    tColor4f explosionColor = tColor4f(0.8f, 0.8f, 0.4f, 1.0f);

    for (int i = 0; i < 1200; i++)
    {
        float speed = 18.0f * (1.0f - 1 / Extensions::nextFloat(1.0f, 10.0f));
        tColor4f color = Extensions::colorLerp(tColor4f(1,1,1,1), explosionColor, Extensions::nextFloat(0, 1));
        ParticleState state(Extensions::nextVector2(speed, speed), ParticleState::kNone, 1);

        GameRoot::getInstance()->getParticleManager()->createParticle(Art::getInstance()->getLineParticle(), mPosition, color, 190, 1.5f, state);
    }
}

