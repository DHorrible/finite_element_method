#include "element.h"

Element* element_create() {
    Element* element = (Element*)malloc(sizeof(Element));

    element->length = 0.;
    element->square = 0.;
    element->hardness = 0.;
    
    element->conn_start = (Connection*)malloc(sizeof(Connection));
    element->conn_start->doff = DOFF_ALL;
    element->conn_start->fx = 0;
    element->conn_start->fy = 0;
    element->conn_start->fz = 0;
    element->conn_start->mx = 0;
    element->conn_start->my = 0;
    element->conn_start->mz = 0;
    
    element->conn_finish = (Connection*)malloc(sizeof(Connection));
    element->conn_finish->doff = DOFF_ALL;
    element->conn_finish->fx = 0;
    element->conn_finish->fy = 0;
    element->conn_finish->fz = 0;
    element->conn_finish->mx = 0;
    element->conn_finish->my = 0;
    element->conn_finish->mz = 0;

    return element;
}

void element_free(Element* element) {
    free(element->conn_start);
    free(element->conn_finish);
    free(element);
}

void update_doff(Connection* connection, int cstr) {
    switch (cstr)
    {
    case 0:
        connection->doff &= CSTR0;
        break;
    case 1:
        connection->doff &= CSTR1;
        break;
    default:
        break;
    }

    if ((connection->doff & 0x100000) == 0) {
        connection->fx = 0.;   
    }
    if ((connection->doff & 0x010000) == 0) {
        connection->fy = 0.;   
    }
    if ((connection->doff & 0x001000) == 0) {
        connection->fz = 0.;   
    }
    if ((connection->doff & 0x000100) == 0) {
        connection->mx = 0.;   
    }
    if ((connection->doff & 0x000010) == 0) {
        connection->my = 0.;   
    }
    if ((connection->doff & 0x000001) == 0) {
        connection->mz = 0.;   
    }
}
