/* 
    File: my_allocator.cpp
*/
#include "BuddyAllocator.h"
#include <iostream>
#include <math.h>
#include <exception>
#include <string>

using namespace std;

BuddyAllocator::BuddyAllocator (uint _basic_block_size, uint _total_memory_length){
	basic_block_size = _basic_block_size;
  total_memory_length = _total_memory_length;
  // BlockHeader* head=FreeList->getHead();
  // FreeList->setHead(alloc(_total_memory_length));

  // FreeList= new LinkedList[_total_memory_length];

    //  (LinkedList*) new LinkedList[total_memory_length]);

  int steps = int(log2(_total_memory_length/_basic_block_size)+1);
  // LinkedList newList[steps];
  
  int block_size = _total_memory_length;

  for(int i =0;i<=steps;i++){
    freeList.push_back(LinkedList());
    // freeListMap.insert(make_pair(block_size, i));
    freeListMap[block_size] = i;
 
    block_size=block_size/2;
    }
  // insert ();  

  begin = (char*)malloc(_total_memory_length);
  BlockHeader* h = (BlockHeader*)begin;
  h->size=_total_memory_length;
  h->next=NULL;
  h->Free=true;
  freeList[0].insert(h);
  for (int i=0; i<freeList.size();i++){
    cout<< "\n \n Stuff inside freeList: \n \n" << freeList[i].getHead()->size << " (size) ... "<<freeList[i].getHead()->Free << " (Free) ... "<<freeList[i].getHead()->next << " (Next) \n";
    
  }
  // avail = (BlockHeader*)(begin)+sizeof(head);
  // FreeList->block = new char [total_memory_length/basic_block_size];
  
 
}

//freeListMap[128] return int index
BuddyAllocator::~BuddyAllocator (){
	free(begin);
}

char* BuddyAllocator::alloc(uint _length) {
  /* This preliminary implementation simply hands the call over the 
     the C standard library! 
     Of course this needs to be replaced by your implementation.
  */
  // return new char [_length];
  int total_request = _length +sizeof(BlockHeader);
  float factor = log(total_request)/log(2);
  int pow_2_ceil = pow(2, ceil(factor));
  int index = int(log2(total_memory_length/pow_2_ceil)+1);
  // bool flag=true;
  int steps=0;
  char* freeBlock;
  try
  {
    if (freeList[index].getHead() != NULL ){return (char*)freeList[index].getHead();}
    for (int i = index-1; i>=0;i--){ 
      if (freeList[i].getHead() != NULL ){
        // if(i!=index){
        //   for
        // }
        // if (freeList[i].if_free()){}
        freeBlock = (char*)freeList[i].getHead();
          for(int i = 0;i<=steps;i++){
            
            BlockHeader* newBlock=(BlockHeader*)split(freeBlock);
            if(newBlock->size==pow_2_ceil){return (char*)newBlock;}
          }
        }
        steps++;
      // else{
      //   if()
      //   split(freeBlock);
      //   i+=2;
      // }        
      
    }throw "No available memory. ";
  }
  catch (string e)
  {
    cout << "Please request another memory size " << e << '\n';
  }
  return NULL;
}

int BuddyAllocator::free(char* _a) {
  /* Same here! */
  // delete _a;
  // return 0;

  free(_a);
}

void BuddyAllocator::debug (){
  
}

char* BuddyAllocator::getbuddy (char * addr){
    BlockHeader* x = (BlockHeader*) addr;
    return (((char*)x-begin)^x->size)+begin;
}

bool BuddyAllocator::isvalid (char * addr){
    BlockHeader* x = (BlockHeader*) addr;  
    return (x->Free==true);

}

char* BuddyAllocator::split (char* block){
  BlockHeader* x = (BlockHeader*) block;
  int index = freeListMap[x->size];
  
  x->size/=2;
  x->next= (BlockHeader*)(block + x->size);
  x->Free=true;

  x->next->size = x->size;
  x->next->Free = true;
  x->next->next = NULL;

  freeList[index+1].insert(x);
  freeList[index].remove((BlockHeader*)block);
  
  return (char*) x;
}

