#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <vector>
#include "messpunkt.h"




void print_array_2D(float ** output,int rows,int cols);

std::vector<messpunkt>csv_einlesen(const char* path);
void extract_values2(float *mp,char *stream);

void udp_server(void);


#endif // HELPFUNCTIONS_H
