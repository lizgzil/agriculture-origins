//
//  pmcc.cpp
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//
// To find the pearson's product moment correlation coefficient from a list of summaries of all the living agents at each iteration.

// INPUT - 'summaryliste' and 'summarylistm' could be the list of average effort strategies and mobility strategies for all the iterations. They are always the same summary, but for the effort and then mobility strategies.
// 'sizevec' will always be the number of iterations, NUMITS

// OUTPUT - correlation coefficient ('cor') from this data and the number of iterations alive ('itsalive').

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Example of using 'pmcc' in main.cpp:
/*
 double cor = pmcc(itsalive, summaryliste, summarylistm);
 */
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "pmcc.h"
#include <iostream>
#include <time.h>       /* time */
#include <cstdlib>      // std::rand, std::srand
#include <sys/time.h> // linux millisecond random numbers. For Legion
#include <math.h>       // pow, floor, round

double pmcc(int famsalive, double summaryliste[], double summarylistm[])
{
    double meane;
    double meanm;
    double sume = 0;
    double summ = 0;

    double SPD = 0; // Sum of products of the differences - numerator in pmcc calculation
    double SDe = 0; // Sum of squares for effort
    double SDm = 0; // Sum of squares for mobility
    
    double cor; // Correlation coefficient = SPD/(pow(SDe,0.5)*pow(SDm,0.5))
    
    // Go through the lists and calculate the sum
    // All these should have a value !=2 since they are from before all the agents died (if they ever did)
    for (int s = 0; s < famsalive; s++)
    {
        sume = sume + summaryliste[s];
        summ = summ + summarylistm[s];
    }
    
    // If there are agents alive (there always should be to get to the stage):
    if (famsalive!=0)
    {
        // Calculate the means:
        meane = (double) sume/famsalive;
        meanm = (double) summ/famsalive;
        
        // Calculate the pmcc:
        
        for (int i = 0; i < famsalive; i++)
        {
            SPD = SPD + (summaryliste[i] - meane)*(summarylistm[i] - meanm);
            SDe = SDe + pow(summaryliste[i] - meane,2);
            SDm = SDm + pow(summarylistm[i] - meanm,2);
        }
        
        // Correlation coefficient
        cor = (double) SPD/(pow(SDe,0.5)*pow(SDm,0.5));
    }
    else
    {
        // If there are no agents left to calculate pmcc! (Not even sure if this can happen)
        // Set 'cor' to (will never happen naturally). Can tell anyway since pmccinfo[1] will be 0 when pmccinfo[0]=2.
        cor = 2;
    }
    
    return cor;
}