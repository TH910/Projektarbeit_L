#include "printer.h"

void printer::print_values(double x,double y, double z)
{
  emit print_signal(x,y,z);
}

void printer::set_state(bool state)
{
  emit state_signal(state);
}

void printer::receive_data(int counter)
{
  emit receive_signal(counter);
}
