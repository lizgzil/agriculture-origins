//
//  birth_6.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#ifndef Foraging_v5_1_birth_6_h
#define Foraging_v5_1_birth_6_h

// only if numfams < MAXNUMSFAMS


if (numfams !=0 ) // There are only births if there are agents left
{
    randbirth = (double)(rand() % 1000 + 1)/1000;  // A random number between (0, 1].
    
    // If numfams is close to MAXNUMFAMS then the families with a lower ID will have a preference for birth before family carrying capacity is reached. Hence, we need to go through the families in a random order.
    
    permutedfambir2 = permute(numfams,permutedfambir);
    int f;
    
    // Go through all the alive families in a random order.
    for (int ff=0; ff<numfams; ff++)
    {
        f = permutedfambir2[ff]; // Family ID (from permuted list)
        
        if (families[f].fit >= deathfit) // If they are alive.
        {
            // Will there be a birth?
            
            randbirth = (double)(rand() % 1000 + 1)/1000;  // A random number between (0, 1].
            
            //probbirth = (double) fu*(pow((families[f].fit-deathfit)/(1-deathfit),0.5));
            
            probbirth = fu - ((double) fu/log(deathfit))*log(families[f].fit);
            
            if ((randbirth <= probbirth)&&(numfams < MAXNUMFAMS)) // There will be a birth and there is space for a new group.
            {
                countallbirths = countallbirths + 1;
                
                if (abc == 0)
                {
                    if (saveless == 0)
                    {
                        fprintf(birthstuff, "%d,%d, ", rr, w);
                    }
                }
                
                
                // Use the next empty/dead family (living families are in rows 0 to (numfams-1):
                
                int babyID = numfams;//families[numfams].famID;
                
                families[babyID].famID = uniquefamID;
                uniquefamID++; // The unique ID for the next baby born.
                
                // The baby lives at the parent's site.
                families[babyID].siteocc = families[f].siteocc;
                
                // Update the site and the new families properties. Parent families are unaffected.
                
                families[babyID].fit = (double)(rand() % (100-ROUND_2_INT(deathfit*100)+1))/100 + deathfit; // Fitness randomly assigned between [deathfit,1] (shouldn't make a dead group) changed 27/08/2016
                families[babyID].mcount = 0; // This is updated when they make food.
                
                if (families[babyID].fit < deathfit)
                {
                    families[babyID].fit = deathfit; // shouldn't make a dead group
                }
                if (families[babyID].fit > 1)
                {
                    families[babyID].fit = 1;
                }
                
                // change from 17/10/2016 - babies just have their parent's strategies:
                
                families[babyID].e_strat = families[f].e_strat;
                families[babyID].m_strat = families[f].m_strat;
                families[babyID].drifttest = families[f].drifttest;
                

                sites[families[babyID].siteocc].occ  = 1;
                sites[families[babyID].siteocc].countocc = sites[families[babyID].siteocc].countocc + 1;
                sites[families[babyID].siteocc].fam_occ[sites[families[babyID].siteocc].countocc - 1] = &families[babyID];
                
                // Add to numfams count:
                numfams++;
                
                
                if (abc == 0)
                {
                    if (saveless == 0)
                    {
                        fprintf(birthstuff, "%d, %d\n", families[f].famID, families[babyID].famID);
                    }
                }
                
            }
        }
    }
    
}


#endif
