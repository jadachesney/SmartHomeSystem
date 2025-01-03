#include "Light.h"
#include <iostream>
#include <thread>
#include <chrono>

Light::Light(const std::string& name)
  : Devices(name), state(false), brightness(0), sleepTimer(0) {
}

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

void Light::quickView() const {
  std::string stateStr = state ? "on" : "off";
  std::cout << name << " (Light): " << stateStr << ", Brightness: " << brightness << "%\n";
}

std::string Light::getType() const {
  return "Light";
}

void Light::display() const {
  std::cout << "Device Name: " << name << "\n"
    << "Device Type: Light\n"
    << "Brightness: " << brightness << "%\n"
    << "State: " << (state ? "On" : "Off") << "\n";
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