//
//  initialisationbeforerepeats_1.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#ifndef Foraging_v5_1_initialisationbeforerepeats_1_h
#define Foraging_v5_1_initialisationbeforerepeats_1_h

// ===== Make structures:

site sites[NUMSITES];           // NUMSITES many sites.
family families[MAXNUMFAMS];    // MAXNUMFAMS many families at the most
family nonfam[1];               // The 'none' family structure which occupies unoccupied sites, different to 'empty/dead' family structures which have the potential to be alive.

// ........................................
// ===== Initialise family structures:

for (int i=0; i<MAXNUMFAMS; i++)
{
    families[i].famID = i;
}

// ........................................
// ===== Initialise site structures:

// coord2site : A vector of the site IDs. Dimensions are the site coordinates. So you can access which siteID is at a certain coordinate. The maximum each dimension is is:
int csx = spatialx + spatialy/2;
int csy = spatialx + (spatialy-1)/2;
int csz = spatialy;
int coord2site[csx][csy][csz]; // Not every combination will be used.

int sitecoord2[3];

int *sitecoord;
for (int i=0; i<NUMSITES; i++)
{
    // Find the 3D hexagonal coordinates of the site:
    sitecoord = hexcoords(spatialx,spatialy,sitecoord2,i); // i is the site number
    
    for (int s=0; s<3; s++)
    {
        sites[i].coords[s] = sitecoord[s];
    }
        
    sites[i].siteID = i;            // Sites always keep their identity.
    coord2site[sites[i].coords[0]][sites[i].coords[1]][sites[i].coords[2]] = sites[i].siteID;
}


// The maximum distance movable in this world:
// It's the maximum of either the distance from site 0 to the last site, or site topleft to site bottomright

int dist1 = (double)(abs(sites[0].coords[0] - sites[NUMSITES-1].coords[0]) + abs(sites[0].coords[1] - sites[NUMSITES-1].coords[1]) + abs(sites[0].coords[2] - sites[NUMSITES-1].coords[2]))/2;
int dist2 = (double)(abs(sites[spatialy-1].coords[0] - sites[NUMSITES-spatialy].coords[0]) + abs(sites[spatialy-1].coords[1] - sites[NUMSITES-spatialy].coords[1]) + abs(sites[spatialy-1].coords[2] - sites[NUMSITES-spatialy].coords[2]))/2;
int maxdistance = max(dist1, dist2);


#endif
