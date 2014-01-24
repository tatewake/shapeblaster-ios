#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class PointMass
{
protected:
    tVector3f   mAcceleration;
    float       mDamping;

public:
    tVector3f   mPosition;
    tVector3f   mVelocity;
    float       mInverseMass;

public:
    PointMass();
    PointMass(const tVector3f& position, float invMass);

    void applyForce(const tVector3f& force);
    void increaseDamping(float factor);
    void update();
};

class Spring
{
public:
    PointMass*  mEnd1;
    PointMass*  mEnd2;
    float       mTargetLength;
    float       mStiffness;
    float       mDamping;

public:
    Spring(PointMass* end1, PointMass* end2, float stiffness, float damping);

    void update();
};

class Grid
{
public:
    std::vector<Spring> mSprings;
    PointMass*          mPoints;
    tVector2f           mScreenSize;
    int                 mCols;
    int                 mRows;

protected:
    void SetPointMass(PointMass* array, int x, int y, const PointMass& val);
    PointMass* GetPointMass(PointMass* array, int x, int y);

public:
    Grid(const tRectf& rect, const tVector2f& spacing);

    void applyDirectedForce(const tVector2f& force, const tVector2f& position, float radius);
    void applyDirectedForce(const tVector3f& force, const tVector3f& position, float radius);
    void applyImplosiveForce(float force, const tVector2f& position, float radius);
    void applyImplosiveForce(float force, const tVector3f& position, float radius);
    void applyExplosiveForce(float force, const tVector2f& position, float radius);
    void applyExplosiveForce(float force, const tVector3f& position, float radius);

    void update();

    void draw(tSpriteBatch* spriteBatch);

    tVector2f toVec2(const tVector3f& v);
};

