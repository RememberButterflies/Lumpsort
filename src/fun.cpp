/**
 * @file fun.cpp
 * @author Patrick McGrath, Student, VIU, Self-Project
 * @version 1.0.0
 * @date June 3, 2025
 *
 * Function Definitions for Lumphump sorting algorithm
 * Functions declared in fun.h
 */

#include "../include/fun.h"
#include <string>
#include <limits>
#include <iostream>
#include <fstream>


// Location and extension used by print function
std::string location = "output/";
std::string extension = ".lump";




/**
 * Function for inserting a new value into a lumphump. 
 * Will recursively call itself on next lumps until success or new one is created.
 *
 * @param val, integer value to be inserted
 * @param L, lump pointer to root lump of the lumphump.
 * 
 * @return val, if successful. -1, otherwise.
 */
int lump_insert_basic(int val, lump* L){

    // check that L exists
    if (L == NULL){
        return -1;
    }

    // make new node for val
    node* N = new node;
    if (N == NULL){
        // failure
        return -1;
    }
    N->val = val;

    // check if L is empty
    // make its only node N and return
    if (L->smallest == NULL){
        L->smallest = N;
        L->largest = N;
        return val;
    }

    // L is not empty
    // check if val is <= L->smallest
    // then, N is new smallest, return
    if (val <= L->smallest->val){
        N->next = L->smallest;
        L->smallest->prev = N;
        L->smallest = N;
        return val;
    }

    // check if val is >= L->largest
    // then, N is new largest, return
    if (val >= L->largest->val){
        L->largest->next = N;
        N->prev = L->largest;
        L->largest = N;
        return val;
    }

    // else, val is in the middle, 
    // delete val's node, the next call will make a new one.
    // check if L->next exists, if not create it and link it
    // insert val into next lump, recursively
    delete N;
    if (L->next == NULL){
        lump* nextL = new lump;
        if (nextL == NULL){
            // failure
            return -1;
        }
        L->next = nextL;
        nextL->prev = L;
    }
    return lump_insert_basic(val, L->next);

    // unknown error
    return -1;
}

int lump_insert_huskcore(int val, lump* L){
/* needs to be thought out more
    // check that L exists
    if (L == NULL){
        return -1;
    }

    // make new node for val
    node* N = new node;
    if (N == NULL){
        // failure
        return -1;
    }
    N->val = val;

    // check if L is empty
    // make its only node N, 
    //dont set the core nodes, 
    // do update L's small size 
    // check and remove all cores, and return
    if (L->smallest == NULL){
        L->smallest = N;
        L->largest = N;
        L->small_size++;
        dehusk_small(N, L);
        return val;
    }

    // L is not empty
    // check if val is <= L->smallest
    // then, N is new smallest, return
    if (val <= L->smallest->val){
        N->next = L->smallest;
        L->smallest->prev = N;
        L->smallest = N;
        L->small_size++;
        return val;
    }

    // check if val is >= L->largest
    // then, N is new largest, return
    if (val >= L->largest->val){
        L->largest->next = N;
        N->prev = L->largest;
        L->largest = N;
        L->large_size++;
        return val;
    }

    // else, val is in the middle, 
    // delete val's node, the next call will make a new one.
    // check if L->next exists, if not create it and link it
    // insert val into next lump, recursively
    delete N;
    if (L->next == NULL){
        lump* nextL = new lump;
        if (nextL == NULL){
            // failure
            return -1;
        }
        L->next = nextL;
        nextL->prev = L;
    }
    return lump_insert_huskcore(val, L->next);

    // unknown error
    */
    return -1;
}





/**
 * Function for finding a value in a lumphump.
 * Will return the first node matching that value in the lumphump,
 * as well as detering the lump it is contained in.
 *
 * @param val, integer value to be searched
 * @param L, lump pointer to root lump of the lumphump.
 * @param LN, lump pointer to the lump containing the node with val.
 * 
 * @return node pointer of val and LN points to N's lump, if successful. 
 * @return NULL and LN points to NULL, otherwise.
 */
