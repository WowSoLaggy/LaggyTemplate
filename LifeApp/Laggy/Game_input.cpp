#include "stdafx.h"
#include "Game.h"

#include "InputManager.h"


void Game::onKeyPressed(const Dx::KeyboardKey i_key)
{
  App::onKeyPressed(i_key);
  SAFE_DEREF(d_inputManager).onKeyPressed(i_key);
}

void Game::onKeyReleased(const Dx::KeyboardKey i_key)
{
  App::onKeyReleased(i_key);
  SAFE_DEREF(d_inputManager).onKeyReleased(i_key);
}

void Game::onKeyCurrent(const Dx::KeyboardKey i_key)
{
  App::onKeyCurrent(i_key);
  SAFE_DEREF(d_inputManager).onKeyCurrent(i_key);
}

void Game::onMouseMove(Sdk::Vector2I i_moveDiff)
{
  App::onMouseMove(std::move(i_moveDiff));
  SAFE_DEREF(d_inputManager).onMouseMove(i_moveDiff);
}

void Game::onMouseWheel(const int i_distance)
{
  App::onMouseWheel(i_distance);
  SAFE_DEREF(d_inputManager).onMouseWheel(i_distance);
}

bool Game::onMouseClick(const Dx::MouseKey i_key)
{
  if (App::onMouseClick(i_key))
    return true;

  return SAFE_DEREF(d_inputManager).onMouseClick(i_key);
}

bool Game::onMouseRelease(const Dx::MouseKey i_key)
{
  if (App::onMouseRelease(i_key))
    return true;

  return SAFE_DEREF(d_inputManager).onMouseRelease(i_key);
}
