#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

void ParticleManager::Swap(typename ParticleManager::CircularParticleArray& list, size_t index1, size_t index2) const
{
    Particle temp = list[index1];
    list[index1] = list[index2];
    list[index2] = temp;
}

ParticleManager::ParticleManager(int capacity)
: mParticleList(capacity)
{

}

void ParticleManager::update()
{
    size_t removalCount = 0;

    for (size_t i = 0; i < mParticleList.getCount(); i++)
    {
        Particle& ref = mParticleList[i];
        ref.mState.updateParticle(ref);
        ref.mPercentLife -= 1.0f / ref.mDuration;

        Swap(mParticleList, i - removalCount, i);

        if (ref.mPercentLife < 0)
        {
            removalCount++;
        }
    }

    mParticleList.setCount(mParticleList.getCount() - removalCount);
}

void ParticleManager::draw(tSpriteBatch* spriteBatch)
{
    for (size_t i = 0; i < mParticleList.getCount(); i++)
    {
        Particle particle = mParticleList[(size_t)i];

        tPoint2f origin = particle.mTexture->getSurfaceSize() / 2;
        spriteBatch->draw(2, particle.mTexture, tPoint2f((int)particle.mPosition.x, (int)particle.mPosition.y), tOptional<tRectf>(),
                         particle.mColor,
                         particle.mOrientation, origin, particle.mScale);
    }
}

void ParticleManager::createParticle(tTexture* texture, const tVector2f& position, const tColor4f& tint, float duration, float scale, const ParticleState& state, float theta)
{
    createParticle(texture, position, tint, duration, tVector2f(scale), state, theta);
}

void ParticleManager::createParticle(tTexture* texture, const tVector2f& position, const tColor4f& tint, float duration, const tVector2f& scale, const ParticleState& state, float theta)
{
    size_t index;

    if (mParticleList.getCount() == mParticleList.getCapacity())
    {
        index = 0;
        mParticleList.setStart(mParticleList.getStart() + 1);
    }
    else
    {
        index = mParticleList.getCount();
        mParticleList.setCount(mParticleList.getCount() + 1);
    }

    Particle& ref = mParticleList[index];

    ref.mTexture = texture;
    ref.mPosition = position;
    ref.mColor = tint;

    ref.mDuration = duration;
    ref.mPercentLife = 1.0f;
    ref.mScale = scale;
    ref.mOrientation = theta;
    ref.mState = state;
}

void ParticleManager::clear()
{
    mParticleList.setCount(0);
}

size_t ParticleManager::getParticleCount()
{
    return mParticleList.getCount();
}

