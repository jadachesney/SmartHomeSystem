#include "Speaker.h"


Speaker::Speaker(const std::string& name)
  : Devices(name), volume(0), isPlaying(false) {
} // default volume is 0%


void Speaker::quickView() const {
  std::cout << name << " (Speaker): Volume " << volume
    << "%, " << (isPlaying ? "Playing" : "Stopped") << "\n";
}


void Speaker::display() const {
  std::cout << "Device Name: " << name << "\n"
    << "Device Type: Speaker\n"
    << "Volume: " << volume << "%\n"
    << "State: " << (isPlaying ? "Playing" : "Stopped") << "\n";
}


std::string Speaker::getType() const {
  return "Speaker";
}

void Speaker::setVolume(int newVolume) {
  if (newVolume >= 0 && newVolume <= 100) {
    volume = newVolume;
    std::cout << name << " volume set to " << volume << "%.\n";
  }
  else {
    std::cout << "Invalid volume level. Please set between 0 and 100.\n";
  }
}


void Speaker::play() {
  if (!isPlaying) {
    isPlaying = true;
    std::cout << name << " is now playing.\n";
  }
  else {
    std::cout << name << " is already playing.\n";
  }
}


void Speaker::stop() {
  if (isPlaying) {
    isPlaying = false;
    std::cout << name << " has stopped.\n";
  }
  else {
    std::cout << name << " is already stopped.\n";
  }
}