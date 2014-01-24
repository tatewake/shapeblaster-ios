#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class Particle
{
public:
	ParticleState   mState;
	tColor4f        mColor;
	tVector2f       mPosition;
	tVector2f       mScale;
	tTexture*       mTexture;
	float           mOrientation;
	float           mDuration;
	float           mPercentLife;

public:
	Particle()
	:   mScale(1,1),
		mPercentLife(1.0f) { }
};
