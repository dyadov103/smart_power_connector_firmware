/*
Daniel Yadov
Outlet class definition
*/

#ifndef outlet_h
#define outlet_h

#include "current_monitor.h"

class outlet {
  private:

    char *identifier;
    int current_mon_pin_num;
    int toggle_pin_num;
    int power_consumption;
    bool status;

  public:

    void pin_mode(int mode);

    int get_pin_num();
    int set_pin_num(int num);

    current_monitor get_current();

    char set_identifier(char *id);
    char get_identifier();

    bool get_status();
    void set_status(bool toggle_value);

};




#endif