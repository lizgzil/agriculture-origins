//
//  initialisationeachrepeat_2.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#ifndef Foraging_v5_1_initialisationeachrepeat_2_h
#define Foraging_v5_1_initialisationeachrepeat_2_h

// ........................................
// Initialise family structures:

numfams = INITNUMFAMS;      // Reset the number of families.

uniquefamID = 0; // A unique family ID for every new agent.

sumeff = 0;
summob = 0;
sumdrift = 0;

// ===== Just the alive families:
for (int i=0; i<INITNUMFAMS; i++)
{
    families[i].famID = i;
    
    
    if (sameinitialcond == 0)
    {
        // Different initial conditions every repeat of the model
        families[i].fit = (double)(rand() % (100-ROUND_2_INT(deathfit*100)+1))/100 + deathfit; // Fitness randomly assigned between [deathfit,1] (shouldn't make a dead group) changed 27/08/2016
        
        families[i].e_strat = (double)(rand() % (100-ROUND_2_INT(INITLOWERE*100)+1))/100 + INITLOWERE; // Effort randomly assigned between [INITLOWERE,1]
        families[i].m_strat = (double)(rand() % (100-ROUND_2_INT(INITLOWERM*100)+1))/100 + INITLOWERM; // Mobility randomly assigned between [INITLOWERM,1] changed 27/08/2016
        families[i].drifttest = (double)(rand() % (100-ROUND_2_INT(INITLOWERM*100)+1))/100 + INITLOWERM; // Drift randomly assigned between [INITLOWERM,1] changed 08/09/2016
        
        if (seedinit == 1 & i == 0)
        {
            // The first agent is the seed agent and will get a smaller strategy values, update this agent's strategies
            families[i].e_strat = seedstrat;
            families[i].m_strat = seedstrat;
            families[i].drifttest = seedstrat;
        }
        
        
        // If the strategies are 0 or 1 set to 0.01 and 0.99
       
        if (families[i].e_strat < 0.01)
        {
            families[i].e_strat = 0.01;
        }
        if (families[i].e_strat > 0.99)
        {
            families[i].e_strat = 0.99;
        }
        
        if (farming == 0)
        { 
            families[i].e_strat = 1; // If you dont want to use the farming model, make all their strategies full foragers
        }
        
        if (families[i].m_strat < 0.01)
        {
            families[i].m_strat = 0.01;
        }
        if (families[i].m_strat > 0.99)
        {
            families[i].m_strat = 0.99;
        }
        
        if (families[i].drifttest < 0.01)
        {
            families[i].drifttest = 0.01;
        }
        if (families[i].drifttest > 0.99)
        {
            families[i].drifttest = 0.99;
        }
        
        families[i].siteocc = rand() % NUMSITES; // Go to a random site in between [0, NUMSITES -1], changed 27/08/2016
    }
    else
    {
        // The same initial conditions every repeat of the model
        families[i].fit = initialfitnesses[i];
        families[i].e_strat = initialefforts[i];
        families[i].m_strat = initialmobilities[i];
        families[i].drifttest = initialdrifts[i];
        families[i].siteocc = initialsites[i];
    }
    
    
    families[i].mcount = 0;     // Not at a site yet.
    
    if (families[i].fit < deathfit)
    {
        families[i].fit = deathfit; // death with fit < deathfit, so fit = deathfit is not dead
    }
    
    if (families[i].fit > 1)
    {
        families[i].fit = 1;
    }
    
    families[i].oldsiteocc = NUMSITES;
    
    sumeff = sumeff + families[i].e_strat;
    summob = summob + families[i].m_strat;
    sumdrift = sumdrift + families[i].drifttest;
    
}


// Save the initial mean effort, mobility and null strategies.

// Calculate means:
meaneffstrats = (double)sumeff/INITNUMFAMS;
meanmobstrats = (double)summob/INITNUMFAMS;
meandrifts = (double)sumdrift/INITNUMFAMS;

if (abc == 1)
{
    if (farming == 1)
    {
        fprintf(detailsabc, "%.3f, %.3f, %.3f,",  meaneffstrats, meanmobstrats, meandrifts);
    }
    if (farming == 0)
    {
        fprintf(detailsabc, "%.3f, %.3f,", meanmobstrats, meandrifts);
    }
}


