#include "stdafx.h"
#include "Game.h"

#include "Background.h"
#include "CameraController.h"
#include "GuiController.h"
#include "InputManager.h"

#include <LaggyDx/AppSettings.h>
#include <LaggyDx/ISpriteShader.h>
#include <LaggySdk/Random.h>
#include <LaggySdk/ScopeGuard.h>


namespace
{
  constexpr double FixedSimStep = 0.1;

  std::unique_ptr<Dx::AppSettings> getAppSettings()
  {
    auto settings = std::make_unique<Dx::AppSettings>();
    return settings;
  }

} // anonym NS


Game* Game::s_this = nullptr;



Game::Game()
  : Dx::App(getAppSettings())
{
  s_this = this;

  Sdk::randomize();
  getResourceController().loadResources();

  d_inputManager = std::make_shared<InputManager>();
  d_cameraController = std::make_shared<CameraController>();
  d_spriteShader = Dx::ISpriteShader::create(&d_cameraController->getCamera());
  d_guiController = std::make_shared<GuiController>();
  d_background = std::make_shared<Background>();

  onNewGame();
}


Game& Game::get() { return SAFE_DEREF(s_this); }

CameraController& Game::getCameraController() const { return SAFE_DEREF(d_cameraController); }
GuiController& Game::getGuiManager() const { return SAFE_DEREF(d_guiController); }


void Game::onNewGame()
{
  d_guiController->createGameUi();
}


void Game::update(double i_dt)
{
  d_accumulatedSimTime += d_simClock.toSimDelta(i_dt);
  while (d_accumulatedSimTime >= FixedSimStep)
  {
    //d_worldState->simTime += FixedSimStep;

    d_accumulatedSimTime -= FixedSimStep;
  }
}


void Game::render()
{
  const Sdk::ScopeGuard spriteGuard(SAFE_DEREF(d_spriteShader));

  SAFE_DEREF(d_background).render(SAFE_DEREF(d_spriteShader));
}
