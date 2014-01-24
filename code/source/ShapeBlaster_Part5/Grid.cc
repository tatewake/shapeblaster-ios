#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

PointMass::PointMass()
:   mAcceleration(0,0,0),
    mDamping(0.98f),
    mPosition(0),
    mVelocity(0,0,0),
    mInverseMass(0)
{
}

PointMass::PointMass(const tVector3f& position, float invMass)
:   mAcceleration(0,0,0),
    mDamping(0.98f),
    mPosition(position),
    mVelocity(0,0,0),
    mInverseMass(invMass)
{

}

void PointMass::applyForce(const tVector3f& force)
{
    mAcceleration += force * mInverseMass;
}

void PointMass::increaseDamping(float factor)
{
    mDamping *= factor;
}

void PointMass::update()
{
    mVelocity += mAcceleration;
    mPosition += mVelocity;
    mAcceleration = tVector3f(0,0,0);
    if (mVelocity.lengthSquared() < 0.001f * 0.001f)
    {
        mVelocity = tVector3f(0,0,0);
    }

    mVelocity *= mDamping;
    mDamping = 0.98f;
}

Spring::Spring(PointMass* end1, PointMass* end2, float stiffness, float damping)
:   mEnd1(end1),
    mEnd2(end2),
    mTargetLength(mEnd1->mPosition.distance(mEnd2->mPosition) * 0.95f),
    mStiffness(stiffness),
    mDamping(damping)
{
}

void Spring::update()
{
    tVector3f x = mEnd1->mPosition - mEnd2->mPosition;

    float length = x.length();

    if (length > mTargetLength)
    {
        x = (x / length) * (length - mTargetLength);
        tVector3f dv = mEnd2->mVelocity - mEnd1->mVelocity;
        tVector3f force = mStiffness * x - dv * mDamping;

        mEnd1->applyForce(-force);
        mEnd2->applyForce(force);
    }
}

void Grid::SetPointMass(PointMass* array, int x, int y, const PointMass& val)
{
    array[y * mCols + x] = val;
}

PointMass* Grid::GetPointMass(PointMass* array, int x, int y)
{
    return &array[y * mCols + x];
}

Grid::Grid(const tRectf& rect, const tVector2f& spacing)
{
    mScreenSize = tVector2f(GameRoot::getInstance()->getViewportSize().width, GameRoot::getInstance()->getViewportSize().height);

    int numColumns = (int)((float)rect.size.width / spacing.x) + 1;
    int numRows = (int)((float)rect.size.height / spacing.y) + 1;

    mPoints = new PointMass[numColumns * numRows];
    mCols = numColumns;
    mRows = numRows;

    PointMass* fixedPoints = new PointMass[numColumns * numRows];

    int column = 0, row = 0;
    for (float y = rect.location.y; y <= rect.location.y + rect.size.height; y += spacing.y)
    {
        for (float x = rect.location.x; x <= rect.location.x + rect.size.width; x += spacing.x)
        {
            SetPointMass(mPoints, column, row, PointMass(tVector3f(x, y, 0), 1));
            SetPointMass(fixedPoints, column, row, PointMass(tVector3f(x, y, 0), 0));
            column++;
        }
        row++;
        column = 0;
    }

    // link the point masses with springs
    for (int y = 0; y < numRows; y++)
    {
        for (int x = 0; x < numColumns; x++)
        {
            if (x == 0 || y == 0 || x == numColumns - 1 || y == numRows - 1)
            {
                mSprings.push_back(Spring(GetPointMass(fixedPoints, x, y), GetPointMass(mPoints, x, y), 0.1f, 0.1f));
            }
            else if (x % 3 == 0 && y % 3 == 0)
            {
                mSprings.push_back( Spring(GetPointMass(fixedPoints, x, y), GetPointMass(mPoints, x, y), 0.002f, 0.02f));
            }

            if (x > 0)
            {
                mSprings.push_back(Spring(GetPointMass(mPoints, x - 1, y), GetPointMass(mPoints, x, y), 0.28f, 0.06f));
            }

            if (y > 0)
            {
                mSprings.push_back(Spring(GetPointMass(mPoints, x, y - 1), GetPointMass(mPoints, x, y), 0.28f, 0.06f));
            }
        }
    }
}

void Grid::applyDirectedForce(const tVector2f& force, const tVector2f& position, float radius)
{
    applyDirectedForce(tVector3f(force.x, force.y, 0), tVector3f(position.x, position.y, 0), radius);
}