uniquefamID = INITNUMFAMS; // We've just allocated the first unique IDs : 0 to (INITNUMFAMS-1)

// ===== Just the dead/empty families (these are dead fams now, but later they could be 'outside' fams, not occupying a site.)
for (int i=INITNUMFAMS; i<MAXNUMFAMS; i++)
{
    families[i].fit = 0.00;
    families[i].e_strat = 1;    // Doesn't actually matter
    families[i].m_strat = 1;    // Doesn't actually matter
    families[i].drifttest = 1;    // Doesn't actually matter
    families[i].mcount = 0;     // Doesn't actually matter
    families[i].siteocc = NUMSITES; // This family is not on a site.
    families[i].oldsiteocc = NUMSITES;
}

nonfam[0].famID = MAXNUMFAMS; // An ID which won't come up when scrolling through the families.

// ........................................
// ===== Initialise site structures:

for (int i=0; i<NUMSITES; i++)
{
    if (sameinitialcond == 0)
    {
        sites[i].qual_f = (double)(rand() % (100-ROUND_2_INT(MINQF*100)+1))/100 + MINQF; // Foraging quality randomly assigned between [MINQF,1] (shouldn't be 0) changed 27/08/2016
        
        sites[i].qual_a = (double)(rand() % (100-ROUND_2_INT(MINQA*100)+1))/100 + MINQA; // Farming quality randomly assigned between [MINQA,1] (shouldn't be 0)
        
    }
    else
    {
        sites[i].qual_f = initialqf[i];
        sites[i].qual_a = initialqa[i];
    }
    
    if (farming == 0)
    {
        sites[i].qual_a = 0;
    }
    
    // To be changed for occupied sites:
    sites[i].occ = 0;                   // These are unoccupied.
    sites[i].countocc = 0;              // There are no agents occupying this site.
    sites[i].fam_occ[0] = &nonfam[0];   // Unoccupied sites are 'occupied' by the 'none' family.
}



// ===== Just the occupied site structures:
for (int i=0; i<INITNUMFAMS; i++)           // Go through the alive families
{
    int siteid = families[i].siteocc;       // Get the site they are occupying's ID
    sites[siteid].occ = 1;                  // These are occupied.
    sites[siteid].countocc = 1;                  // There is one agent occupying this site (to begin with).
    sites[siteid].fam_occ[0] = &families[i];   // Pointer to the family
}




// ===== Save the initial conditions:
// Print in the first repeat if you have chosen sameinitialcond == 1

//if ((sameinitialcond == 1 & rr == 0)) // Only saves once the repeats are all done.

if ((sameinitialcond == 1) & (rr % 1000 == 0))
{
    // Families: fitness, mobility, drift, site occupied
    for (int i=0; i<INITNUMFAMS; i++)
    {
        fprintf(initialfaminfo, "%.3f,", families[i].fit);
    }
    fprintf(initialfaminfo, "\n");
    for (int i=0; i<INITNUMFAMS; i++)
    {
        fprintf(initialfaminfo, "%.3f,", families[i].e_strat);
    }
    fprintf(initialfaminfo, "\n");
    for (int i=0; i<INITNUMFAMS; i++)
    {
        fprintf(initialfaminfo, "%.3f,", families[i].m_strat);
    }
    fprintf(initialfaminfo, "\n");
    for (int i=0; i<INITNUMFAMS; i++)
    {
        fprintf(initialfaminfo, "%.3f,", families[i].drifttest);
    }
    fprintf(initialfaminfo, "\n");
    for (int i=0; i<INITNUMFAMS; i++)
    {
        fprintf(initialfaminfo, "%d,", families[i].siteocc);
    }
    fprintf(initialfaminfo, "\n");
    
    
    // Sites: qf and qa
    
    for (int i=0; i<NUMSITES; i++)
    {
        fprintf(initialsiteinfo, "%.3f,",sites[i].qual_f);
    }
    for (int i=0; i<NUMSITES; i++)
    {
        fprintf(initialsiteinfo, "%.3f,",sites[i].qual_a);
    }
    fprintf(initialsiteinfo,"\n");
}





#endif
