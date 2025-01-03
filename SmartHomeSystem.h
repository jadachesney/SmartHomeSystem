#pragma once

#include "Light.h"
#include "Button.h"
#include <vector>
#include <string>

class SmartHomeSystem {
public:
  SmartHomeSystem();

  void run(); // Entry point for the system

private:
  std::vector<Light> lights;
  Button switchOnButton;
  Button switchOffButton;

  void loadDevices();             // Load devices into memory
  void saveDevices();             // Save devices to a file
  void listDevices() const;       // Display the list of devices
  void addDevice(const std::string& name); // Add a new device
  void setupCallbacks();          // Set up button functionality
  void displayMenu() const;       // Display the main menu
  void handleUserInput();         // Handle user input from the menu
};