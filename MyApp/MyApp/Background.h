#pragma once

#include <LaggyDx/AnimatedSprite.h>
#include <LaggyDx/LaggyDxFwd.h>


class Background
{
public:
  Background();

  void render(const Dx::ISpriteShader& i_shader) const;

private:
  Dx::AnimatedSprite d_sprite;
};
