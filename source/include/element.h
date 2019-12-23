#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdlib.h>

#include "share.h"

typedef struct Element {
    double length;
    double square;
    double hardness;
    int conn_start_doff;
    int conn_finish_doff;
} Element;

Element* element_create();

#endif
