#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class ParticleState;

class ParticleManager
{
protected:
    class CircularParticleArray
    {
    protected:
        std::vector<Particle>   mList;
        size_t                     mStart;
        size_t                     mCount;

    public:
        CircularParticleArray(int capacity)
        {
            mList.resize((size_t)capacity);
        }

        size_t  getStart()          { return mStart; }
        void    setStart(size_t value) { mStart = value % mList.size(); }
        size_t  getCount() { return mCount; }
        void    setCount(size_t value) { mCount = value; }
        size_t  getCapacity() { return mList.size(); }

        Particle& operator [](const size_t i)
        {
            return mList[(mStart + i) % mList.size()];
        }

        const Particle& operator [](const size_t i) const
        {
            return mList[(mStart + i) % mList.size()];
        }
    };

protected:
    CircularParticleArray   mParticleList;

protected:
    void Swap(CircularParticleArray& list, size_t index1, size_t index2) const;

public:
    ParticleManager(int capacity);
    void update();
    void draw(tSpriteBatch* spriteBatch);

    void createParticle(tTexture* texture, const tVector2f& position, const tColor4f& tint, float duration, float scale, const ParticleState& state, float theta = 0);
    void createParticle(tTexture* texture, const tVector2f& position, const tColor4f& tint, float duration, const tVector2f& scale, const ParticleState& state, float theta = 0);

    void clear();
    size_t getParticleCount();
};

