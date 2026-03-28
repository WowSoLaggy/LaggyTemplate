#pragma once

#include "Fwd.h"

#include <LaggyDx/KeyboardKeys.h>  
#include <LaggyDx/MouseKeys.h>  
#include <LaggySdk/Vector.h>


class InputManager
{
public:
  void onKeyPressed(Dx::KeyboardKey i_key);
  void onKeyReleased(Dx::KeyboardKey i_key);
  void onKeyCurrent(Dx::KeyboardKey i_key);
  void onMouseMove(Sdk::Vector2I i_moveDiff);
  void onMouseWheel(int i_distance);
  bool onMouseClick(Dx::MouseKey i_key);
  bool onMouseRelease(Dx::MouseKey i_key);

private:
  bool d_tryDrag = false;
  bool d_isDragging = false;
};
