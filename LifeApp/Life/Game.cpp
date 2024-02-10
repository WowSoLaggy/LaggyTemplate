#include "stdafx.h"
#include "Game.h"

#include <LaggyDx/AppSettings.h>


namespace
{
  std::unique_ptr<Dx::AppSettings> getAppSettings()
  {
    auto settings = std::make_unique<Dx::AppSettings>();
    return settings;
  }

} // anonym NS


Game::Game()
  : Dx::App(getAppSettings())
{
}
