//
//  permute.cpp
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

// A function to permute a list randomly: input is the size of the list, output is a list of numbers randomly ordered.


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Example of using 'permute' in main.cpp:
/* int size = 10;
 int permutedlist2[size];
 int *permutedlist3;
 permutedlist3 = permute(size,permutedlist2);
 
 for (int n=0; n<10; n++)
 {
 cout << permutedlist3[n]<<", ";
 }
 */
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#include "permute.h"
#include <iostream>
#include <time.h>       /* time */
#include <cstdlib>      // std::rand, std::srand
#include <sys/time.h> // linux millisecond random numbers. For Legion

using namespace std;

int *permute(int sizevec, int permutedlist[])
{
        // ===== Seed random numbers:
      //  srand((unsigned int) time(NULL));
   
    
    // Randomly permute the list 0 - NUMSITES, 100 swaps:
    
    //permutedlist[sizevec];
    for (int i=0;i<sizevec;i++)
    {
        permutedlist[i] = i;
    }
    for (int i=0; i<100; i++)
    {
        int r1 = rand() % sizevec;
        int r2 = rand() % sizevec;
        // swap enteries r1 and r2 in perminitsites:
        int h1 = permutedlist[r1];
        permutedlist[r1] = permutedlist[r2];
        permutedlist[r2] = h1;
        
    }
    return permutedlist;
}







