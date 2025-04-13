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
    int mV = analogReadMilliVolts(pin_num); // Reads millivolts directly
    float voltage_out = mV / 1000.0;     
    float voltage_diff = voltage_out - zero_current; // zero_current
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
    int mV = analogReadMilliVolts(pin_num);
    float voltage = mV / 1000.0;
    sum += voltage;
    delayMicroseconds(500);  // Small delay between samples
  }
  zero_current = sum / NUM_SAMPLES;  // Return average voltage
  Serial.println(zero_current);
}


//  float vADC = (adcValue / (float)ADC_RESOLUTION) * V_REF;
