#include "stdafx.h"
#include "SimClock.h"


double SimClock::toSimDelta(double i_realDelta) const
{
  return i_realDelta * d_timeScale;
}

void SimClock::setTimeScale(double i_timeScale)
{
  d_timeScale = i_timeScale;
}

bool SimClock::isPaused() const
{
  return d_timeScale <= 0.1; // 0.1 to avoid floating point precision issues
}
