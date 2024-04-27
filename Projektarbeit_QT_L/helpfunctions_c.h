#ifndef HELPFUNCTIONS_C_H
#define HELPFUNCTIONS_C_H

#include"messpunkt.h"
extern "C" {
float **aufbau_matrix(int zeile, int spalte);
void abbau_matrix(float **matrix,int zeile);
}

#endif // HELPFUNCTIONS_C_H
