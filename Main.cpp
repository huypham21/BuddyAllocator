#include "Ackerman.h"
#include "BuddyAllocator.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int main(int argc, char ** argv) {
  // int aflag = 0;
  // int bflag = 0;
  // char *cvalue = NULL;
  // int index;
  // int c;

  int basic_block_size = 128, memory_length = 512*1024;
//  while ((c = getopt (argc, argv, "abc:")) != -1)
//     switch (c)
//       {
//       case 'b':
//         aflag = argv;
//         break;
//       case 'b':
//         bflag = 1;
//         break;
//       case 'c':
//         cvalue = optarg;
//         break;
//       case '?':
//         if (optopt == 'c')
//           fprintf (stderr, "Option -%c requires an argument.\n", optopt);
//         else if (isprint (optopt))
//           fprintf (stderr, "Unknown option `-%c'.\n", optopt);
//         else
//           fprintf (stderr,
//                    "Unknown option character `\\x%x'.\n",
//                    optopt);
//         return 1;
//       default:
//         abort ();
//       }
  // create memory manager
  BuddyAllocator * allocator = new BuddyAllocator(basic_block_size, memory_length);
  BlockHeader* mem1 = (BlockHeader*)allocator->alloc(14);
  BlockHeader* mem2 = (BlockHeader*)allocator->alloc(14);

// cout << "\n \n ---Size of mem1 = " << mem1->size <<endl;
// BlockHeader* mem2 = (BlockHeader*)allocator->alloc(60);
// cout << "\n \n ---Size of mem2 = " << mem2->size <<endl;
// BlockHeader* mem3 = (BlockHeader*)allocator->alloc(60);
// cout << "\n \n ---Size of mem3 = " << mem3->size <<endl;
// int free = allocator->free((char*)mem2); cout<< " mem 2 free true? "<< free << endl;
// free = allocator->free((char*)mem3); cout<< " mem 3 free true? "<< free << endl;
// int free = allocator->free((char*)mem1); cout<< " mem 1 free true? "<< free << endl;
  // test memory manager
  Ackerman* am = new Ackerman ();
  am->test(allocator); // this is the full-fledged test. 
  allocator->debug();
  
  // destroy memory manager
   delete allocator; 
  
}
//break BuddyAllocator.cpp:139