void Grid::applyDirectedForce(const tVector3f& force, const tVector3f& position, float radius)
{
    for(int i = 0; i < mCols * mRows; i++)
    {
        if (position.distanceSquared(mPoints[i].mPosition) < radius * radius)
        {
            mPoints[i].applyForce(10.0f * force / (10 + position.distance(mPoints[i].mPosition)));
        }
    }
}

void Grid::applyImplosiveForce(float force, const tVector2f& position, float radius)
{
    applyImplosiveForce(force, tVector3f(position.x, position.y, 0), radius);
}

void Grid::applyImplosiveForce(float force, const tVector3f& position, float radius)
{
    for (int i = 0; i < mCols * mRows; i++)
    {
        float dist2 = position.distanceSquared(mPoints[i].mPosition);
        if (dist2 < radius * radius)
        {
            mPoints[i].applyForce(10.0f * force * (position - mPoints[i].mPosition) / (100 + dist2));
            mPoints[i].increaseDamping(0.6f);
        }
    }
}

void Grid::applyExplosiveForce(float force, const tVector2f& position, float radius)
{
    applyExplosiveForce(force, tVector3f(position.x, position.y, 0), radius);
}

void Grid::applyExplosiveForce(float force, const tVector3f& position, float radius)
{
    for (int i = 0; i < mCols * mRows; i++)
    {
        float dist2 = position.distanceSquared(mPoints[i].mPosition);
        if (dist2 < radius * radius)
        {
            mPoints[i].applyForce(100 * force * (mPoints[i].mPosition - position) / (10000 + dist2));
            mPoints[i].increaseDamping(0.6f);
        }
    }
}

void Grid::update()
{
    for(size_t i = 0; i < mSprings.size(); i++)
    {
        mSprings[i].update();
    }

    for(int i = 0; i < mCols * mRows; i++)
    {
        mPoints[i].update();
    }
}

void Grid::draw(tSpriteBatch* spriteBatch)
{

    int width = mCols;
    int height = mRows;
    tColor4f color(0.12f, 0.12f, 0.55f, 0.33f);

    for (int y = 1; y < height; y++)
    {
        for (int x = 1; x < width; x++)
        {
            tVector2f left, up;
            tVector2f p = toVec2(GetPointMass(mPoints, x, y)->mPosition);
            if (x > 1)
            {
                left = toVec2(GetPointMass(mPoints, x - 1, y)->mPosition);
                float thickness = (y % 3 == 1) ? 3.0f : 1.0f;

                int clampedX = (int)tMath::min(x + 1, width - 1);
                tVector2f mid = MathUtil::catmullRom(toVec2(GetPointMass(mPoints, x - 2, y)->mPosition), left, p, toVec2(GetPointMass(mPoints, clampedX, y)->mPosition), 0.5f);

                if (mid.distanceSquared((left + p) / 2) > 1)
                {
                    Extensions::drawLine(spriteBatch, left, mid, color, thickness);
                    Extensions::drawLine(spriteBatch, mid, p, color, thickness);
                }
                else
                {
                    Extensions::drawLine(spriteBatch, left, p, color, thickness);
                }
            }
            if (y > 1)
            {
                up = toVec2(GetPointMass(mPoints, x, y - 1)->mPosition);

                float thickness = (x % 3 == 1) ? 3.0f : 1.0f;
                int clampedY = (int)tMath::min(y + 1, height - 1);
                tVector2f mid = MathUtil::catmullRom(toVec2(GetPointMass(mPoints, x, y - 2)->mPosition), up, p, toVec2(GetPointMass(mPoints, x, clampedY)->mPosition), 0.5f);

                if (mid.distanceSquared((up + p) / 2) > 1)
                {
                    Extensions::drawLine(spriteBatch, up, mid, color, thickness);
                    Extensions::drawLine(spriteBatch, mid, p, color, thickness);
                }
                else
                {
                    Extensions::drawLine(spriteBatch, up, p, color, thickness);
                }
            }

            if (x > 1 && y > 1)
            {
                tVector2f upLeft = toVec2(GetPointMass(mPoints, x - 1, y - 1)->mPosition);
                Extensions::drawLine(spriteBatch, 0.5f * (upLeft + up), 0.5f * (left + p), color, 1.0f);	// vertical line
                Extensions::drawLine(spriteBatch, 0.5f * (upLeft + left), 0.5f * (up + p), color, 1.0f);	// horizontal line
            }
        }
    }
}

tVector2f Grid::toVec2(const tVector3f& v)
{
    float factor = (v.z + 2000.0f) * 0.0005f;
    return (tVector2f(v.x, v.y) - mScreenSize * 0.5f) * factor + mScreenSize * 0.5f;
}

