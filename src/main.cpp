/**
 * @file main.cpp
 * @author Patrick McGrath, Student, VIU, Self-Project
 * @version 1.0.0
 * @date June 3, 2025
 *
 * Main function for lumpsort algorithm.
 * Handles user input and calls appropriate functions until quit is chosen.
 */
#include "../include/fun.h"
#include <string>
#include <limits>




/**
 * Main function. Handles all user input and interaction. 
 *
 * @param none
 * 
 * @return 0
 */
int main (){

    // pointer for root lump
    lump* L = new lump;
    if (L == NULL){
        return -1;
    }
    int Lsize = 0;

    // variables for user input
    std::string userInput = "DEFAULT";              // string for user input
    int inputCode = (int)UI::error;                 // code for user selection
    int newval = std::numeric_limits<int>::max();   // integer for user input
    node* N = NULL;                                 // temp node pointer
    node* Nprev = NULL;
    lump* LN = NULL;                                // temp lump pointer



    // continually ask for user selection until quit is chosen
    while (inputCode != (int)UI::quit){

        // If previous selection was not help, print the prompt asking for input
        if(inputCode != (int)UI::help){
            std::cout << "Please enter your next command (or 'h' for a list of commands)" << std::endl;
        }

        // get input and inputCode
        // and reset variables
        std::cin >> userInput;
        inputCode = getInputCode(userInput);
        userInput = "DEFAULT";
        int result = -1;

        // handle input
        switch (inputCode) {
            case (int)UI::help:
                            print_user_prompts();
                            break;
            case (int)UI::insert:

                            // get user input for new value and insert it
                            // if error, set code to quit
                            // else, continue
                            newval = std::numeric_limits<int>::max();
                            std::cout << "integer value: ";
                            std::cin >> userInput;
                            newval = getUserInt(userInput);
                            if (newval != std::numeric_limits<int>::max()){
                                if (lump_insert(newval, L) == -1){
                                    inputCode = (int)UI::quit;
                                } else {
                                    Lsize++;
                                }
                            } else {
                                std::cout << "Not a valid integer" << std::endl;
                            }
                            break;
            case (int)UI::search:

                            // get user input for search
                            newval = std::numeric_limits<int>::max();
                            std::cout << "integer value: ";
                            std::cin >> userInput;
                            newval = getUserInt(userInput);
                            if (newval != std::numeric_limits<int>::max()){
                                LN = NULL;
                                N = lump_find(newval, L, LN);
                                if (N == NULL){
                                    std::cout << newval << " not found" << std::endl;
                                } else {
                                    std::cout << newval << " found" << std::endl;
                                }
                            } else {
                                std::cout << "Not a valid integer" << std::endl;
                            }
                            break;
            case (int)UI::remove:

                            // get user input for removal
                            newval = std::numeric_limits<int>::max();
                            std::cout << "integer value: ";
                            std::cin >> userInput;
                            newval = getUserInt(userInput);
                            if (newval != std::numeric_limits<int>::max()){
                                // attempt to remove it
                                result = lump_remove(newval, L);
                                if (result == -1){
                                    std::cout << "Error removing " << newval << std::endl;
                                } else if (result == -2){
                                    std::cout << newval << ", not found in lumphump" << std::endl;
                                }
                            } else {
                                std::cout << "Not a valid integer" << std::endl;
                            }
                            break;
            case (int)UI::print:
                            std::cout << "Lumphump values are: " << std::endl;
                            lump_print(L);
                            break;
            case (int)UI::printfile:
                            std::cout << "Please enter a file name (without extension): ";
                            std::cin >> userInput;
                            result = lump_print_to_file(L, userInput);
                            if (result == -1){
                                std::cout << "Not a valid filename" << std::endl;
                            } else if (result == -2){
                                std::cout << "Error: file already exists" << std::endl;
                            } else if (result == -3){
                                std::cout << "Error writing to file" << std::endl;
                            }
                            break;
            case (int)UI::quit: // do nothing, the next iteration of this loop will exit itself
                        break;
            case (int)UI::error:
                        std::cout << "Invalid input. Enter a Valid command (or 'h' for a list of commands)" << std::endl;
                        break;
            default:
                        // some issue, reset userCode
                        inputCode = (int)UI::error;
                        break;
        }
        
    }

    // Free memory and exit
    lump_free(L);
    return 0;
}