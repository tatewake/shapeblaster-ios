#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

void Enemy::AddBehaviour(Behavior b)
{
    mBehaviors.push_back(b);
}

void Enemy::ApplyBehaviours()
{
    std::list<Behavior>::iterator iter, iterNext;

    iter = mBehaviors.begin();
    iterNext = iter;

    while (iter != mBehaviors.end())
    {
        iterNext++;

        bool result = false;

        switch (*iter)
        {
            case kFollow: result = followPlayer(0.9f); break;
            case kMoveRandom: result = moveRandomly(); break;
        }

        if (!result)
        {
            mBehaviors.erase(iter);
        }

        iter = iterNext;
    }
}

Enemy::Enemy(tTexture* image, const tVector2f& position)
:   mPointValue(1),
mTimeUntilStart(60)
{
    mImage = image;
    mPosition = position;
    mRadius = image->getSurfaceSize().width / 2.0f;
    mColor = tColor4f(0,0,0,0);
    mKind = kEnemy;
}

void Enemy::update()
{
    if (mTimeUntilStart <= 0)
    {
        ApplyBehaviours();
    }
    else
    {
        mTimeUntilStart--;
        mColor = tColor4f(1,1,1,1) * (1.0f - (float)mTimeUntilStart / 60.0f);
    }

    mPosition += mVelocity;
    mPosition = tVector2f(tMath::clamp(mPosition.x, getSize().width / 2.0f, GameRoot::getInstance()->getViewportSize().width - getSize().width / 2.0f),
                          tMath::clamp(mPosition.y, getSize().height / 2.0f, GameRoot::getInstance()->getViewportSize().height - getSize().height / 2.0f));

    mVelocity *= 0.8f;
}

void Enemy::draw(tSpriteBatch* spriteBatch)
{
    if (mTimeUntilStart > 0)
    {
        float factor = mTimeUntilStart / 60.0f;
        spriteBatch->draw(1, mImage, tPoint2f((int32_t)mPosition.x, (int32_t)mPosition.y), tOptional<tRectf>(), tColor4f(factor),
                         mOrientation, getSize() / 2.0f, tVector2f(2.0f - factor));
    }

    Entity::draw(spriteBatch);
}

bool Enemy::getIsActive()
{
    return mTimeUntilStart <= 0;
}

int Enemy::getPointValue()
{
    return mPointValue;
}

Enemy* Enemy::createSeeker(const tVector2f& position)
{
    Enemy* enemy = new Enemy(Art::getInstance()->getSeeker(), position);

    enemy->AddBehaviour(kFollow);
    enemy->mPointValue = 2;

    return enemy;
}

Enemy* Enemy::createWanderer(const tVector2f& position)
{
    Enemy* enemy = new Enemy(Art::getInstance()->getWanderer(), position);

    enemy->mRandomDirection = tMath::random() * tMath::PI * 2.0f;
    enemy->mRandomState = 0;
    enemy->AddBehaviour(kMoveRandom);

    return enemy;
}

void Enemy::handleCollision(Enemy* other)
{
    tVector2f d = mPosition - other->mPosition;
    
    mVelocity += 10.0f * d / (d.lengthSquared() + 1.0f);
}

void Enemy::wasShot()
{
    mIsExpired = true;

    PlayerStatus::getInstance()->addPoints(mPointValue);
    PlayerStatus::getInstance()->increaseMultiplier();


//TODO: ShapeBlaster fmod
    float hue1 = Extensions::nextFloat(0, 6);
    float hue2 = fmodf(hue1 + Extensions::nextFloat(0, 2), 6.0f);
    tColor4f color1 = ColorUtil::HSVToColor(hue1, 0.5f, 1);
    tColor4f color2 = ColorUtil::HSVToColor(hue2, 0.5f, 1);

    for (int i = 0; i < 120; i++)
    {
        float speed = 18.0f * (1.0f - 1 / Extensions::nextFloat(1, 10));
        ParticleState state(Extensions::nextVector2(speed, speed), ParticleState::kEnemy, 1);

        tColor4f color = Extensions::colorLerp(color1, color2, Extensions::nextFloat(0, 1));
        GameRoot::getInstance()->getParticleManager()->createParticle(Art::getInstance()->getLineParticle(), mPosition, color, 190, 1.5f, state);
    }
    
    tSound* temp = Sound::getInstance()->getExplosion();

    if (!temp->isPlaying())
    {
        temp->play(0, 1);
    }
}

bool Enemy::followPlayer(float acceleration)
{
    if (!PlayerShip::getInstance()->getIsDead())
    {
        tVector2f temp = (PlayerShip::getInstance()->getPosition() - mPosition);
        temp = temp * (acceleration / temp.length());
        mVelocity += temp;
    }

    if (mVelocity != tVector2f(0,0))
    {
        mOrientation = atan2f(mVelocity.y, mVelocity.x);
    }

    return true;
}

bool Enemy::moveRandomly()
{
    if (mRandomState == 0)
    {
        mRandomDirection += tMath::random() * 0.2f - 0.1f;
    }

    mVelocity += 0.4f * tVector2f(cosf(mRandomDirection), sinf(mRandomDirection));
    mOrientation -= 0.05f;

    tRectf bounds        = tRectf(0,0, GameRoot::getInstance()->getViewportSize());
    bounds.location.x   -= -mImage->getSurfaceSize().width  / 2.0f - 1.0f;
    bounds.location.y   -= -mImage->getSurfaceSize().height / 2.0f - 1.0f;
    bounds.size.width   += 2.0f * (-mImage->getSurfaceSize().width  / 2.0f - 1.0f);
    bounds.size.height  += 2.0f * (-mImage->getSurfaceSize().height / 2.0f - 1.0f);

    if (!bounds.contains(tPoint2f((int32_t)mPosition.x, (int32_t)mPosition.y)))
    {
        tVector2f temp  = tVector2f(GameRoot::getInstance()->getViewportSize().x, GameRoot::getInstance()->getViewportSize().y) / 2.0f;
        temp -= mPosition;
        mRandomDirection = atan2f(temp.y, temp.x) + tMath::random() * tMath::PI - tMath::PI / 2.0f;
    }

    mRandomState = (mRandomState + 1) % 6;

    return true;
}

