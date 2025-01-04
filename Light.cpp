#include "Light.h"
#include <iostream>
#include <thread>
#include <chrono>

/* I used the following link from stackoverflow to aid in formatting my light.
https://stackoverflow.com/questions/71789390/c-light-switch-with-two-buttons-if-bar-do-x-set-foo-1-if-thing-and-foo-1
From this, I was able to learn how to simulate the interaction of turning on and off the button which I had been struggling to understand.
Although my output is different due to the coursework requirements, when the user indicates they want to turn on/off a light, the button will be
"pressed" (simulated as we aren't using hardware). When the button is turned on for a device, e.g. Bedroom, the current brightness will be displayed.
When the off button is "pressed", it will simply just display [switch on] so the user can turn it on if they want. */

Light::Light(const std::string& name)
  : Devices(name), state(false), brightness(0), sleepTimer(0) {
}

#pragma region Viewing Functions
void Light::quickView() const {
  std::cout << name << " (" << getType() << "): "
  << brightness << "Brightness," << (state ? "On" : "Off") << "%\n";
}

void Light::display() const {
  std::cout << "Device Name: " << name << "\n"
    << "Device Type: " << getType() << "\n"
    << "Brightness: " << brightness << "%\n"
    << "State: " << (state ? "On" : "Off") << "\n";
}
#pragma endregion

#pragma region Light Functions
void Light::turnOn() {
  if (!state) {
    state = true;
    std::cout << name << ": " << brightness << "% Brightness [switch off]\n";
  }
}

void Light::turnOff() {
  if (state) {
    state = false;
    std::cout << name << ": off [switch on]\n";
  }
}

void Light::adjustBrightness(int newBrightness) {
  if (newBrightness >= 0 && newBrightness <= 100) {
    brightness = newBrightness;
  }
  else {
    std::cout << "Invalid brightness value for " << name << ".\n";
  }
}

void Light::setSleepTimer(int minutes) {
  sleepTimer = minutes;
  std::cout << name << " will turn off in " << sleepTimer << " minutes.\n";
  std::thread([this]() {
    std::this_thread::sleep_for(std::chrono::minutes(sleepTimer));
    this->turnOff();
    }).detach();
}

std::string Light::getType() const {
  return "Light";
}

bool Light::getState() const {
  return state;
}

int Light::getBrightness() const {
  return brightness;
}

int Light::getSleepTimer() const {
  return sleepTimer;
}

// Register a callback for turning the light on
void Light::registerOnCallback(std::function<void()> callback) {
  onCallbacks.push_back(callback);
}

// Register a callback for turning the light off
void Light::registerOffCallback(std::function<void()> callback) {
  offCallbacks.push_back(callback);
}

// Simulate pressing the "On" button
void Light::pressOnButton() {
  for (const auto& callback : onCallbacks) {
    callback();
  }
  turnOn();
}

// Simulate pressing the "Off" button
void Light::pressOffButton() {
  for (const auto& callback : offCallbacks) {
    callback();
  }
  turnOff();
}
#pragma endregion