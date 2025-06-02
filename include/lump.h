#include "node.h"
#include <cstddef>

#ifndef LUMP_H
#define LUMP_H









struct lump {
    node* smallest = NULL;
    node* largest = NULL;
    lump* next = NULL;
    lump* prev = NULL;
};




#endif