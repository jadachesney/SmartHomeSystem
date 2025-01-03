#pragma once

#include <string>
#include <iostream>

class Devices {
public:
  Devices(const std::string& name) : name(name) {}
  virtual ~Devices() = default;

  virtual void quickView() const = 0;
  virtual std::string getType() const = 0;
  virtual void display() const = 0;

  std::string getName() const { return name; }

protected:
  std::string name;
};