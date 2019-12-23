#include "element.h"

Element* element_create() {
    Element* element = (Element*)malloc(sizeof(Element));

    element->length = 0.;
    element->square = 0.;
    element->hardness = 0.;
    element->conn_start_doff = DOFF_ALL;
    element->conn_finish_doff = DOFF_ALL;

    return element;
}