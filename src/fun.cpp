#include "../include/fun.h"
#include <string>
#include <limits>



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
    if (N == NULL){
        return -1;
    }
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
        if (nextL == NULL){
            return -1;
        }
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

    // check that L exists
    if (L == NULL){
        return NULL;
    }

    // check that L is not empty
    if (L->smallest == NULL){
        return NULL;
    }

    // search this lump
    node* N = L->smallest;
    while (N != NULL){
        if (N->val == val){
            // found
            return N;
        } else {
            N = N->next;
        }
    }

    // val not found in this lump, search next
    // return value with tail recursion
    return lump_find(val, L->next);
}


// remove a value from a hump if it exists
// -1 on error, 0 otherwise
int lump_remove(int val, lump* L){

    // check if L exists
    if (L == NULL){
        return -1;
    }

std::cout << "000 test" << std::endl;

    // find val's node (N), previous node (Nprev) and its lump (LN)
    node* N = lump_find(val, L);
    lump* LN = NULL;
    node* Nprev = find_prev(L, N, LN);


std::cout << "001 test" << std::endl;



    // either N does not exist, it is the only node a lump, it is smallest, largest or in the middle
    // if N does not exist
    if (N == NULL){
        return -1;
    }

    // if N is only element of lump
    if ((LN->smallest == N) && (LN->largest == N)){
        // delete both
        delete N;
        delete LN;
        return val;
    }

    // if N is smallest, but not only
    if ((LN->smallest == N) && (LN->largest != N)){
        LN->smallest = N->next;
        delete N;
        return val;
    }

    // if N is largest but not only
    if ((LN->smallest != N) && (LN->largest == N)){
        LN->largest = Nprev;
        Nprev->next = NULL;
        delete N;
        return val;
    }

    // if N is in the middle
    if ((LN->smallest != N) && (LN->largest != N)){
        Nprev->next = N->next;
        delete N;
        return val;
    }

    // unknown error
    return -1;
}


// find the node previous to N in lumphump
node* find_prev(lump* L, node* N, lump* LN){

    // check L, N is not NULL
    if ((L == NULL) || (N == NULL)){
        LN = NULL;
        return NULL;
    }

    // check that L is not empty
    if (L->smallest == NULL){
        LN = NULL;
        return NULL;
    }

    // first check if N is smallest in L
    if (L->smallest == N){
        // set LN to current L, and return NULL to say that it is first
        LN = L;
        return NULL;
    }
    
    // walk through lump looking for N
    node* tempA = L->smallest;
    node* tempB = tempA->next;
    while (tempB != NULL){
        // if tempB is N, then tempA is prev. update LN and return tempA
        if (tempB == N){
            LN = L;
            return tempA;
        }
        tempA = tempB;
        tempB = tempB->next;
    }

    // check next lumps
    return find_prev(L->next, N, LN);

    return NULL;
}


// prints the values in a hump
// pass the root lump of the hump
void lump_print(lump* L){

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
    lump_print(L->next);
    return;
}


// print the values in a hump to a file, in a format that this program can read as input
// pass the root lump of the hump
void lump_print_to_file(lump* L, std::string filename){
    return;
}


// display options to user
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



// convert user input into a input code
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



// get integer from user input
int getUserInt(std::string userInput){

    // check userInput is not empty
    int len = (int)userInput.size();
    if (len <= 0){
        return std::numeric_limits<int>::max();
    }

    // ones for current value, tens for its decimal power
    // curr is a char for converting input to integer value
    int ones = 0;
    int tens = 1;
    char curr = '!';
    int result = 0;
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


// free memory from a hump
void lump_free(lump* L){
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
    lump_free(L->next);
    return;

}