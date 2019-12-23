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
    //Connection* ficonn
    int conn_start_doff;
    int conn_finish_doff;

} Element;

Element* element_create();

#endif
