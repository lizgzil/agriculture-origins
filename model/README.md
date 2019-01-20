This code describes an agent-based model for the origins of sedentism and agriculture.

## Overview

The Forager Model simulates families moving around a region over many years. The model is iterative and each iteration is one year. The region is split up into sites of the same size, and each of these sites has a dynamic foraging quality. Foraging quality can be thought of as the potential for foraging or, equally, the quality of the natural resources. Foraging resources stay within each site, and in this way do not include migrating animals. Family units (or ‘agents’) occupy one site each iteration (although many families can co-occupy a single site), and forage at this site. The family’s foraging creates a feedback between the foraging quality of the site and the family’s fitness. Families can die, fission, mutate, and move from site to site, according to different probabilities.

The Forager-Farmer Model builds on the Forager Model by allowing agents to have a strategy which makes them more of less depending on farming.

This code describes both models - switching between them simply relies you to change certain parameters.

This code also allows for the ability to randomly chose parameter values for each simulation you run it for, in our analysis we frequently run the model thousands of times with each run of the model using a randomly chosen set of parameters - this is part of the fitting to idealised outcomes method (FIO) described in Section 2.4.1 of my thesis 'Evolutionary Models for the Origins of Agriculture'.

![A visualisation of two iterations of the model](./exampleofmodel.png)

## Set-up

To run this code, edit your model settings and parameters as described below, and run `main.cpp`.

## Methodology

Details of the model are given in Chapter 4 and Chapter 6.1 of my PhD thesis. Parameter settings for several experiments are given in the Appendix of my PhD thesis.

## Model settings and parameters

Most model settings and parameters are defined in variables.h.

Depending on the type of model you run some parameters may be not used, and if you use FIO (abc = 1) then some of the parameters will be changed randomly in variablesFIO.h, so what they are set to in variables.h will be overwritten.

If you want to use FIO then you may wish to edit variablesFIO.h to set which parameters you want to vary (lines 15 to 48) and what you want to save in the output files (lines 232 to 248).

You may also wish to edit savebeginningiteration_3.h and savefinaliteration_8.h depending on what kind of output files you want.

### Model settings in variables.h:

- extension:
The extension name of your output files.

- abc: 
If you want to use FIO (1) or not (0), different output files will be saved

- farming:
If you want to include farming (1) or not (0).
Default co-settings:

farming = 1, INITLOWERM = 0.99, MAXNUMFAMS = 3000, seedinit = 1
farming = 0, INITLOWERM = 0, MAXNUMFAMS = 600, seedinit = 0

- seedinit:
How initial strategies are set up.
0 : every agent gets initial strategies between [INITLOWERM,0.99].
1 : one agent gets an initial strategy of seedstrat for both mob and eff (the rest in [INITLOWERM,0.99])

- legion:
Whether you are using parallel computing (1) or not (0). This effects how you do your random number seed. This should be kept as 0.


#### Temporal variability:

See Chapter 5.4 of my PhD thesis for details about modelling this. Need to check in variablesFIO.h that settings are as you want.

- variability:
0 means parameters are the same throughout iterations.
1 means at iteration 100 the parameters change.
2 means that you are doing to null run for the variability (so need to make sure input file is correct).

- varrunintime:
If variability is on, how many iterations do you run the model for before varying r, lambda, beta and delta.
You may want this to be 0 (i.e. it is variable from the beginning).

- stopvarrunintime:
If variability is on, the iteration at which you stop changing r and lam (becomes stable again).
You may want this to be the same as NUMITS (i.e. it is never stable).

- WD:
Walk distance for when you have variability on, this can be varied in FIO too.

#### Spatial variability:

See Chapter 5.4 of my PhD thesis for details about modelling this. Need to check in variablesFIO.h that settings are as you want.

- sparvar:
0 means parameters are the same for every site.
1 means each site has a gradient of r and lambda values.
2 means you are doing the null run where all sites have one random r and lambda (like the original way).
3 means you are doing the null run where the sites have random r and lambda.
Things are done with this in variablesFIO (get GR1 and GR2 and output, and find the blended GR values for all sites), and in foragingcultivation (use the different GR value when this is on).
Even though this isnt actually abc, still set abc = 1 for saving.

