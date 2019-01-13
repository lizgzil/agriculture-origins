//
//  movement_7.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#ifndef Foraging_v5_1_movement_7_h
#define Foraging_v5_1_movement_7_h


// [This section of code is very different to how it had to be when there could be no co-occupation of sites].

// We need to always go through the families in a random order so that there is no preference for being having a low ID number.


if (numfams != 0) // Only do this step if there are agents left!
{
    permutedfam2 = permute(numfams,permutedfam1);
    int i;
    
    // Scroll through all families - if they are ready to move, then they move.
    
    randsite = NUMSITES; // Initialised to the empty site
    prevfampoint = &nonfam[0]; // previous family pointer for shifting, initialised to the empty family.
    tempprevfampoint = &nonfam[0]; // temporary pointer
    
    for (int ii=0; ii<numfams; ii++) // Go through all the alive families
    {
    here8:
        
        i = permutedfam2[ii]; // Family ID
        
        if ((families[i].mcount != 0)&&(families[i].siteocc != NUMSITES)) // If the family hasn't just got to a site and the family isn't dead
        {
            randmov = (double)(rand() % 1000 + 1)/1000;  // A random number between (0, 1].
            randmov2 = (double)(rand() % 1000 + 1)/1000; // A random number between (0, 1].
            //if ((randmov2 <= families[i].m_strat) || (randmov <= (1 - families[i].fit))) // If it's time to move on, or neccessary to move. RELAXED - 29TH JUNE
            if (randmov2 <= families[i].m_strat) // If it's time to move on.
            {
                oldsite = families[i].siteocc;
                
                
                
                // The new site:
                // double potfit;
                // Create the vector for attractiveness of all sites to where this agent is currently.
                for (int s=0; s<NUMSITES; s++)
                {
                    sitedist = (double)(abs(sites[oldsite].coords[0] - sites[s].coords[0]) + abs(sites[oldsite].coords[1] - sites[s].coords[1]) + abs(sites[oldsite].coords[2] - sites[s].coords[2]))/2; // The distance from the current site to site s.
                    
                    if (farming == 1)
                    {
                        // Calculate the sum of the effort strategies at this site plus if this agent lived there:
                        
                        sume = 0;
                        for (int f=0; f<sites[s].countocc; f++)
                        {
                            sume = sume + (*sites[s].fam_occ[f]).e_strat;
                        }
                        sume = sume + families[i].e_strat;
                        
                        if (sume > 1){
                            Yf = (double) families[i].e_strat*sites[s].qual_f/sume;
                        } else {
                            Yf = families[i].e_strat*sites[s].qual_f;
                        }
                        
                        if ((sites[s].countocc + 1 - sume) > PHI){
                            Ya = (double) (1 - families[i].e_strat)*sites[s].qual_a*PHI/(sites[s].countocc + 1 - sume);
                        } else {
                            Ya = (1 - families[i].e_strat)*sites[s].qual_a;
                        }
                        
                        // Potential fitness of site s for this agent:
                        
                        potfit = Ya + Yf;
                    } else {
                        potfit = (double)sites[s].qual_f/(sites[s].countocc+1); // Potential fitness of site s for this agent.
                    }
                    
                    
                    if (potfit > 1)
                    {
                        potfit = 1;
                    }
                    
                    siteattract[s] = (1 - ((double) sitedist/maxdistance))*potfit;
                }
                
                // So now the site this agent moves to (randsite) is weighted by siteattract.
                // (algorithm from the internet).
                
                // a. Sum all the attractivenesses:
                sumattract = 0;
                for (int s=0; s<NUMSITES; s++)
                {
                    sumattract = sumattract + siteattract[s];
                }
                
                // b. Pick a random number between 0 and the sum
                randnum = ((double)(rand() % 1000)/1000)*sumattract; // [0,sumattract)
                
                // c. Go through the items one at a time, subtracting their weight from your random number, until you get the item where the random number is less than that item's weight
                
                for (int s = 0; s < NUMSITES; s++)
                {
                    if (randnum < siteattract[s])
                    {
                        randsite = s;
                        break;
                    }
                    randnum = randnum - siteattract[s];
                }
                
                if (randsite != oldsite) // Changes are only made if the new site is different from the old site.
                {
                    // There is no conflict in this version, so if the agent selects to go somewhere, it will go there no matter what.
                    
                    // **** Changes to the old site: ****
                    
                    // The old site's list of members has this family removed:
                    for (int m=sites[families[i].siteocc].countocc - 1; m >= 0; --m) // Decremental for loop, to go through the list in reverse - shuffling down the list until you get to the family who just moved.
                    {
                        if (sites[families[i].siteocc].fam_occ[m] != &families[i])
                        {
                            tempprevfampoint = sites[families[i].siteocc].fam_occ[m];
                            sites[families[i].siteocc].fam_occ[m] = prevfampoint;
                            prevfampoint = tempprevfampoint;
                            
                        }
                        else
                        {
                            sites[families[i].siteocc].fam_occ[m] = prevfampoint;
                            break; // Don't need to go down the list anymore. The ones before the agent who has moved stay the same.
                        }
                    }
                    
                    // The old site is deducted a count, which might mean it is now empty:
                    sites[families[i].siteocc].countocc = sites[families[i].siteocc].countocc - 1;
                    
                    if (sites[families[i].siteocc].countocc == 0)
                    {
                        sites[families[i].siteocc].occ = 0;
                    }
                    
                    sitedist = (double)(abs(sites[oldsite].coords[0] - sites[randsite].coords[0]) + abs(sites[oldsite].coords[1] - sites[randsite].coords[1]) + abs(sites[oldsite].coords[2] - sites[randsite].coords[2]))/2; // The distance from the old site to the new site.
                    
                    // Add this move to the sum of the distances moved
                    summovedistance = summovedistance + sitedist;
                    numbermoves ++;
                    
                    // **** Changes to the family: ****
                    
                    // Then this family moves to a random other site.
                    
                    families[i].siteocc = randsite;
                    families[i].mcount = 0;
                    families[i].fit = families[i].fit - ETA*sitedist; // The cost of moving this distance
                    
                    // **** Changes to the new site: ****
                    
                    // Change qualities of the site.
                    sites[randsite].occ = 1; // It may have been this before.
                    sites[randsite].countocc = sites[randsite].countocc + 1; // There is one more family at this site.
                    sites[randsite].fam_occ[sites[randsite].countocc - 1] = &families[i]; // This family is now on the site's members list.
                }
            }
        }
    }
}

#endif
