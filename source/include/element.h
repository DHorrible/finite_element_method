#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdlib.h>
#include <stdio.h>

#include "share.h"

typedef struct Connection {
    unsigned doff;
    double fx;
    double fy;
    double fz;
    double mx;
    double my;
    double mz;
} Connection;

typedef struct Element {
    double l;
    double a;
    double b;
    double e;
    Connection* conn_start;
    Connection* conn_finish;
} Element;

Element* element_create();
void element_free(Element* element);
void update_doff(Connection* connection, unsigned cstr);

#endif
