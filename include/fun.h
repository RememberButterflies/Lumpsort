/**
 * @file fun.h
 * @author Patrick McGrath, Student, VIU, Self-Project
 * @version 1.0.0
 * @date June 3, 2025
 *
 * Function Declarations for Lumphump sorting algorithm
 */

#include "lump.h"
#include "node.h"
#include <string>
#include <iostream>


#ifndef FUN_H
#define FUN_H


// Global Information
// enum for determining user selection
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



/**
 * Function for inserting a new value into a lumphump. 
 * Will recursively call itself on next lumps until success or new one is created.
 *
 * @param val, integer value to be inserted
 * @param L, lump pointer to root lump of the lumphump.
 * 
 * @return val, if successful. -1, otherwise.
 */
int lump_insert(int val, lump* L);


/**
 * Function for finding a value in a lumphump.
 * Will return the first node matching that value in the lumphump,
 * as well as detering the lump it is contained in.
 *
 * @param val, integer value to be searched
 * @param L, lump pointer to root lump of the lumphump.
 * @param LN, lump pointer to the lump containing the node with val.
 * 
 * @return node pointer of val, if successful. NULL, otherwise.
 */
node* lump_find(int val, lump* L, lump*& LN);


/**
 * Function for removing a value from a lumphump
 *
 * @param val, integer value to be removed (if exists)
 * @param L, lump pointer to root lump of the lumphump.
 * 
 * @return -1, if unsuccessful. 0, otherwise.
 */
int lump_remove(int val, lump* L);


/**
 * Helper function for removal of nodes.
 * Removing a node from the edge of a lump can cause its lump to be invalid. 
 * This function checks if the lump is invalidated, and "borrows" from the next lump's edge node.
 * This is done recursively until no lump is invalidated or the end is reached.
 *
 * @param LN, lump pointer to lump that is being checked whether it needs to borrow from its neighbours.
 * 
 * @return -1, if unsuccessful. 0, otherwise. (no unsuccessful conditions identified)
 */
int borrow_nodes(lump* LN);




/**
 * Function for printing the contents of the in-memory lumphump to command-line
 *
 * @param L, lump pointer to root lump of the lumphump.
 * 
 * @return void
 */
void lump_print(lump* L);


/**
 * Function for printing the contents of the in-memory lumphump to file.
 * The output format is for re-use as input by this program.
 * Each value has "i" before it for insert and the whole file ends in "p" and "q" for print and quit.
 * File will be printed to "location" with "extension" appended
 *
 * @param L, lump pointer to root lump of the lumphump.
 * @param filename, string of the file to print to, without extension or location.
 * 
 * @return -1, if not a valid filename.
 * @return -2, if file already exists
 * @return -3, if other error.
 * @return 0, if no error.
 */
int lump_print_to_file(lump* L, std::string filename);



/**
 * Function for displaying user options to command line
 *
 * @param none
 * 
 * @return void
 */
void print_user_prompts();


/**
 * Function for determing if user input is valid and if so, what it is.
 *
 * @param userInput, string to be checked
 * 
 * @return integer value from enum class UI
 */
int getInputCode(std::string userInput);


/**
 * Function for converting user input string into a positive integer, if the string is a valid integer.
 *
 * @param userInput, string to be checked
 * 
 * @return std::numeric_limits<int>::max() if unsuccesful, otherwise the converted value
 */
int getUserInt(std::string userInput);


/**
 * Function for freeing in-memory lumphump and all its nodes
 *
 * @param L, lump pointer to root lump of the lumphump.
 * 
 * @return void
 */
void lump_free(lump* L);

#endif