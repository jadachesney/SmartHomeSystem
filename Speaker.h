#pragma once
#include "Devices.h"
#include <iostream>
#include <string>

class Speaker : public Devices {
public:

  Speaker(const std::string& name);


  void quickView() const override;
  std::string getType() const override;
  void display() const override;


  void setVolume(int volume);
  void play();
  void stop();

private:
  int volume;  
  bool isPlaying; 
};
