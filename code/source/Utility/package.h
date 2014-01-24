#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

//Debugging
#if DEBUG
#include <assert.h>
#else
#ifdef assert
#undef assert
#endif
#define assert(x) { }
#endif

//Some standard headers from C and C++
#include <math.h>
#include <list>
#include <vector>
#include <string>
#include <map>
#include <vector>
#include <bitset>

//OpenGL-specific
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#define glDepthRange glDepthRangef

//Patterns
#include "tSingleton.h"
#include "tOptional.h"

//Math
#include "tMath.h"
#include "tVector.h"
#include "tMatrix.h"
#include "tRect.h"

//System Time, Input, and Audio
#include "tTimer.h"
#include "tInputEvent.h"
#include "tSound.h"

//OpenGL helper classes
#include "tSurface.h"
#include "tTexture.h"
#include "tShader.h"
#include "tProgram.h"

//Advanced OpenGL Helper classes
#include "tViewport.h"
#include "tAutosizeViewport.h"
#include "tSpriteFont.h"
#include "tSpriteBatch.h"