node* lump_find_basic(int val, lump* L, lump*& LN){

    // check that L exists and if its empty.
    // if either, update LN to NULL and return NULL 
    if (L == NULL){
        LN = NULL;
        return NULL;
    }
    if (L->smallest == NULL){
        LN = NULL;
        return NULL;
    }

    // L exists and has nodes, search it
    node* N = L->smallest;
    while (N != NULL){
        if (N->val == val){
            // found, L is the lump containing N
            LN = L;
            return N;
        } else {
            // not found, check next
            N = N->next;
        }
    }

    // val not found in this lump, search next lump
    // return value from that insertion with tail recursion
    return lump_find_basic(val, L->next, LN);
}


/**
 * Function for removing a value from a lumphump
 *
 * @param val, integer value to be removed (if exists)
 * @param L, lump pointer to root lump of the lumphump.
 * 
 * @return -2 if val not in lumphump
 * @return -1, if other error
 * @return val, if succesful.
 */
int lump_remove_basic(int val, lump* L){

    // find val's node and lump
    lump* LN = NULL;
    node* N = lump_find_basic(val, L, LN);

    // check if node found
    if (N == NULL){
        return -2;
    }


    // relink neighbour nodes
    // check if N is the smallest in LN
    if (N->prev != NULL){
        // not the smallest, link the smaller neighbor of N to N's larger neighbour
        N->prev->next = N->next;
    } else {
        // is the smallest, point LN's smallest to N's larger neighbour
        LN->smallest = N->next;
    }
    // check if N is the largest in LN
    if (N->next != NULL){
        // not largest, link the larger neighbour of N to N's smaller neighbor
        N->next->prev = N->prev;
    } else {
        // is largest, point LN's largest to N's smaller neighbour
        LN->largest = N->prev;
    }

    // remove N
    delete N;

    // check if LN is 1 or 0 nodes
    if (LN->smallest == LN->largest){
        if (LN->smallest == NULL){
            // LN is empty, 0 nodes
            // logically, there should not be any remaining lumps, 
            // link LN's previous neighbour to NULL. 
            // delete LN and return val
            if (LN->prev != NULL){
                LN->prev->next = NULL;
            }
            delete LN;
            return val;
        }
    }

    // Removing val didn't remove a lump. 
    // Must check if lump is now invalidated and borrow nodes from next lumps if it is
    if (borrow_nodes_basic(LN) != -1){
        // borrowing done, return val
        return val;
    }

    // unknown error
    return -1;
}


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
int borrow_nodes_basic(lump* LN){

    // check if LN exists
    if (LN == NULL){
        // No lump is valid
        return 0;
    }
    // check if LN has a next lump
    if (LN->next == NULL){
        // If nothing to borrow, no nodes to invalidate this lump
        return 0;
    }


    // Variables for borrowing
    lump* LNn = LN->next;               // The next lump from this one
    node* LNsmallest = LN->smallest;    // The smallest node of this lump
    node* LNnsmallest = LNn->smallest;  // The smallest node of the next lump
    node* LNlargest = LN->largest;      // The largest node of this lump
    node* LNnlargest = LNn->largest;    // The largest node of the next lump


    // Check small side, and if borrowing there, recursion will occur from that block
    // Code block for borrowing on large side is afterwards, and similarly recursive borrowing will call from that block.

    // check if LN's smallest is larger than next lump's smallest. This is LN being invalid.
    // Sequential lumps can have the same value smallests (or largests) nodes.
    // first check if there is a smallest node
    if (LNsmallest == NULL){
        return 0;
    }
    // check if LN's smallest is larger than next lump's smallest
    if (LNsmallest->val > LNnsmallest->val){
        // move LN's next's smallest node to be LN's new smallest and link it
        LNn->smallest = LNnsmallest->next;
        if (LNn->smallest != NULL){
            LNn->smallest->prev = NULL;
        } else {
            // if moving LNn's smallest made it NULL, its largest is also NULL and must be updated to reflect that
            LNn->largest = NULL;
        }
        LNnsmallest->next = LNsmallest;
        LNsmallest->prev = LNnsmallest;
        LN->smallest = LNnsmallest;

        // check if LN->next is now empty
        // if so, delete it and return
        if (LNn->smallest == NULL){
            if (LNn->prev != NULL){
                LNn->prev->next = LNn->next;
            }
            if (LNn->next != NULL){
                LNn->next->prev = LNn->prev;
            }
            delete LNn;
            return 0;
        }

        // If the next node was not deleted through borrowing, check if the next lump needs to borrow too
        return borrow_nodes_basic(LNn);
    }

    // first check if there is a largest node
    if (LNlargest == NULL){
        return 0;
    }
    // check LN's largest is smaller than next lump's largest
    // sequential nodes can have the same value largest's (or smallest)
    if (LNlargest->val < LNnlargest->val){
        // move LN's next's largest node to be LN's new largest
        LNn->largest = LNnlargest->prev;
        if (LNn->largest != NULL){
            LNn->largest->next = NULL;
        }else {
            // if moving LNn's largest made it NULL, its smallest is also NULL
            LNn->smallest = NULL;
        }
        LNnlargest->prev = LNlargest;
        LNlargest->next = LNnlargest;
        LN->largest = LNnlargest;

        // check if LN->next is now empty
        // delete it and return
        if (LNn->largest == NULL){
            if (LNn->prev != NULL){
                LNn->prev->next = LNn->next;
            }
            if (LNn->next != NULL){
                LNn->next->prev = LNn->prev;
            }
            delete LNn;
            return 0;
        }

        // borrow from the next nodes
        return borrow_nodes_basic(LNn);
    }

    /// nothing to borrow
    return 0;

}




