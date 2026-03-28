#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>


class CameraController
{
public:
  CameraController();

  void update(double i_dt);

  Dx::ICamera2& getCamera();
  const Dx::ICamera2& getCamera() const;

  const Sdk::Vector2I& getScreenSize() const;
  const Sdk::Vector2I& getScreenCenter() const;

private:
  Sdk::Vector2I d_screenSize;
  Sdk::Vector2I d_halfScreenSize;
  std::shared_ptr<Dx::ICamera2> d_camera;
};
