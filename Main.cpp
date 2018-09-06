#include "Ackerman.h"
#include "BuddyAllocator.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char ** argv) {
  // int aflag = 0;
  // int bflag = 0;
  // char *cvalue = NULL;
  // int index;
  // int c;

  int basic_block_size = 128, memory_length = 512 * 1024;
//  while ((c = getopt (argc, argv, "abc:")) != -1)
//     switch (c)
//       {
//       case 'a':
//         aflag = 1;
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

  // test memory manager
  // Ackerman* am = new Ackerman ();
  // am->test(allocator); // this is the full-fledged test. 
  
  // destroy memory manager
  delete allocator;
}