/**
 * Function for printing the contents of the in-memory lumphump to command-line
 *
 * @param L, lump pointer to root lump of the lumphump.
 * 
 * @return void
 */
void lump_print_basic(lump* L){

    // check if lump exists
    // don't print error, it might be the end of hump
    if (L == NULL){
        return;
    }

    // check that L is not empty
    if (L->smallest == NULL){
        return;
    }

    // print all values in order
    // check if at end of lump before printing comma
    node* N = L->smallest;
    while (N != NULL){
        std::cout << N->val;
        N = N->next;
        if (N != NULL){
            std::cout << ", ";
        }
    }
    // end of lump, print new line and print next lumps
    std::cout << std::endl;
    lump_print_basic(L->next);
    return;
}


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
int lump_print_to_file_basic(lump* L, std::string filename){

    // check if lump exists
    if (L == NULL){
        return -3;
    }

    // check that L is not empty
    if (L->smallest == NULL){
        return -3;
    }

    // check if valid filename
    // Valid filename contains ( ( 0-9a-zA-Z ) | '-' | '_' | '.' | ' ' )+
    int len = (int)filename.size();
    if (len <= 0){
        return -1;
    }
    for (int i=0; i<len; i++){
        int valid = -1;
        // check '-', '_', '.' and ' '
        // then 0-9, A-Z and a-z
        if (filename[i] == ' '){
            valid = 0;
        } else if (filename[i] == '-'){
            valid = 0;
        } else if (filename[i] == '_'){
            valid = 0;
        } else if (filename[i] == '.'){
            valid = 0;
        } else if ((filename[i] >= '0') && (filename[i] <= '9')){
            valid = 0;
        } else if ((filename[i] >= 'A') && (filename[i] <= 'Z')){
            valid = 0;
        } else if ((filename[i] >= 'a') && (filename[i] <= 'z')){
            valid = 0;
        }

        // check if that char was valid
        if (valid == -1){
            return -1;
        }
    }


    // string with location and extension appended
    std::string realFN = location + filename + extension;

    // check if file already exists
    std::ifstream file(realFN.c_str(), std::ios::ate);
    // Check if the file stream was successfully opened
    if (file.good()){
        file.close();
        return -2;
    }
    file.close();



    // open file in write only mode
    std::ofstream outFile;
    outFile.open(realFN);
    if (!outFile.is_open()) {
        return -3;
    }


    // iterate through lumps, and nested iterate through nodes
    lump* currL = L;
    node* N = currL->smallest;
    while (currL != NULL){
        while (N != NULL){
            // insert "i" + newline before each number so this program can read it later
            outFile << "i\n" << N->val << "\n";
            N = N->next;
        }
        currL = currL->next;
        if (currL != NULL){
            N = currL->smallest;
        }
    }
    // command for program to print contents and close
    outFile << "p\n";
    outFile << "q\n";
    outFile.close();

    return 0;
}


