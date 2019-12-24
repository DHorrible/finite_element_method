#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdlib.h>

#include "share.h"

typedef struct Connection {
    int doff;
    double fx;
    double fy;
    double fz;
    double mx;
    double my;
    double mz;
} Connection;

typedef struct Element {
    double length;
    double square;
    double hardness;
    Connection* conn_start;
    Connection* conn_finish;
 } Element;

Element* element_create();
void element_free(Element* element);
void update_doff(Connection* connection, int cstr);
void set_csrt(int* doff, int csrt);
#endif
