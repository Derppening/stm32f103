#include "button.h"
#include "led.h"

int main() {
  Led LEDa({0});
  LEDa.SetEnable(true);
  Led LEDb({1});
  Led LEDc({2});

  Button BUTTON1({0});
  Button BUTTON2({1});

  LEDa.SetEnable(false);
  LEDb.SetEnable(false);
  LEDc.SetEnable(false);

  while (true) {
    LEDc.SetEnable(true);
    LEDa.SetEnable(BUTTON1.Read());
    LEDb.SetEnable(BUTTON2.Read());
  }
}