/**
 * Function for displaying user options to command line
 *
 * @param none
 * 
 * @return void
 */
void print_user_prompts(){
    std::cout << "Please select an option: " << std::endl;
    std::cout << "    h:    Display this menu again." << std::endl;
    std::cout << "    i:    Insert values into a the lumphump." << std::endl;
    std::cout << "    s:    Search for a value in the lumphump." << std::endl;
    std::cout << "    r:    Remove a value from the lumphump." << std::endl;
    std::cout << "    p:    Print the contents of the lumphump." << std::endl;
    std::cout << "    f:    Print the contents of the lumphump to a file." << std::endl;
    std::cout << "    q:    Quit this program, lumphump will be lost." << std::endl;
}



/**
 * Function for determing if user input is valid and if so, what it is.
 *
 * @param userInput, string to be checked
 * 
 * @return integer value from enum class UI
 */
int getInputCode(std::string userInput){

    // if nothing entered, return error
    int len = (int)userInput.size();
    if (len <= 0){
        return (int)UI::error;
    }

    // switch based on first char of input
    int result = (int)UI::error;
    switch (userInput[0]){
        case 'h':
        case 'H':
                result = (int)UI::help;
                break;
        case 'i':
        case 'I':
                result = (int)UI::insert;
                break;
        case 's':
        case 'S':
                result = (int)UI::search;
                break;
        case 'r':
        case 'R':
                result = (int)UI::remove;
                break;
        case 'p':
        case 'P':
                result = (int)UI::print;
                break;
        case 'f':
        case 'F':
                result = (int)UI::printfile;
                break;
        case '0':
                result = (int)UI::basic;
                break;
        case '1':
                result = (int)UI::huskcore;
                break;
        case '2':
                result = (int)UI::huskcoresquare;
                break;
        case 'q':
        case 'Q':
                result = (int)UI::quit;
                break;
        default:
                result = (int)UI::error;
                break;
    }

    // return result
    return result;
}



/**
 * Function for converting user input string into a positive integer, if the string is a valid integer.
 *
 * @param userInput, string to be checked
 * 
 * @return std::numeric_limits<int>::max() if unsuccesful, otherwise the converted value
 */
int getUserInt(std::string userInput){

    // check userInput is not empty
    int len = (int)userInput.size();
    if (len <= 0){
        return std::numeric_limits<int>::max();
    }

    // ones for current value, tens for its decimal power
    // curr is a char for converting input to integer value
    int ones = 0;           // base value
    int tens = 1;           // value of the decimal position of the base value
    char curr = '!';        // char that is converted to 'ones'
    int result = 0;         // the running total to be returned
    for (int i = len-1; i >= 0; i--){
        curr = userInput[i];
        // check curr is a number
        if ((curr < '0') || (curr > '9')){
            return std::numeric_limits<int>::max();
        }

        // char to int.
        // then int times current power of 10
        // add to result
        // increase 10's power
        ones = curr - '0';
        ones *= tens;
        result += ones;
        tens *= 10;
    }

    // return result
    return result;
}


/**
 * Function for freeing in-memory lumphump and all its nodes
 *
 * @param L, lump pointer to root lump of the lumphump.
 * 
 * @return void
 */
void lump_free_basic(lump* L){
    // check if L exists
    if (L == NULL){
        return;
    }


    // L exists, free its Nodes
    node* curr = L->smallest;
    while (curr != NULL){
        node* temp = curr->next;
        delete curr;
        curr = temp;
    }

    // free remaining lumps
    lump_free_basic(L->next);
    return;

}