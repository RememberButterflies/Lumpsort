# Lumpsort Algorithm Demonstration Program


## Background
Lumpsort algorithm I designed for fun. I half finished it a few years ago. But, moved on to other things. 
I don't think it is particular efficient. But it was interesting. 

This is an attempt to rebuild it from memory, and hopefully better now. 

## Idea:
A binary search tree will take a new value to insert, and check recursively; "is the value less than the current value, or is it greater than or equal to the current value?" and then inserts it at a LOWER level than the current value. 
My thought was, what if instead of a single node as the current value, it was a sorted list. Each list would have a largest and smallest value and 0 or more internal values. 
Then, when inserting a new value, you would recursively check, "is the value less than the current list's smallest value, or is it greater than or equal to the current list's largest value, or is it between them?" If the answer was yes for the first question, the value is the new smallest for that list. Else, if the 2nd answer was yes, then its the new largest. Otherwise, recursively check the next lists. If the end is reached, it is a new list by itself.


## Terminology:
    Node:   The data structure being sorted. Exists in a double-linked list contained within a single lump.
    Lump:   The data structure that contains a single sorted double-linked node list. Exists in a double-linked list within a hump
    Hump:   (aka Lumphump) A double-linked list of lumps. Each lump is within the range of the previous lump.
    Husk:   The smallest and largest portions of a lump, where each lowest value is lesser than each next lump, and similar for the largest values. 
    Core:   The values not present in any husk in a hump. That is, the values that overlap with the ranges of subsequent lumps. 

## Observations:
### Traversing
    In any hump, starting from the root lump's smallest value, if just the small side of the husks are included until the last lump. 
    That whole lump is included. Then all the largest husks starting from the last lump to the root lump are included. 
    That list will be sorted. But, the core remains unsorted. 
    If, there were no core nodes, this method could be used to produce a fully sorted list. 
### Structure
    Max - There are a maximum number of lumps in a hump, ( (((n-1)/2)+1) 1 single node last lump, and then each other lump is just 1 node in its small husk and 1 in its large husk ).
    Min - If there is just 1 lump, it is fully sorted. 
### Complexity
    Worst case scenario for the basic lumphump sorting algorithm inserting is O(N). 
    This is the max lump scenario, where there are and equivalence of N/2 comparisons to make. 
### Improvements
    I had plans for improvements. They were going to be ways to make the lumps not overlap. Also, there would be the same number of lumps as the size of each lump. This would make each lumphump like a square. 
    I thought this would make it more efficient by limiting the worse-case scenario and the number of lumps need to search.
    I considered these improvements further and realized that they essentially the same thing as have a sorted list with sqrt(N) index pointers throughout. 
    For this reason, I believe this project has concluded with this initial working prototype. 
    Perhaps in the future I will improve the printing functions to show more detail like lump sizes, and also add a random number generator. That way, the size of the data set is all that will be needed to be selected by the user.

## Use
    This program was designed and tested on Debian GNU/Linux 12 (bookworm) x86_64. It was not tested on any other system. 
    The makefile uses gcc as the compiler. It must be installed prior to building using the method below.

### Build
    To build this program;
        1. In command-line, navigate to the directory containing this README.
            * Optional, execute `make clean` to remove any previous build and ouput.
        2. Execute `make` to build the program called _lumpsort_.
### Run
    To run this program;
        1. In command-line, navigate to the directory containing this README.
        2. Build this program, (see above)
        3. Execute `./lumpsort`.
        4. Follow the commands:
            *h:    Display this menu again
            *i:    Insert values into a the lumphump
            *s:    Search for a value in the lumphump
            *r:    Remove a value from the lumphump
            *p:    Print the contents of the lumphump
            *f:    Print the contents of the lumphump to a file
            *q:    Quit this program, lumphump will be lost
        5. Alternatively, if a previous execution produced an output file, it can be used as input by execution `./lumpsort output/filename.lump`. It will quit automatically. 

    Note: output filename's must contain only 0-9, a-z, A-Z or '-', '.', '_' or ' '.
### Uninstall
    To uninstall this program;
        1. In command-line, navigate to the directory containing this README.
        2. Execute `make clean`. Note, this will also remove any previous output files.


## Examples
    _later_

## Contributors
    All files and code were the original ideas and work by Patrick McGrath, 2025.

## License
    Lumpsort Algorithm Demonstration Program
        Copyright (C) 2025  Patrick McGrath
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.