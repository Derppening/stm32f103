#include "main.h"

int main() {
    LED LEDa(&PA15);
    LEDa.init();
    while (1) {
        LEDa.on();
    }
}
