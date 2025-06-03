#include "../include/fun.h"
#include <string>
#include <limits>





int main (){

    // pointer for root lump
    lump* L = new lump;
    if (L == NULL){
        return -1;
    }
    int Lsize = 0;

    // variables for user input
    std::string userInput = "DEFAULT";
    int inputCode = (int)UI::error;
    int newval = std::numeric_limits<int>::max();
    node* N = NULL;
    node* Nprev = NULL;
    lump* LN = NULL;



    // continually ask for user selection until quit is chosen
    while (inputCode != (int)UI::quit){

        // get input
        if(inputCode != (int)UI::help){
            std::cout << "Please enter your next command (or 'h' for a list of commands)" << std::endl;
        }
        std::cin >> userInput;
        inputCode = getInputCode(userInput);
        userInput = "DEFAULT";

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
                                lump* LN = NULL;
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
                                int result = lump_remove(newval, L);
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
            case (int)UI::printfile:
            case (int)UI::quit:
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
    return 0;
}