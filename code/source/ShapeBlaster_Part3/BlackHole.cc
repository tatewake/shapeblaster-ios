#include "Utility/package.h"
#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

BlackHole::BlackHole(const tVector2f& position)
:   mHitPoints(10)
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

