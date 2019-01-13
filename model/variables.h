//
//  parameters.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#ifndef Foraging_v5_1_parameters_h
#define Foraging_v5_1_parameters_h

#define ROUND_2_INT(f) ((int)(f >= 0.0 ? (f + 0.5) : (f - 0.5))) // A function to round a double to an int


// ====================================================================================
// ===================== Settings =====================================================

// -------------------------------------------------------------------------------------------------------------------

char const *extension = "_foragingmodel17May2018_highmoballinfoxx.txt"; // The extension you want to save your files with


// Common runs: abc and saving only at the end - have saveless = 1
//              abc and saving every iteration - have saveless = 3

// -------------------------------------------------------------------------------------------------------------------
// TYPE OF RUN:

int abc = 0; // If you are using abc (1) or not (0). Saves different output files.
// abc == 1:      Saves details, Rdetails, detailsabc, endfamilymobs, endfamilynulls, numfamilies

int farming = 0; // If you want to include farming or not. If farming == 0 then this will be the same as Foraging_v5.1
                 // farming: #define INITLOWERM  0.99, MAXNUMFAMS 3000 and seedinit = 1
                 // foraging: #define INITLOWERM  0, MAXNUMFAMS 600 and seedinit = 0

int seedinit = 0; // 0 : everyone gets initial strategies between [INITLOWERM,0.99].
                  // 1 : one agent gets an initial strategy of seedstrat for both mob and eff (the rest in [INITLOWERM,0.99])

int legion = 0; // Whether you are (1) or not (0) using legion. This effects how you do your random number seed.


// -------------------------------------------------------------------------------------------------------------------
// TEMPORAL VARIABILITY: (NEED TO CHECK THINGS IN VARIABLESFIO.H ARE AS YOU WANT)

int variability = 0; // 0 means parameters are the same throughout.
                     // 1 means at iteration 100 the parameters change.
                     // 2 means that you are doing to null run for the variability (so need to make sure input file is correct
                // abc == 0 and variability == 1: also saves variabilitygrandlamdba
                // abc == 1 still has variability occuring, it just doesnt save variabilitygrandlamdba

int varrunintime = 0; // If variability is on, how many iterations do you run the model for before varying r, lambda, beta and delta
// You may want this to be 0 (i.e. it is variable from the beginning)

int stopvarrunintime = 1000; // If variability is on, the iteration at which you stop changing r and lam (becomes stable again).
// You may want this to be the same as NUMITS (i.e. it is never stable)

// If you are using variability type 4 this means that you run the model with variability on, and the mean r, lambda, beta and delta values are saved for every simulation.
// Then you compare these runs to a null run, and for these the values chosen for r, lambda, beta and delta are the mean values.
// Comment out where appropriated in the variablesFIO file (when you arent studying variability you wont want to read in the data).
// So you need to make sure the number of simulations was the same and you have this file first before running the 'off' run

double WD = 0.1; // Walk distance for when you have variability on, this can be varied in FIO too
double WDbefore = WD;
// -------------------------------------------------------------------------------------------------------------------
// SPATIAL VARIABILITY: (NEED TO CHECK THINGS IN VARIABLESFIO.H ARE AS YOU WANT)

int sparvar = 0; // 0 means parameters are the same for every site,
                 // 1 means each site has a gradient of r and lambda values
                 // 2 means you are doing the null run where all sites have one random r and lambda (like the original way)
                 // 3 means you are doing the null run where the sites have random r and lambda
                 // Things are done with this in variablesFIO (get GR1 and GR2 and output, and find the blended GR values for all sites),
                 // and in foragingcultivation (use the different GR value when this is on)
                 // Even though this isnt actually abc, still set abc = 1 for saving complications.

// Note: if you are doing the null run, then you need to keep whichparam as it was in the var run

// Which parameter do you want to vary in the x and y axis? // 1:4. 1 = r, 2 = lambda, 3 = beta, 4 = delta.
int whichparamx = 2;
int whichparamy = 4;

// I HAVE ONLY CODED 1,2; 1,4; AND 3,4 (since beta is boring) go into variablesFIO if you want to add new pairs.

// -------------------------------------------------------------------------------------------------------------------
// OTHER SETTINGS:

