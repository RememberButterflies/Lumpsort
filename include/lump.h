/**
 * @file lump.h
 * @author Patrick McGrath, Student, VIU, Self-Project
 * @version 1.0.0
 * @date June 3, 2025
 *
 * Definition of Lump data structure
 * Lumps exist in a double-linked list and contain another double-linked list of nodes.
 * Nodes defined in node.h
 */
#include "node.h"
#include <cstddef>

#ifndef LUMP_H
#define LUMP_H


struct lump {
    node* smallest = NULL;
    node* smallest_core = NULL;
    node* largest = NULL;
    node* largest_core = NULL;
    lump* next = NULL;
    lump* prev = NULL;
};




#endif