#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class Enemy
:   public Entity
{
public:
    enum Behavior
    {
        kFollow = 0,
        kMoveRandom,
    };

protected:
    std::list<Behavior> mBehaviors;
    float               mRandomDirection;
    int                 mRandomState;
    int                 mPointValue;
    int                 mTimeUntilStart;

protected:
    void AddBehaviour(Behavior b);
    void ApplyBehaviours();

public:
    Enemy(tTexture* image, const tVector2f& position);

    void update();

    bool getIsActive();
    int getPointValue();

    static Enemy* createSeeker(const tVector2f& position);
    static Enemy* createWanderer(const tVector2f& position);

    void handleCollision(Enemy* other);
    void wasShot();

    bool followPlayer(float acceleration);
    bool moveRandomly();
};

