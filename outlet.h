/*
Daniel Yadov
Outlet class definition
*/

#ifndef outlet_h
#define outlet_h

#include <Arduino.h>

class outlet {
  private:

    String identifier;
    int current_mon_pin_num;
    int toggle_pin_num;
    int power_consumption;
    bool status;

  public:


    outlet(); //default constructor to initialize the array
    outlet(int current, int toggle, int index); //constructor used to initialize static values

    void pin_mode(int mode);

    int get_pin_num();
    int set_pin_num(int num);

    int get_power();

    String get_identifier();

    bool get_status();
    void set_status(bool toggle_value);

};




#endif