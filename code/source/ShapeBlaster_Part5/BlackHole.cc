#include "Utility/package.h"
#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

BlackHole::BlackHole(const tVector2f& position)
:   mHitPoints(10),
    mSprayAngle(0)
{
    mImage = Art::getInstance()->getBlackHole();
    mPosition = position;
    mRadius = mImage->getSurfaceSize().width / 2.0f;
    mKind = kBlackHole;
}

void BlackHole::update()
{
    std::list<Entity*> entities = EntityManager::getInstance()->getNearbyEntities(mPosition, 250);

    for(std::list<Entity*>::iterator iter = entities.begin(); iter != entities.end(); iter++)
    {
        if ((*iter)->getKind() == kEnemy && !((Enemy*)(*iter))->getIsActive())
        {
            //Do nothing
        }
        else if ((*iter)->getKind() == kBullet)
        {
            tVector2f temp = ((*iter)->getPosition() - mPosition);
            (*iter)->setVelocity((*iter)->getVelocity() + temp.normalize() * 0.3f);
        }
        else
        {
            tVector2f dPos = mPosition - (*iter)->getPosition();
            float length = dPos.length();

            (*iter)->setVelocity((*iter)->getVelocity() + dPos.normalize() * tMath::mix(2.0f, 0.0f, length / 250.0f));
        }
    }


    // The black holes spray some orbiting particles. The spray toggles on and off every quarter second.
    if ((tTimer::getTimeMS() / 250) % 2 == 0)
    {
        tVector2f sprayVel = MathUtil::fromPolar(mSprayAngle, Extensions::nextFloat(12, 15));
        tColor4f color = ColorUtil::HSVToColor(5, 0.5f, 0.8f);
        tVector2f pos = mPosition + 2.0f * tVector2f(sprayVel.y, -sprayVel.x) + Extensions::nextVector2(4, 8);
        ParticleState state(sprayVel, ParticleState::kEnemy, 1.0f);

        GameRoot::getInstance()->getParticleManager()->createParticle(Art::getInstance()->getLineParticle(), pos, color, 190, 1.5f, state);
    }

    // rotate the spray direction
    mSprayAngle -= tMath::PI * 2.0f / 50.0f;

    GameRoot::getInstance()->getGrid()->applyImplosiveForce((float)sinf(mSprayAngle / 2.0f) * 10 + 20, mPosition, 200);
}

void BlackHole::draw(tSpriteBatch* spriteBatch)
{
    
    // make the size of the black hole pulsate
    float scale = 1.0f + 0.1f * sinf(tTimer::getTimeMS() * 10.0f / 1000.0f);
    spriteBatch->draw(1, mImage, tPoint2f((int32_t)mPosition.x, (int32_t)mPosition.y), tOptional<tRectf>(), mColor,
                      mOrientation, getSize() / 2.0f, tVector2f(scale));
}

void BlackHole::wasShot()
{
    mHitPoints--;
    if (mHitPoints <= 0)
    {
        mIsExpired = true;

        PlayerStatus::getInstance()->addPoints(5);
        PlayerStatus::getInstance()->increaseMultiplier();
    }

    float hue = fmodf(3.0f / 1000.0f * tTimer::getTimeMS(), 6);
    tColor4f color = ColorUtil::HSVToColor(hue, 0.25f, 1);
    const int numParticles = 150;
    float startOffset = Extensions::nextFloat(0, tMath::PI * 2.0f / numParticles);

    for (int i = 0; i < numParticles; i++)
    {
        tVector2f sprayVel = MathUtil::fromPolar(tMath::PI * 2.0f * i / numParticles + startOffset, Extensions::nextFloat(8, 16));
        tVector2f pos = mPosition + 2.0f * sprayVel;
        ParticleState state(sprayVel, ParticleState::kIgnoreGravity, 1.0f);

        GameRoot::getInstance()->getParticleManager()->createParticle(Art::getInstance()->getLineParticle(), pos, color, 90, 1.5f, state);
    }
    

    tSound* temp = Sound::getInstance()->getExplosion();

    if (!temp->isPlaying())
    {
        temp->play(0, 1);
    }
}

void BlackHole::kill()
{
    mHitPoints = 0;
    wasShot();
}

