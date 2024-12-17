#include "current_monitor.h"
#include <Arduino.h>
#include "configuration.h"

current_monitor::current_monitor() {
  pin_num = -1;
}

current_monitor::current_monitor(int pin) {
  pin_num = pin;
  pinMode(pin, INPUT);
}

void current_monitor::set_pin_num(int pin) {
  pin_num = pin;
  pinMode(pin, INPUT);
}

float current_monitor::get_current() {
  float sum_squared = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    int adc_value = analogRead(pin_num);
    float voltage_out = ((float)adc_value / ADC_RESOLUTION) * VOLTAGE_REFERENCE;
    float voltage_diff = voltage_out - zero_current;
    sum_squared += voltage_diff * voltage_diff;
    delay(1);
  }

  float voltage_rms = sqrt(sum_squared / NUM_SAMPLES);
  float current_rms = voltage_rms / CURRENT_SENSITIVITY;

  return current_rms;
}

void current_monitor::calibrate_zero_current() {
  float sum = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    int adc_value = analogRead(pin_num);
    float voltage = ((float)adc_value / ADC_RESOLUTION) * VOLTAGE_REFERENCE; // Convert to voltage
    sum += voltage;
    delay(1);  // Small delay between samples
  }
  zero_current = sum / NUM_SAMPLES;  // Return average voltage
  Serial.println(zero_current);
}


//  float vADC = (adcValue / (float)ADC_RESOLUTION) * V_REF;
