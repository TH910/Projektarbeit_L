#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <vector>
#include "messpunkt.h"




void print_array_2D(double ** output,int rows,int cols);

std::vector<messpunkt>csv_einlesen(const char* path);
void extract_values2(double *mp,char *stream);

void udp_server(void);
void conv_vec_to_arr(std::vector<messpunkt> data,double array[3][3]);



#endif // HELPFUNCTIONS_H

