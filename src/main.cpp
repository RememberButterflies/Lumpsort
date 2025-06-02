#include "../include/fun.h"
#include <string>
#include <limits>





int main (){

    // pointer for root lump
    lump* L = new lump;
    if (L == NULL){
        return -1;
    }

    // variables for user input
    std::string userInput = "DEFAULT";
    int inputCode = UI::error;

    // initial prompt display
    print_user_prompts;

    // continually ask for user selection until quit is chosen
    while (inputCode != UI::quit){

        // get input
        std::cin >> userInput;
        inputCode = getInputCode(userInput);
        userInput = "DEFAULT";

        // handle input
        switch (inputCode) {
            case UI::help:
                            print_user_prompts;
                            break;
            case UI::insert:

                            // get user input for new value and insert it
                            // if error, set code to quit
                            // else, continue
                            int newval = std::numeric_limits<int>::max();
                            std::cout << "integer value: ";
                            std::cin >> userInput;
                            newval = getUserInt(userInput);
                            if (newval != std::numeric_limits<int>::max()){
                                if (lump_insert(newval, L) == -1){
                                    inputCode = UI::quit;
                                }
                            }
                            break;
            case UI::search:
            case UI::remove:
            case UI::print:
            case UI::printfile:
            case UI::quit:
                        break;
            case UI::error:
                        std::cout << "Invalid input. Enter a Valid command (or 'h' for a list of commands)" << std::endl;
                        break;
            default:
                        // some issue, reset userCode
                        inputCode = UI::error;
                        break;
        }
    }
    return 0;
}