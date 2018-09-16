/* 
    File: my_allocator.h

    Original Author: R.Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 08/02/08

    Modified: Huy Pham

*/

#ifndef _BuddyAllocator_h_                   // include file only once
#define _BuddyAllocator_h_
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdexcept>
using namespace std;
typedef unsigned int uint;

/* declare types as you need */
struct NotEnoughMemException : std::range_error {
  explicit NotEnoughMemException(char const* msg=NULL): range_error(msg) {}
};

class BlockHeader{
	// decide what goes here
	// hint: obviously block size will go here
	public:

	bool Free;
	int size;
	BlockHeader* next;

	// BlockHeader (bool Free, int size, BlockHeader *next );
	
};

class LinkedList{
	// this is a special linked list that is made out of BlockHeader s. 
private:
	BlockHeader* head=NULL;		// you need a head of the list
	// char* block;
public:
	BlockHeader* setHead(char* memStart){ head=(BlockHeader*) memStart;}
	BlockHeader* getHead(){return head;}
	BlockHeader* traverse();
	bool if_free(){return head-> Free;}
	void insert (BlockHeader* b){	// adds a block to the list
		// cout << "\n Insert: "<<b->size<<endl;
		b->Free=true;
		if(head==NULL){ head=b;b->next=NULL;  }//
		else{
			b->next=head;
			head=b;
		 }
		
	}
	
	void remove (BlockHeader* b){  // removes a block from the list

		//  else head = NULL;
		//b->next=NULL;
		//b->Free=false;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~``
		// b->Free=false;
		
		//  int total_block = 0;
		// BlockHeader* curr = head;
		// BlockHeader* prev =NULL;
	// if (curr==b && curr->next==NULL) {head=NULL;b->next=NULL;}
		
		int total_block = 0;
		BlockHeader* curr = head;
		BlockHeader* prev =head;
	
		// cout<<"\n \n";
	while(curr!=NULL){
		

		prev = curr;
		curr=curr->next;
		if (curr==b) {
			// cout << "found b to remove: " <<endl;
 			prev->next = curr->next;
			curr->next=NULL;
			// cout<<"\n \n total_block: "<<total_block;
			if(head==b	&&	b->next==NULL) cout<<head; setHead(NULL);
			break;
		}

		total_block++;

	}
	if(curr==NULL){head=b->next;}
	b->Free=false;
		
	}
};


class BuddyAllocator{
private:
	/* declare member variables as necessary */
	vector<LinkedList> freeList; 
	char* initial;
	unordered_map<int, int> freeListMap;
	// LinkedList *FreeList;
	// LinkedList FreeList[];

	uint basic_block_size, total_memory_length;

private:
	/* private function you are required to implement
	 this will allow you and us to do unit test */
	
	char* getbuddy (char * addr); 
	// given a block address, this function returns the address of its buddy 
	
	bool isvalid (char *addr);
	// Is the memory starting at addr is a valid block
	// This is used to verify whether the a computed block address is actually correct 

	bool arebuddies (char* block1, char* block2);
	// checks whether the two blocks are buddies are not

	char* merge (char* block1, char* block2);
	// this function merges the two blocks returns the beginning address of the merged block
	// note that either block1 can be to the left of block2, or the other way around

	char* split (char* block);
	// splits the given block by putting a new header halfway through the block
	// also, the original header needs to be corrected


public:
	BuddyAllocator (uint _basic_block_size, uint _total_memory_length); 
	/* This initializes the memory allocator and makes a portion of 
	   ’_total_memory_length’ bytes available. The allocator uses a ’_basic_block_size’ as 
	   its minimal unit of allocation. The function returns the amount of 
	   memory made available to the allocator. If an error occurred, 
	   it returns 0. 
	*/ 

	~BuddyAllocator(); 
	/* Destructor that returns any allocated memory back to the operating system. 
	   There should not be any memory leakage (i.e., memory staying allocated).
	*/ 

	char* alloc(uint _length); 
	/* Allocate _length number of bytes of free memory and returns the 
		address of the allocated portion. Returns 0 when out of memory. */ 

	int free(char* _a); 
	/* Frees the section of physical memory previously allocated 
	   using ’my_malloc’. Returns 0 if everything ok. */ 
   
	void debug ();
	/* Mainly used for debugging purposes and running short test cases */
	/* This function should print how many free blocks of each size belong to the allocator
	at that point. The output format should be the following (assuming basic block size = 128 bytes):

	128: 5
	256: 0
	512: 3
	1024: 0
	....
	....
	 which means that at point, the allocator has 5 128 byte blocks, 3 512 byte blocks and so on.*/
};

#endif 
