//
//  death_5.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#ifndef Foraging_v5_1_death_5_h
#define Foraging_v5_1_death_5_h

countalldead = 0; // from all the sites
int originalnumfams = numfams; // before death happened.

for (int i=0; i<NUMSITES; i++)
{
    originalcount = sites[i].countocc; // Store original count of number of agents at this site, before you change it every iteration.
    for (int j=0; j<originalcount; j++) // won't go through loop if there is no-one at this site
    {
        
        if ((sites[i].fam_occ[j] != &nonfam[0])&&((*sites[i].fam_occ[j]).fit<deathfit)) // The family that occupies this site is not the none family and it's fitness is less than a threshold of DEATHFIT (very low, but not = 0)
        {
            
            if (abc == 0)
            {
                if (saveless==0)
                {
                    fprintf(exfams, "%d,%d,%d\n", rr,w,(*sites[i].fam_occ[j]).famID);
                }
                
            }
            
            countalldead = countalldead + 1;
            
            (*sites[i].fam_occ[j]).siteocc = NUMSITES; // The family now occupies the 'outside' site
            (*sites[i].fam_occ[j]).oldsiteocc = NUMSITES;
            (*sites[i].fam_occ[j]).mcount = 0;         // Counter set back to 0
            (*sites[i].fam_occ[j]).fit = 0;            //
            sites[i].countocc = sites[i].countocc - 1; // Counter of number of occupying agents is decreased.
            sites[i].fam_occ[j] = &nonfam[0];          // The site is now 'occupied' by the 'none' family. //NEEDCHANGE
            
            numfams = numfams - 1; // The number of families decreases.
        }
    }
    
    // So now you have a number of agents at this site, some of which have died. Go through the list and shift down if there is a gap.
    
    countdead = 0;
    for (int j=0; j<originalcount; j++) // won't go through loop if there is no-one at this site
    {
        if (sites[i].fam_occ[j] == &nonfam[0]) // If this family just died
        {
            countdead = countdead + 1;
        }
        else
        {
            sites[i].fam_occ[j-countdead] = sites[i].fam_occ[j]; // Move agent ID down
        }
    }
    // So now, the list of occupying families should all be alive, and go from sites[i].fam_occ[0 - countocc]
}


for (int i=0; i<NUMSITES; i++)
{
    if (sites[i].countocc == 0)
    {
        sites[i].occ = 0;  // If there is a 0 count of agents, then the site is now unoccupied
    }
}


// Families outside the sites with 0 fitness will already have these properties.


// ...............................................................
// 2.5. REORDERING. Make sure the first numfams agents are the living ones.

// countalldead agents died. There used to be originalnumfams alive.


countdead = 0;
for (int j=0; j<originalnumfams; j++) // Go through all the families which are alive or just died.
{
    if (families[j].fit < deathfit) // If this family just died
    {
        countdead = countdead + 1;
    }
    else
    {
        // If this family is still alive move it down countdead rows
        // It's family ID remains the same! (needed so we don't need to update who's at the site)
        
        // The site this family occupies, must have it's fam_occ list replaced from the old family pointer to the reshuffled one.
        
        for (int fo=0; fo<sites[families[j].siteocc].countocc; fo++) // Go through the list of families which occupy the site this family is at
        {
            if (sites[families[j].siteocc].fam_occ[fo] == &families[j]) // When you get to the old pointer, update it.
            {
                sites[families[j].siteocc].fam_occ[fo] = &families[j-countdead];
                break;
            }
        }
        
        families[j-countdead].famID = families[j].famID;
        families[j-countdead].fit = families[j].fit;
        families[j-countdead].e_strat = families[j].e_strat;
        families[j-countdead].m_strat = families[j].m_strat;
        families[j-countdead].drifttest = families[j].drifttest;
        families[j-countdead].mcount = families[j].mcount;
        families[j-countdead].siteocc = families[j].siteocc;
        families[j-countdead].oldsiteocc = families[j].oldsiteocc;
    }
}



#endif
