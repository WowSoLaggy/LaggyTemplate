#pragma once


class SimClock
{
public:
  double toSimDelta(double realDelta) const;

  void setTimeScale(double timeScale);

  bool isPaused() const;

private:
  double d_timeScale{ 1.0 };
};
