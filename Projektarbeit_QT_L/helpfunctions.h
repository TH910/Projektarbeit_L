#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include <vector>
#include "helpfunctions_c.h"
#include "messpunkt.h"

void print_array_2D(float ** output,int rows,int cols);
std::vector<messpunkt>csv_einlesen(const char* path);


#endif // HELPFUNCTIONS_H
