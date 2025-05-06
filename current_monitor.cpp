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
    int mV = analogReadMilliVolts(pin_num); // Already accounts for 3.3V Vref
    float voltage = mV / 1000.0;

    float voltage_diff = voltage - zero_current;
    sum_squared += voltage_diff * voltage_diff;

    delayMicroseconds(500); // Tight sampling for smooth signal
  }

  float voltage_rms = sqrt(sum_squared / NUM_SAMPLES);
  float current_rms = (voltage_rms / CURRENT_SENSITIVITY) * calibration_factor;

  return current_rms;
}

void current_monitor::calibrate_zero_current() {
  float sum = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    int mV = analogReadMilliVolts(pin_num);
    float voltage = mV / 1000.0;
    sum += voltage;
    delayMicroseconds(500);
  }

  zero_current = sum / NUM_SAMPLES;
  Serial.print("Zero current (V): ");
  Serial.println(zero_current, 4);

}

void current_monitor::error_factor_calibration() {
  Serial.println("Beginning error factor calculation");
  float expected_current = 0.035;
  float measured_current = get_current();
  Serial.println(measured_current);
  if (measured_current == 0.0) {
    calibration_factor = 1.0;
    Serial.println("Measured current is 0. Failed to calibrate");
    return;
  }
  calibration_factor = expected_current / measured_current;
  Serial.print("Calibration factor: ");
  Serial.println(calibration_factor, 4);
}


//  float vADC = (adcValue / (float)ADC_RESOLUTION) * V_REF;
