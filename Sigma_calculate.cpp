#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include "pico/stdlib.h"
#include "hardware/adc.h"

using namespace std;

const uint ADC_PIN = 26;  // GPIO 26 es ADC0

uint64_t get_current_time() {
    return to_ms_since_boot(get_absolute_time());
}

float adc_to_voltage(uint16_t adc_value) {
    return (static_cast<float>(adc_value) / 4095.0) * 3.3;
}

int main() {
    stdio_init_all();
    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_select_input(0);

    uint64_t start_time = get_current_time();

    while (true) {
        uint16_t result = adc_read();
        float voltage = adc_to_voltage(result);
        uint64_t current_time = get_current_time();
        // Imprimir valores en tiempo real
        printf("%llu, %.4f\n", current_time, voltage);  // %llu para uint64_t
        if (current_time - start_time >= 60000) {  // 60,000,000 us = 1 minuto
            return 0;
        }
    }
}