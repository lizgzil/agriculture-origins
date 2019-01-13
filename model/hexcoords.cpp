//
//  hexcoords.cpp
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//
// Returns the 3 coordinates which describe where site i is

#include "hexcoords.h"
#include <iostream>
#include <time.h>       /* time */

using namespace std;

int *hexcoords(int spatialx, int spatialy, int sitecoord[], int i)
{
    if (spatialy%2 ==0 ) // If spatialy is even
    {
        // x coord (sitecoord[0]):
        
        if (i%2 == 0) // If i is even
        {
            sitecoord[0] = (i/ spatialy) + (i% spatialy)/2;
        }
        else // i is odd
        {
            if ((i+1)% spatialy == 0) // The top row
            {
                sitecoord[0] = ((i-1)/ spatialy) + ((i-1)% spatialy)/2 +1;
            }
            else // Not the top row
            {
                sitecoord[0] = ((i+1)/ spatialy) + ((i+1)% spatialy)/2;
            }
        }
        
        // y coord (sitecoord[1]):
        
        if (i%2 == 0) // If i is even
        {
            sitecoord[1] =  (i% spatialy)/2 - (i/ spatialy) + (spatialx-1);
        }
        else // i is odd
        {
            sitecoord[1] =  ((i-1)% spatialy)/2 - ((i-1)/ spatialy) + (spatialx-1);
        }
        
        // z coord (sitecoord[2]):
        
        sitecoord[2] = i%spatialy;
    }
    else // if spatialy is odd
    {
        // x coord (sitecoord[0]):
        
        if ((i+1)% spatialy == 0) // The top row
        {
            sitecoord[0] = (i/ spatialy) + (i% spatialy)/2;
        }
        else
        {
            sitecoord[0] = (i/ spatialy) + ((i+1)% spatialy)/2;
        }
        
        // y coord (sitecoord[1]):
        
        
        sitecoord[1] =  ((i)% spatialy)/2 - ((i)/ spatialy) + (spatialx-1);
        
        
        // z coord (sitecoord[2]):
        
        sitecoord[2] = i%spatialy;
        
        
    }
    return sitecoord;
    
}



