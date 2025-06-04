/**
 * @file node.h
 * @author Patrick McGrath, Student, VIU, Self-Project
 * @version 1.0.0
 * @date June 3, 2025
 *
 * Definition for node data structure.
 * Nodes exist in a double-linked list and each of these lists are contained within a lump.
 * Lumps are a seperate double-linked list defined in lump.h
 */
#include <cstddef>

#ifndef NODE_H
#define NODE_H


struct node {
    int val;
    node* next = NULL;
    node* prev = NULL;
};





#endif
