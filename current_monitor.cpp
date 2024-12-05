#include "current_monitor.h"
#include <Arduino.h>
#include "configuration.h"

current_monitor::current_monitor(int pin) {
  pin_num = pin;
}


int current_monitor::get_current() {
  int adc_value = analogRead(pin_num);
  float voltage_out = (adc_value / ADC_RESOLUTION) * VOLTAGE_REFERENCE;
  float current = (voltage_out - ZERO_CURRENT) / CURRENT_SENSITIVITY;
  float power = current * 110;

  return power;
}


//  float vADC = (adcValue / (float)ADC_RESOLUTION) * V_REF;
