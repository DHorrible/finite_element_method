#include "element.h"

Element* element_create() {
    Element* element = (Element*)malloc(sizeof(Element));

    element->l = 0.;
    element->a = 0.;
    element->b = 0.;
    element->e = 0.;
    
    element->conn_start = (Connection*)malloc(sizeof(Connection));
    element->conn_start->doff = DOFF_ALL;
    element->conn_start->fx = 0.;
    element->conn_start->fy = 0.;
    element->conn_start->fz = 0.;
    element->conn_start->mx = 0.;
    element->conn_start->my = 0.;
    element->conn_start->mz = 0.;
    
    element->conn_finish = (Connection*)malloc(sizeof(Connection));
    element->conn_finish->doff = DOFF_ALL;
    element->conn_finish->fx = 0.;
    element->conn_finish->fy = 0.;
    element->conn_finish->fz = 0.;
    element->conn_finish->mx = 0.;
    element->conn_finish->my = 0.;
    element->conn_finish->mz = 0.;

    return element;
}

void element_free(Element* element) {
    free(element->conn_start);
    free(element->conn_finish);
    free(element);
}

void update_doff(Connection* connection, unsigned csrt) {
    connection->doff &= csrt;

    if ((connection->doff & DOFF1) == DOFF_NONE) {
        connection->fx = 0.;   
    }
    if ((connection->doff & DOFF2) == DOFF_NONE) {
        connection->fy = 0.;   
    }
    if ((connection->doff & DOFF3) == DOFF_NONE) {
        connection->fz = 0.;   
    }
    if ((connection->doff & DOFF4) == DOFF_NONE) {
        connection->mx = 0.;   
    }
    if ((connection->doff & DOFF5) == DOFF_NONE) {
        connection->my = 0.;   
    }
    if ((connection->doff & DOFF6) == DOFF_NONE) {
        connection->mz = 0.;   
    }
}
