//
//  structures.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#ifndef Sedentism_v4_1_structures_h
#define Sedentism_v4_1_structures_h

#include "variables.h" // Where MAXNUMFAMS is


//===== Properties of a family:
struct family{
public:
    int famID;        // Family I.D.
    double fit;       // Fitness
    double e_strat;     // Effort strategy, the proportion of effort an agent gives to foraging.
    double m_strat;     // Migration strategy, the probability they try to move to a different site each iteration.
    double drifttest;  // A 'strategy' which does nothing, but mutates in the same way as the others, so should just drift
    int mcount;       // A counter of how long they've been at a site for.
    int siteocc;      // The group occupies siteID or NUMSITES if it is a dead/empty family.
    int oldsiteocc;   // If this agent just moved (to limbo too), then oldsiteocc will be its previous site ID
    
};


//===== Properties of a site:
struct site{
public:
    int siteID;         // Site I.D.
    int occ;            // Whether it's occupied or not, occupied = 1, empty = 0, transition state (for migration step) = 2
    int countocc;       // A counter of how many agents are at this site.
    double qual_f;      // Foraging resource quality
    double qual_a;      // Farming resource quality
    family *fam_occ[MAXNUMFAMS];   // A pointer to a vector with the numbers (row number not ID) of the families that occupy this site/ the "empty" family.
    int coords[3];      // The 3 hexagonal coordinates the site has x,y,z 
};


#endif