#### Other settings:

- saveless:
How much to save. Only need to worry about if abc == 0 (if abc==1, it doesn't matter what is selected here).

0: Saves details, Rdetails, numfamilies, savefamilies, endmeans, sites, numfamilies, savefamiliesuniquesims, birthstuff, exfams, famsocc EXTRA BITS.
1: Saves details, Rdetails, numfamilies, savefamilies, endmeans, sites, numfamilies, savefamiliesuniquesims DEFAULT!.
2: Saves details, Rdetails, endinfo, meanmobs.
3: Saves details, Rdetails, [COMMENTED OUT families, sites] WITH abc == 1. also saves mean info every iteration in detailsabc.

- saveres:
Save family information every 'saveres' iterations. e.g. 1: saves every iteration, 50: saves every 50 iterations.

- sameinitialcond:
If you want the same initial conditions every repeat (1) or not (0) (qf, agent locations, fitness, mobility).

### Parameters in variables.h:

- repeats:
How many repeats of the model you want (useful for ABC stage).
Default = 100

- NUMITS:
Number of iterations (years) you want to run it for.
Default = 1000

- MAXNUMFAMS:
Maximum number of families nmax x PHI x NUMSITES - so if you are doing FIO pick the largest nmax and phi values you will be using. 10 x 10 x 100.
Farming: 10 x 10 x 5 x 6 = 3000.
Foraging: 10 x 10 x 6 = 600.

#### Spatial parameters:

- NUMSITES:
Number of sites. spatialx x spatialy = NUMSITES.
Default = 100

- spatialx:
The dimensions of the site if it is spatial.
Default = 10

- spatialy:
Make sure these give a product of NUMSITES.
Default = 10


#### Growth and death:

- GR:
Growth rate of the foraging quality.
Default = 0.53.

- LAMBDA:
Foraging depletion parameter.
Default = 0.64.

- PHI:
PHI times more farmers can be supported than foragers.
Default = 5.

- BETA: 
Farming interference scalar.
Default = 0.1.

- DELTA:
Farming depletion parameter.
Default = 0.1.

- nmax:
The maximum number of agents that can be supported at a site.
Default = 6.

- deathfit:
The fitness can get extrememly low, but still not actually = 0, so we will have death if fitness < DEATHFIT // Numerator - since the maximum site quality is 1.
Default = (double) 1/nmax

#### Fission parameters:

- fl:
Probability of fission - lower limit.
Default = 0.

- fu:
Probability of fission - upper limit.
Default = 0.14.

- kappam:
The number of components in the strategies, this just collapses to the range of the binomial.
Default = 100.

- kappae:
higher = tighter. For 100 the range is 0.4. For 10000 the range is about 0.04.
Default = 100.

- mut
Probability of mutation every iteration. 1/gentime = 1/25 = 0.04.
Default = 0.04.

#### Movement parameters:

- ETA:
Each time an agent moves n sites it's fitness is reduced by ETA x n.
Default = 0.01.

#### Limits/initial values:

- seedstrat
One agent in the initial population will have it's mobility and effort strategy as seedstrat.
Default = 0.8.

- INITLOWERM:
The mobility scores are randomly chosen between INITLOWERM and 1 in the initial population.
Default = 0.0.

- INITLOWERE:
The effort scores are randomly chosen between INITLOWERE and 1 in the initial population.
Default = INITLOWERM.

- MINQF
qf CAN'T BE 0 otherwise the foraging resource can never recover.
Default = 0.1.

- MINQA:
< DEATHFIT, otherwise agents will never die.
Default = MINQF.

- percentageinitocc:
The percentage of the number of sites which have agents initially.
Default = 0.1.

- INITNUMFAMS
This is actually calculated in main.

#### Parameters to do with spatial varibility:

If sparvar!=0.

- GR1:
Growth rate of the foraging quality on the left half of the region.
Default = 0.8.

- GR2:
Growth rate of the foraging quality on the right half of the region.
Default = 0.8.



