#include "node.h"
#include <cstddef>

#ifndef LUMP_H
#define LUMP_H








// if only 1 node, then largest will remain NULL
struct lump {
    node* smallest = NULL;
    node* largest = NULL;
    lump* next = NULL;
};




#endif