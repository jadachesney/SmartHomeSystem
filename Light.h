#pragma once

#include "Devices.h"
#include <vector>
#include <functional>

class Light : public Devices {
public:
  Light(const std::string& name);

  void turnOn();
  void turnOff();
  void adjustBrightness(int brightness);
  void setSleepTimer(int minutes);

  void quickView() const override;
  std::string getType() const override;
  void display() const override;

  bool getState() const;
  int getBrightness() const;
  int getSleepTimer() const;

  // Button Callbacks
  void registerOnCallback(std::function<void()> callback);
  void registerOffCallback(std::function<void()> callback);
  void pressOnButton();
  void pressOffButton();

private:
  bool state;
  int brightness;
  int sleepTimer;
  std::vector<std::function<void()>> onCallbacks;
  std::vector<std::function<void()>> offCallbacks;
};