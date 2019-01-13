//
//  randn.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//


#ifndef __Sedentism_v4_1__randn__
#define __Sedentism_v4_1__randn__

#include <cstdlib>      // std::rand, std::srand
#include <sys/time.h> // linux millisecond random numbers. For Legion

double
randn (double mu, double sigma);

#endif /* defined(__Sedentism_v4_3__randn__) */
