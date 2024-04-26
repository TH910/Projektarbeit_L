#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include <vector>
#include "helpfunctions_c.h"

void print_array_2D(float ** output,int rows,int cols);
void csv_einlesen(const char* path,float **matrix);


#endif // HELPFUNCTIONS_H
