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
  public:

    current_monitor(int pin);

    int get_current();
};




#endif