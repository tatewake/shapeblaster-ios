#include "Utility/package.h"

#include "package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

GameRoot* gApp = GameRoot::getInstance();

#define kScale 3.0f
void GameRoot::DrawRightAlignedString(const std::string& str, int32_t y)
{
    int32_t textWidth = int32_t(Art::getInstance()->getFont().getTextSize(str).width * kScale);
    mSpriteBatch->drawString(1, Art::getInstance()->getFont(), str, tPoint2f(mViewportSize.width - textWidth - 5, y), tColor4f(1,1,1,1),
                            0, tPoint2f(0,0), tVector2f(kScale));
}

GameRoot::GameRoot()
:   mParticleManager(1024 * 20),
    mViewportSize(800, 600),
    mSpriteBatch(NULL)
{
}

tDimension2f GameRoot::getViewportSize()
{
    return mViewportSize;
}

ParticleManager* GameRoot::getParticleManager()
{
    return &mParticleManager;
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
    char buf[80];
#pragma unused(time)
    Input::getInstance()->update();

    PlayerStatus::getInstance()->update();
    EntityManager::getInstance()->update();
    EnemySpawner::getInstance()->update();
    mParticleManager.update();

    EntityManager::getInstance()->draw(mSpriteBatch);
    mParticleManager.draw(mSpriteBatch);

    // Draw user interface
    sprintf(buf, "Lives: %d", PlayerStatus::getInstance()->getLives());
    mSpriteBatch->drawString(1, Art::getInstance()->getFont(), buf, tPoint2f(5,5), tColor4f(1,1,1,1),
                            0, tPoint2f(0,0), tVector2f(kScale));

    sprintf(buf, "Score: %d", PlayerStatus::getInstance()->getScore());
    DrawRightAlignedString(buf, 5);

    sprintf(buf, "Multiplier: %d", PlayerStatus::getInstance()->getMultiplier());
    DrawRightAlignedString(buf, 35);

    mSpriteBatch->draw(0, Art::getInstance()->getPointer(), Input::getInstance()->getMousePosition(), tOptional<tRectf>());

    VirtualGamepad::getInstance()->draw(mSpriteBatch);

    if (PlayerStatus::getInstance()->getIsGameOver())
    {
        sprintf(buf, "Game Over\nYour Score: %d\nHigh Score: %d",
                PlayerStatus::getInstance()->getScore(),
                PlayerStatus::getInstance()->getHighScore());

        tDimension2f textSize = Art::getInstance()->getFont().getTextSize(buf);
        mSpriteBatch->drawString(1, Art::getInstance()->getFont(), buf, (mViewportSize - textSize) / 2, tColor4f(1,1,1,1),
                                0, tPoint2f(0,0), tVector2f(kScale));
    }
    

//Run redraw logic here
    mViewport->run();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mSpriteBatch->end();

    glFlush();
}

