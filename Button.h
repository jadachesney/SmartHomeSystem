#pragma once

#include <functional>
#include <vector>

class Button {
public:
  template<class Func>
  void RegisterCallback_Press(Func&& cb) {
    callbacks_press.emplace_back(std::forward<Func>(cb));
  }

  void Press();

private:
  std::vector<std::function<void(Button&)>> callbacks_press;
};