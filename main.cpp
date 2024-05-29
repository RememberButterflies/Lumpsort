#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "include/node.h"
#include "include/lump.h"
#include "include/fun.h"
#include "include/error.h"











int main(){

	// size of list being created
	srand(time(NULL));
	int size = rand() % 100 + 1;
	std::cout << "size of list being created is: "<< size << std::endl;

	// populate list
	node* start = NULL;
	node* last = NULL;
	for (int i = 0; i < size; i++){
		node* temp = new node;
		temp->val = rand() % 100 + 1;
		if (start == NULL){
			start = temp;
			last = temp;
		} else {
			last->next = temp;
			last = temp;
		}
		std::cout << "The " << i+1 << "th random value is: " << temp->val << std::endl;
	}

// lumpstack
	lump* L = lumpstack(start);

	lumphuskprint(L);

       	return 0;	
}
