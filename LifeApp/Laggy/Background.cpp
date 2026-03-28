#include "stdafx.h"
#include "Background.h"

#include "CameraController.h"
#include "DrawLayers.h"
#include "Game.h"

#include <LaggyDx/ISpriteShader.h>


Background::Background()
{
  d_sprite.setTexture("back.png");

  const auto& cameraController = Game::get().getCameraController();
  d_sprite.setSize(cameraController.getScreenSize().getVector<float>());
}


void Background::render(const Dx::ISpriteShader& i_shader) const
{
  i_shader.drawDelayed(d_sprite, DrawLayer::Background, nullptr, true);
}
