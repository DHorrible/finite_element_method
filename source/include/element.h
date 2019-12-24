#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdlib.h>

#include "share.h"

typedef struct Connection {
    int doff;
    int fx;
    int fy;
    int fz;
    int mx;
    int my;
    int mz;
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

#endif
