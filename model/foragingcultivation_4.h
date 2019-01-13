//
//  foragingcultivation_4.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#ifndef Foraging_v5_1_foragingcultivation_4_h
#define Foraging_v5_1_foragingcultivation_4_h

// Go through each site and see if it's occupied.

for (int i=0; i<NUMSITES; i++)
{
    if (sites[i].countocc > 0) // There is at least one family that lives at this site.
    {
        // ~~~~~~~~ Occupied ~~~~~~~~
        
        // Find sum of effort strategies at this site (for use in yield calculations):
        
        sume = 0;
        for (int f=0; f<sites[i].countocc; f++)
        {
            sume = sume + (*sites[i].fam_occ[f]).e_strat;
        }
        
        // Sum of the yields of the individuals at this site (for use in qf/qa equations):
        
        sumyfs = 0;
        sumyas = 0;
        
        for (int f=0; f<sites[i].countocc; f++)
        {
            // For each of the agent's who live at this site:
            
            // Find yields and update agent's fitness
            
            if (farming == 1)
            {
                // Calculate Yields:
                
                if (sume > 1){
                    Yf = (double) (*sites[i].fam_occ[f]).e_strat*sites[i].qual_f/sume;
                } else {
                    Yf = (*sites[i].fam_occ[f]).e_strat*sites[i].qual_f;
                }
                
                if ((sites[i].countocc - sume) > PHI){
                    Ya = (double) (1 - (*sites[i].fam_occ[f]).e_strat)*sites[i].qual_a*PHI/(sites[i].countocc - sume);
                } else {
                    Ya = (1 - (*sites[i].fam_occ[f]).e_strat)*sites[i].qual_a;
                }
            
                // Update agent's fitness:
                
                (*sites[i].fam_occ[f]).fit = Ya + Yf;
                
                // Add to yield count:
                
                sumyfs = sumyfs + Yf;
                sumyas = sumyas + Ya;
            }
            else
            {
                // For the foraging model:
                (*sites[i].fam_occ[f]).fit = (double) sites[i].qual_f/ (double)sites[i].countocc;
            }
            
            
            // Add to the counter of how long the group has been at this site.
            
            (*sites[i].fam_occ[f]).mcount ++;
        }
        
        // Site qualities:
        
        if (farming == 1)
        {
            if (sparvar == 0 | sparvar == 2)
            {
                sites[i].qual_f = sites[i].qual_f + GR*sites[i].qual_f*(1 - sites[i].qual_f) - LAMBDA*(1- (double)1/(1+sites[i].countocc))*sumyfs - BETA*sumyas;
                sites[i].qual_a = sites[i].qual_a + sumyas*sites[i].qual_a*(1 - sites[i].qual_a) - DELTA*sites[i].qual_a;
            } else {
                // When there was spatial variability (either structured or not) each site can have different parameter values:
                
                sites[i].qual_f = sites[i].qual_f + GRblended[i]*sites[i].qual_f*(1 - sites[i].qual_f) - LAMBDAblended[i]*(1- (double)1/(1+sites[i].countocc))*sumyfs - BETAblended[i]*sumyas;
                sites[i].qual_a = sites[i].qual_a + sumyas*sites[i].qual_a*(1 - sites[i].qual_a) - DELTAblended[i]*sites[i].qual_a;
            }
        } else {
            if (sparvar == 0 | sparvar == 2)
            {
                sites[i].qual_f = sites[i].qual_f + GR*sites[i].qual_f*(1 - sites[i].qual_f) - LAMBDA*(1- (double)1/(1+sites[i].countocc))*sites[i].qual_f;
                sites[i].qual_a = 0;
            } else {
                // When there was spatial variability (either structured or not) each site can have different parameter values:
                sites[i].qual_f = sites[i].qual_f + GRblended[i]*sites[i].qual_f*(1 - sites[i].qual_f) - LAMBDAblended[i]*(1- (double)1/(1+sites[i].countocc))*sites[i].qual_f;
                sites[i].qual_a = 0;
            }
        }
        
        // Check limits:
        
        // Make sure q_f is within limits:
        if (sites[i].qual_f < MINQF)
        {
            sites[i].qual_f = MINQF;
        }
        if (sites[i].qual_f > 1)
        {
            sites[i].qual_f = 1;
        }
        // Make sure q_a is within limits:
        if (sites[i].qual_a < MINQA)
        {
            sites[i].qual_a = MINQA;
        }
        if (sites[i].qual_a > 1)
        {
            sites[i].qual_a = 1;
        }
        
    }
    else
    {
        // ~~~~~~~~ Unoccupied ~~~~~~~~
        
        // Site qualities:
        
        if (farming == 1)
        {
            if (sparvar == 0 | sparvar == 2)
            {
                sites[i].qual_f = sites[i].qual_f + GR*sites[i].qual_f*(1 - sites[i].qual_f);
                sites[i].qual_a = sites[i].qual_a - DELTA*sites[i].qual_a;
            } else {
                sites[i].qual_f = sites[i].qual_f + GRblended[i]*sites[i].qual_f*(1 - sites[i].qual_f);
                sites[i].qual_a = sites[i].qual_a - DELTAblended[i]*sites[i].qual_a;
            }
        } else {
            if (sparvar == 0 | sparvar == 2)
            {
                sites[i].qual_f = sites[i].qual_f + GR*sites[i].qual_f*(1 - sites[i].qual_f);
                sites[i].qual_a = 0;
            } else {
                sites[i].qual_f = sites[i].qual_f + GRblended[i]*sites[i].qual_f*(1 - sites[i].qual_f);
                sites[i].qual_a = 0;
            }
        }
        
        
        // Check limits:
        
        // Make sure q_f is within limits:
        if (sites[i].qual_f < MINQF)
        {
            sites[i].qual_f = MINQF;
        }
        if (sites[i].qual_f > 1)
        {
            sites[i].qual_f = 1;
        }
        // Make sure q_a is within limits:
        if (sites[i].qual_a < MINQA)
        {
            sites[i].qual_a = MINQA;
        }
        if (sites[i].qual_a > 1)
        {
            sites[i].qual_a = 1;
        }
    }
}


// ...............................................................
// Make sure family fitness is within limits:

for (int i=0; i<numfams; i++)
{
    if (families[i].fit > 1)
    {
        families[i].fit = 1;
    }
}




#endif
