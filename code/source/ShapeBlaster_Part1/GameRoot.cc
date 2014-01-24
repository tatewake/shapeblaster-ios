#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

GameRoot* gApp = GameRoot::getInstance();

GameRoot::GameRoot()
:   mViewportSize(800, 600),
    mSpriteBatch(NULL)
{
}

tDimension2f GameRoot::getViewportSize()
{
    return mViewportSize;
}

void GameRoot::onInitView()
{
    Art::getInstance();
    Sound::getInstance();

    EntityManager::getInstance()->add(PlayerShip::getInstance());

    Sound::getInstance()->getMusic()->play(0, (uint32_t)-1);

    mViewport       = new tAutosizeViewport(mViewportSize);
    mSpriteBatch    = new tSpriteBatch;

    mSpriteBatch->setProjection(tMatrix4x4f::ortho(0,mViewportSize.width, mViewportSize.height, 0));

    glClearColor(0,0,0,1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glHint(GL_GENERATE_MIPMAP_HINT, GL_DONT_CARE);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void GameRoot::onRedrawView(float time)
{
#pragma unused(time)
    Input::getInstance()->update();

    EntityManager::getInstance()->update();

    EntityManager::getInstance()->draw(mSpriteBatch);

    mSpriteBatch->draw(0, Art::getInstance()->getPointer(), Input::getInstance()->getMousePosition(), tOptional<tRectf>());

//Run redraw logic here
    mViewport->run();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mSpriteBatch->end();

    glFlush();
}

