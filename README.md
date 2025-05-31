# Lumpsort
Lumpsort algorithm I am designing for fun. I half finished it a few years ago. But, moved on to other things. 
I don't think it is particular efficient. But it was interesting. 

This is an attempt to rebuild it from memory, and hopefully better now. 

Idea:
A binary search tree will take a new value to insert, and check recursively "is the value less than the current value, or is it greater than or equal to the current value?" and then inserts it at a LOWER level than the current value. 
My thought was, what if instead of a single node as the current value, it was a sorted list. Each list would have a largest and smallest value and 0 or more internal values. 
Then, when inserting a new value, you would recursively check, "is the value less than the current list's smallest value, or is it greater than or equal to the current list's largest value, or is it between them?" If the answer was yes for the first question, the value is the new smallest for that list. Else, if the 2nd answer was yes, then its the new largest. Otherwise, recursively check the next lists. If the end is reached, it is a new list by itself.

Terminology:
Lump:   Each sorted list.
Hump:   A series of nested lumps, starting from the bottom.
Husk:   The smallest and largest portion of a lower lump, where each lowest value is lesser than each subsequent lump, and similar for the largest values. 
Core:   The values not present in any husk in a hump.

Observations:
Traversing - In any hump, starting from the bottom lump's smallest value, if just the small side of the husks are included until the last lump. That lump is included. Then all the largest husks starting from the top to the bottom are included. That list will be sorted. But, the core remains unsorted. 
Structure - Max - If there are a maximum number of lumps in a husk, ( (((n-1)/2)+1) 1 single node top lump, and then each other lump is just 1 single node small and large husk ), then following the previous traversing will give a fully sorted list. When a hump has no core, it is called "all-husk."
Structure - Min - If there is just 1 lump, it is fully sorted. 
Structure - Min/Max - If the 2 extremes of the structure are sorted, then what about in between? Is it better to have all-husk? What if it were the middle of min and max, that is there are sqrt(n) lumps, each sqrt(n) long?

Implementation and use:
This program is written in c++ and uses command line interaction. The user is asked repeatedly to either insert, search, or remove a value, print or quit. 

Plan - The planned order of features to implement:
    Skeleton of program, including ui, print and quit.
    Insert
    Search
    Remove
Potentially later:
    All-husk mode
    Restructure existing hump.
