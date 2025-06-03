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
        L->smallest->prev = N;
        L->smallest = N;
        return val;
    }

    // check if val is >= L->largest
    // N is new largest
    if (val >= L->largest->val){
        L->largest->next = N;
        N->prev = L->largest;
        L->largest = N;
        return val;
    }

    // else, val is in the middle, 
    // delete val's node
    // check if L->next exists, if not create it and link it
    // insert val into next lump, recursively
    delete N;
    if (L->next == NULL){
        lump* nextL = new lump;
        if (nextL == NULL){
            return -1;
        }
        L->next = nextL;
        nextL->prev = L;
    }
    return lump_insert(val, L->next);

    // unknown error
    return -1;
}




// find value in hump
// pass the root lump of the hump
// null on error, the node itself if found
// updates LN to be the lump with val's node
node* lump_find(int val, lump* L, lump*& LN){

    // check that L exists
    if (L == NULL){
        LN = NULL;
        return NULL;
    }

    // check that L is not empty
    if (L->smallest == NULL){
        LN = NULL;
        return NULL;
    }

    // search this lump
    node* N = L->smallest;
    while (N != NULL){
        if (N->val == val){
            // found
            LN = L;
            return N;
        } else {
            N = N->next;
        }
    }

    // val not found in this lump, search next
    // return value with tail recursion
    return lump_find(val, L->next, LN);
}


// remove a value from a hump if it exists
// -1 on error, 0 otherwise
int lump_remove(int val, lump* L){

    // find val's node and lump
    lump* LN = NULL;
    node* N = lump_find(val, L, LN);

    // check if node found
    if (N == NULL){
        return -2;
    }


    // relink neighbour nodes
    if (N->prev != NULL){
        // not the smallest
        N->prev->next = N->next;
    } else {
        // is the smallest
        LN->smallest = N->next;
    }
    if (N->next != NULL){
        // not largest
        N->next->prev = N->prev;
    } else {
        // is largest
        LN->largest = N->prev;
    }
    // remove N
    delete N;

    // check if LN is 1 or 0 nodes
    if (LN->smallest == LN->largest){
        if (LN->smallest == NULL){
            // LN is empty
            // there should not be any remaining lumps, delete LN
            if (LN->prev != NULL){
                LN->prev->next = LN->next;
            }
            if (LN->next != NULL){
                LN->next->prev = LN->prev;
            }
            delete LN;
            return val;
        }
    }

    // borrow edge nodes from next lump(s), if needed
    if (borrow_nodes(LN) != -1){
        return val;
    }

    // unknown error
    return -1;
}


// "borrows" nodes from neighbour lumps if needed
// helper funciton for lump_remove
// if an edge node was removed, it may have in validated that lump.
// this function will check if thats true and then move the next lump's edge node down
// then recursively do the same until its not needed or its at the end, then stops
int borrow_nodes(lump* LN){

    // check if LN exists
    if (LN == NULL){
        return 0;
    }
    // check if LN has a next lump
    if (LN->next == NULL){
        // nothing to borrow
        return 0;
    }


    // variables for borrowing
    lump* LNn = LN->next;
    // this nodes current smallest
    // the next node's smallest
    node* LNsmallest = LN->smallest;
    node* LNnsmallest = LNn->smallest;
    // this nodes current largest
    // the next node's largest
    node* LNlargest = LN->largest;
    node* LNnlargest = LNn->largest;
    // check LN's smallest is larger than next lump's smallest
    // sequential nodes can have the same value smallest's (or largests)
    // first check if there is a smallest node
    if (LNsmallest == NULL){
        return 0;
    }
    if (LNsmallest->val > LNnsmallest->val){
        // move LN's next's smallest node to be LN's new smallest
        LNn->smallest = LNnsmallest->next;
        if (LNn->smallest != NULL){
            LNn->smallest->prev = NULL;
        } else {
            // if moving LNn's smallest made it NULL, its largest is also NULL
            LNn->largest = NULL;
        }
        LNnsmallest->next = LNsmallest;
        LNsmallest->prev = LNnsmallest;
        LN->smallest = LNnsmallest;

        // check if LN->next is now empty
        // delete it and return
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

        // borrow from the next nodes
        return borrow_nodes(LNn);
    }

    // largest side
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
        return borrow_nodes(LNn);
    }

    /// nothing to borrow
    return 0;

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