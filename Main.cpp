#include "Ackerman.h"
#include "BuddyAllocator.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int main(int argc, char ** argv) {
  int c;


  int basic_block_size = 128, memory_length = 512*1024;
 while ((c = getopt (argc, argv, "b:s:")) != -1)
    switch (c)
      {
      case 'b':
        basic_block_size = atoi(optarg);
        break;
      case 's':
        memory_length = atoi(optarg);
        break;
      case '?':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }

  // create memory manager
  BuddyAllocator * allocator = new BuddyAllocator(basic_block_size, memory_length);
//   char* mem1 = allocator->alloc(14);
//   allocator->debug();

  // test memory manager
  Ackerman* am = new Ackerman ();
  am->test(allocator); // this is the full-fledged test. 
  allocator->debug();
  
  // destroy memory manager
   delete allocator; 
  
}