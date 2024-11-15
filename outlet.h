/*
Daniel Yadov
Outlet class definition
*/

#ifndef outlet_h
#define outlet_h

#include "current_monitor.h"
#include <Arduino.h>

class outlet {
  private:

    String identifier;
    int current_mon_pin_num;
    int toggle_pin_num;
    int power_consumption;
    bool status;

  public:

    outlet(int current, int toggle, int index); //constructor used to initialize static values

    void pin_mode(int mode);

    int get_pin_num();
    int set_pin_num(int num);

    current_monitor get_current();

    char get_identifier();

    bool get_status();
    void set_status(bool toggle_value);

};




#endif