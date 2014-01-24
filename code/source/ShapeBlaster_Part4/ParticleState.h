#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class Particle;

class ParticleState
{
public:
    enum ParticleType
    {
        kNone = 0,
        kEnemy,
        kBullet,
        kIgnoreGravity
    };

public:
    tVector2f       mVelocity;
    ParticleType    mType;
    float           mLengthMultiplier;

public:
    ParticleState();
    ParticleState(const tVector2f& velocity, ParticleType type, float lengthMultiplier = 1.0f);

    ParticleState   getRandom(float minVel, float maxVel);
    void            updateParticle(Particle& particle);
};

