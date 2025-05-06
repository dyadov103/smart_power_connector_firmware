/*
Daniel Yadov
Current Monitor class definition
*/

#ifndef current_mon
#define current_mon


class current_monitor {
  private:
    int current_consumption;
    int pin_num;
    float zero_current;
    float calibration_factor = 1.0;
  public:

    current_monitor();
    current_monitor(int pin);

    void set_pin_num(int pin);

    float get_current();
    void calibrate_zero_current();
    void error_factor_calibration();
};




#endif