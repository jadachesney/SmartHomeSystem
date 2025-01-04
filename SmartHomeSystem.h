#pragma once

#include "Light.h"
#include "Button.h"
#include "Devices.h"
#include "Socket.h"
#include <vector>
#include <string>

class SmartHomeSystem {
public:
  SmartHomeSystem();
  void loadDevices(const std::string& filename);
  void saveDevices(const std::string& filename);
  void listDevices() const;
  void sortByName();
  void sortByDeviceType();
  void addDevice(const std::string& deviceType, const std::string& deviceName);
  void interactWithDevice(const std::string& deviceName);
  void displayMenu() const;
  void run();

private:
  std::vector<Light> lights;
  Button switchOnButton;
  Button switchOffButton;

  std::vector<std::unique_ptr<Devices>> devices;
 
};