int saveless = 1; // How much to save. Only need to worry about if abc == 0 (if abc==1, it doesn't matter what is selected here)
// saveless == 0: Saves details, Rdetails, numfamilies, savefamilies, endmeans, sites, numfamilies, savefamiliesuniquesims, birthstuff, exfams, famsocc EXTRA BITS
// saveless == 1: Saves details, Rdetails, numfamilies, savefamilies, endmeans, sites, numfamilies, savefamiliesuniquesims DEFAULT!
// saveless == 2: Saves details, Rdetails, endinfo, meanmobs
// saveless == 3: Saves details, Rdetails, [COMMENTED OUT families, sites] WITH abc == 1. also saves mean info every iteration in detailsabc


int saveres = 1; // Save family information every 'saveres' iterations. e.g. 1: saves every iteration, 50: saves every 50 iterations.

int sameinitialcond = 0; // If you want the same initial conditions every repeat (1) or not (0) (qf, agent locations, fitness, mobility)



// ====================================================================================
// ===================== Variables ====================================================


int repeats = 100; // How many repeats of the model you want (useful for ABC stage).
int NUMITS = 1000;    // Number of iterations (years) you want to run it for.
#define MAXNUMFAMS 600 // Maximum number of families nmax*PHI*NUMSITES - so if you are doing FIO pick the largest nmax and phi values you will be using. 10*10*100.
                // Farming: 10*10*5*6 = 3000
                // Foraging: 10*10*6 = 600


// ==== Space parameters: ====

#define NUMSITES      100   // Number of sites. spatialx*spatialy = NUMSITES
int spatialx = 10;          // The dimensions of the site if it is spatial.
int spatialy = 10;          // Make sure these give a product of NUMSITES


// ==== Growth and death: ====

double GR = 0.53;     // Growth rate of the foraging quality.
double LAMBDA = 0.64; // Foraging depletion parameter
int PHI = 5;         // PHI times more farmers can be supported than foragers. Previously T
double BETA = 0.1;   // Farming interference scalar.
double DELTA = 0.1;  // Farming depletion parameter


int nmax = 6;       // The maximum number of agents that can be supported at a site
double deathfit = (double) 1/nmax; // The fitness can get extrememly low, but still not actually = 0, so we will have death if fitness < DEATHFIT // Numerator - since the maximum site quality is 1

// ======= Fission parameters: =====================

double fl = 0;       // Probability of fission - lower limit
double fu = 0.14;    // Probability of fission - upper limit

int kappam = 100;    // The number of components in the strategies, this just collapses to the range of the binomial
int kappae = 100;    // higher = tighter. For 100 the range is 0.4. For 10000 the range is about 0.04.

double mut = 0.04;   // Probability of mutation every iteration. 1/gentime = 1/25 = 0.04

// ====== Movement parameters: =========================

double ETA = 0.01;  // Each time an agent moves n sites it's fitness is reduced by ETA*n. Before = 0.

// ==== Limits/initial values: ====

double seedstrat = 0.8;     // One agent in the initial population will have it's mobility and effort strategy as seedstrat
#define INITLOWERM  0.0//0.99//0.8//0.8//0.0//0.99    // The mobility scores are randomly chosen between INITLOWERM and 1 in the initial population. 0
double INITLOWERE = INITLOWERM;  // The effort scores are randomly chosen between INITLOWERE and 1 in the initial population.
#define MINQF   0.1         //!! qf CAN'T BE 0 otherwise the foraging resource can never recover.
double MINQA = MINQF;       // < DEATHFIT, otherwise agents will never die.

double percentageinitocc = 0.1; // The percentage of the number of sites which have agents.
int INITNUMFAMS; // This is actually calculated in main.

// ===== Misc: ====================

int numfams;        // This will be updating throughout, the number of families at sites.
double siteattract[NUMSITES];   // This is unique for each agent that wants to move.
int sitedist; // The distance from each site to another.

// ===== Spatial varibility: ====================

double GR1 = 0.8;    // Growth rate of the foraging quality on the left half of the region
double GR2 = 0.8;    // Growth rate of the foraging quality on the right half of the region

#endif
