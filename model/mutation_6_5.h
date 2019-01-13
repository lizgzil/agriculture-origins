//
//  mutation_6_5.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#ifndef Foraging_v5_1_mutation_6_5_h
#define Foraging_v5_1_mutation_6_5_h

// Go through all the alive families (doesn't need to be in a random order)

for (int f=0; f<numfams; f++)
{
    if (families[f].fit >= deathfit) // If they are alive.
    {
        // There will be a mutation with a probability of 1/25
        
        randmut = (double)(rand() % 1001)/1000;  // A random number between [0, 1].
        
        if (randmut <= mut) // (double)1/25 There will be a mutation in the strategies of this family
        {
            // Effort strategy
            // === Get a number from a Binomial distribution:
            std::binomial_distribution<int> distribution1(ROUND_2_INT(kappae*families[f].fit),families[f].e_strat);
            families[f].e_strat = (double) distribution1(generator)/ROUND_2_INT(kappae*families[f].fit); // Value is between 0 and 1
            
            // Mobility strategy
            // === Get a number from a Binomial distribution:
            std::binomial_distribution<int> distribution2(ROUND_2_INT(kappam*families[f].fit),families[f].m_strat);
            families[f].m_strat = (double) distribution2(generator)/ROUND_2_INT(kappam*families[f].fit); // Value is between 0 and 1
            
            // Drift strategy
            // === Get a number from a Binomial distribution:
            std::binomial_distribution<int> distribution3(ROUND_2_INT(kappam*families[f].fit),families[f].drifttest);
            families[f].drifttest = (double) distribution3(generator)/ROUND_2_INT(kappam*families[f].fit); // Value is between 0 and 1
            
            // If the strategies are 0 or 1 set to 0.01 and 0.99
            if (families[f].m_strat < 0.01)
            {
                families[f].m_strat = 0.01;
            }
            if (families[f].m_strat > 0.99)
            {
                families[f].m_strat = 0.99;
            }
            
            if (families[f].e_strat < 0.01)
            {
                families[f].e_strat = 0.01;
            }
            if (families[f].e_strat > 0.99)
            {
                families[f].e_strat = 0.99;
            }
            
            if (families[f].drifttest < 0.01)
            {
                families[f].drifttest = 0.01;
            }
            if (families[f].drifttest > 0.99)
            {
                families[f].drifttest = 0.99;
            }
        }
    }
}



#endif
