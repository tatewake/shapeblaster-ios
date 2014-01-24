#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

ParticleState::ParticleState()
:   mVelocity(tVector2f(0,0)),
    mType(kNone),
    mLengthMultiplier(1.0f)
{
}

ParticleState::ParticleState(const tVector2f& velocity, ParticleType type, float lengthMultiplier)
:   mVelocity(velocity),
    mType(type),
    mLengthMultiplier(lengthMultiplier)
{
}

ParticleState   ParticleState::getRandom(float minVel, float maxVel)
{
    return ParticleState(Extensions::nextVector2(minVel, maxVel), kNone, 1);
}

void            ParticleState::updateParticle(Particle& particle)
{
    tVector2f vel = particle.mState.mVelocity;
    float speed = vel.length();

    // using Vector2.Add() should be slightly faster than doing "x.Position += vel;" because the Vector2s
    // are passed by reference and don't need to be copied. Since we may have to update a very large
    // number of particles, this method is a good candidate for optimizations.
    particle.mPosition += vel;

    // fade the particle if its PercentLife or speed is low.
    float alpha = tMath::min(1.0f, tMath::min(particle.mPercentLife * 2, speed * 1.0f));
    alpha *= alpha;

    particle.mColor.a = alpha;

    // the length of bullet particles will be less dependent on their speed than other particles
    if (particle.mState.mType == kBullet)
    {
        particle.mScale.x = particle.mState.mLengthMultiplier * tMath::min(tMath::min(1.0f, 0.1f * speed + 0.1f), alpha);
    }
    else
    {
        particle.mScale.x = particle.mState.mLengthMultiplier * tMath::min(tMath::min(1.0f, 0.2f * speed + 0.1f), alpha);
    }

    particle.mOrientation = Extensions::toAngle(vel);

    tVector2f pos = particle.mPosition;
    int width = (int)GameRoot::getInstance()->getViewportSize().width;
    int height = (int)GameRoot::getInstance()->getViewportSize().height;

    // collide with the edges of the screen
    if (pos.x < 0)
    {
        vel.x = (float)fabs(vel.x);
    }
    else if (pos.x > width)
    {
        vel.x = (float)-fabs(vel.x);
    }

    if (pos.y < 0)
    {
        vel.y = (float)fabs(vel.y);
    }
    else if (pos.y > height)
    {
        vel.y = (float)-fabs(vel.y);
    }

    if (particle.mState.mType != kIgnoreGravity)
    {
        for (std::list<BlackHole*>::iterator j = EntityManager::getInstance()->mBlackHoles.begin(); j != EntityManager::getInstance()->mBlackHoles.end(); j++)
        {
            tVector2f dPos = (*j)->getPosition() - pos;
            float distance = dPos.length();
            tVector2f n = dPos / distance;
            vel += 10000.0f * n / (distance * distance + 10000.0f);

            // add tangential acceleration for nearby particles
            if (distance < 400)
            {
                vel += 45.0f * tVector2f(n.y, -n.x) / (distance + 100.0f);
            }
        }
    }

    if (fabs(vel.x) + fabs(vel.y) < 0.00000000001f)
    {
        vel = tVector2f(0,0);
    }
    else if (particle.mState.mType == kEnemy)
    {
        vel *= 0.94f;
    }
    else
    {
        //TODO: ShapeBlaster fmod
        vel *= 0.96f + (float)fmod(fabs(pos.x), 0.04f);
    }

    particle.mState.mVelocity = vel;
}

