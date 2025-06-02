#include "../include/fun.h"




// insert a value into a hump,
// pass the root lump of the hump
// -1 on error, val otherwise
int lump_insert(int val, lump* L){

    // check that L exists
    if (L == NULL){
        return -1;
    }

    // make new node for val
    node* N = new node;
    N->val = val;

    // check if L is empty
    if (L->smallest == NULL){
        L->smallest = N;
        L->largest = N;
        return val;
    }

    /* REDUNDANT?
    // check if L has only one node
    if (L->largest == L->smallest){
        // check if val is <= L->smallest
        // if so, N (val) is new smallest
        // old smallest tracked by largest
        if (val <= L->smallest->val){
            N->next = L->smallest;
            L->smallest = N;
            return val;
        } else {
            // val is > (L->smallest // L->largest)
            // N (val) is new largest
            L->largest->next = N;
            L->largest = N;
            return val;
        }
    }
*/
    // L is not empty
    // check if val is <= L->smallest
    // N is new smallest
    if (val <= L->smallest->val){
        N->next = L->smallest;
        L->smallest = N;
        return val;
    }

    // check if val is >= L->largest
    // N is new largest
    if (val >= L->largest->val){
        L->largest->next = N;
        L->largest = N;
        return val;
    }

    // else, val is in the middle, 
    // delete val's node
    // check if L->next exists, if not create it and link it
    // insert it into next lump, recursively
    delete N;
    if (L->next == NULL){
        lump* nextL = new lump;
        L->next = nextL;
    }
    return lump_insert(val, L->next);

    // unknown error
    return -1;
}




// find value in hump
// pass the root lump of the hump
// null on error, the node itself if found
node* lump_find(int val, lump* L){
    return NULL;
}


// remove a value from a hump if it exists
// -1 on error, 0 otherwise
int lump_remove(int val, lump* L){
    return 0;
}


// prints the values in a hump
// pass the root lump of the hump
void lump_print(lump* L){
    return;
}


// print the values in a hump to a file, in a format that this program can read as input
// pass the root lump of the hump
void lump_print_to_file(lump* L, std::string filename){
    return;
}



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