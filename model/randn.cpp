//
//  randn.cpp
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#include "randn.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cstdlib>      // std::rand, std::srand
#include <sys/time.h> // linux millisecond random numbers. For Legion

// pick values from a normal distribution with mean mu and standard deviation sigma

// Code from: http://phoxis.org/2013/05/04/generating-random-numbers-from-normal-distribution-in-c/

double
randn (double mu, double sigma)
{
    
    double U1, U2, W, mult;
    static double X1, X2;
    static int call = 0;
    
    if (call == 1)
    {
        call = !call;
        return (mu + sigma * (double) X2);
    }
    
    do
    {
        U1 = -1 + ((double) rand ()/RAND_MAX) * 2;
        U2 = -1 + ((double) rand ()/RAND_MAX) * 2;
        W = pow (U1, 2) + pow (U2, 2);
    }
    while (W >= 1 || W == 0);
    
    mult = sqrt ((-2 * log (W)) / W);
    X1 = U1 * mult;
    X2 = U2 * mult;
    
    call = !call;
    
    return (mu + sigma * (double) X1);
}




