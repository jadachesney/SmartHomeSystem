#include "Button.h"

void Button::Press() {
  for (auto& cb : callbacks_press) cb(*this);
}