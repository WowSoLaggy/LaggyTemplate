#include "stdafx.h"
#include "InputManager.h"

#include "Game.h"


void InputManager::onKeyPressed(const Dx::KeyboardKey i_key)
{
  if (i_key == Dx::KeyboardKey::Escape)
    Game::get().stop();
}

void InputManager::onKeyReleased(const Dx::KeyboardKey i_key)
{
}

void InputManager::onKeyCurrent(const Dx::KeyboardKey i_key)
{
}

void InputManager::onMouseMove(const Sdk::Vector2I i_moveDiff)
{
  if (d_tryDrag)
  {
    d_isDragging = true;
  }
}

void InputManager::onMouseWheel(const int i_distance)
{
}

bool InputManager::onMouseClick(const Dx::MouseKey i_key)
{
  if (i_key == Dx::MouseKey::Left)
  {
    d_tryDrag = true;
  }
  else if (i_key == Dx::MouseKey::Right)
  {
  }

  return false;
}

bool InputManager::onMouseRelease(const Dx::MouseKey i_key)
{
  if (i_key == Dx::MouseKey::Left)
  {
    if (!d_isDragging)
    {
    }

    d_tryDrag = false;
    d_isDragging = false;

    return true;
  }

  return false;
}
