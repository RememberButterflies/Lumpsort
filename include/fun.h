#include "lump.h"
#include "node.h"
#include <string>
#include <iostream>


#ifndef FUN_H
#define FUN_H

// enums for determining user selection
enum class UI {
    help,
    insert,
    search,
    remove,
    print,
    printfile,
    quit,
    error
};


// insert a value into a hump,
// pass the root lump of the hump
// -1 on error, 0 otherwise
int lump_insert(int val, lump* L);

// find value in hump
// pass the root lump of the hump
// null on error, the node itself if found
node* lump_find(int val, lump* L);


// remove a value from a hump if it exists
// -1 on error, 0 otherwise
int lump_remove(int val, lump* L);


// prints the values in a hump
// pass the root lump of the hump
void lump_print(lump* L);


// print the values in a hump to a file, in a format that this program can read as input
// pass the root lump of the hump
void lump_print_to_file(lump* L, std::string filename);


// display options to user
void print_user_prompts();

// convert user input into a input code
int getInputCode(std::string userInput);

// get integer from user input
int getUserInt(std::string userInput);

// free memory from a hump
void lump_free(lump* L);

#endif