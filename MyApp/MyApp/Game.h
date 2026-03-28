#pragma once

#include "Fwd.h"
#include "SimClock.h"

#include <LaggyDx/App.h>


class Game : public Dx::App
{
public:
  static Game& get();

public:
  Game();

  CameraController& getCameraController() const;
  GuiController& getGuiManager() const;

private:
  static Game* s_this;

  double d_accumulatedSimTime = 0;
  SimClock d_simClock;

  std::shared_ptr<InputManager> d_inputManager;
  std::shared_ptr<CameraController> d_cameraController;
  std::shared_ptr<Dx::ISpriteShader> d_spriteShader;
  std::shared_ptr<GuiController> d_guiController;
  std::shared_ptr<Background> d_background;


  void onNewGame();

  virtual void update(double i_dt) override;
  virtual void render() override;

  virtual void onKeyPressed(Dx::KeyboardKey i_key) override;
  virtual void onKeyReleased(Dx::KeyboardKey i_key) override;
  virtual void onKeyCurrent(Dx::KeyboardKey i_key) override;
  virtual void onMouseMove(Sdk::Vector2I i_moveDiff) override;
  virtual void onMouseWheel(int i_distance) override;
  virtual bool onMouseClick(Dx::MouseKey i_key) override;
  virtual bool onMouseRelease(Dx::MouseKey i_key) override;
};
