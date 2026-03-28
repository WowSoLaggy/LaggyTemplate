#include "stdafx.h"
#include "CameraController.h"

#include <LaggyDx/App.h>
#include <LaggyDx/ICamera2.h>


CameraController::CameraController()
{
  d_screenSize = Sdk::Vector2I(
    Dx::App::get().getSettings().screenWidth,
    Dx::App::get().getSettings().screenHeight);

  d_halfScreenSize = Sdk::Vector2I(
    d_screenSize.x / 2,
    d_screenSize.y / 2);

  d_camera = Dx::ICamera2::create();
  CONTRACT_ASSERT(d_camera);
}


void CameraController::update(const double i_dt)
{
}


Dx::ICamera2& CameraController::getCamera()
{
  CONTRACT_ASSERT(d_camera);
  return *d_camera;
}
const Dx::ICamera2& CameraController::getCamera() const
{
  CONTRACT_ASSERT(d_camera);
  return *d_camera;
}

const Sdk::Vector2I& CameraController::getScreenSize() const { return d_screenSize; }
const Sdk::Vector2I& CameraController::getScreenCenter() const { return d_halfScreenSize; }
