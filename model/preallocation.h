//
//  preallocation.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#ifndef Foraging_v5_1_preallocation_h
#define Foraging_v5_1_preallocation_h


// In foraging/farming:

double Yf;
double Ya;
double sume;
double sumyfs;
double sumyas;

// Misc:

double pi = 3.1415926535897;

double initialfitnesses[MAXNUMFAMS];
double initialefforts[MAXNUMFAMS];
double initialmobilities[MAXNUMFAMS];
double initialdrifts[MAXNUMFAMS];
int initialsites[MAXNUMFAMS];
double initialqf[NUMSITES];
double initialqa[NUMSITES];
int INITNUMFAMSbefore;

double previousGR;
double previousLAMBDA;
double previousBETA;
double previousDELTA;
//double WDbefore;

double sumvargr = 0;
double sumvarlambda = 0;
double sumvarbeta = 0;
double sumvardelta = 0;

double meanvargr;
double meanvarlambda;
double meanvarbeta;
double meanvardelta;

double GRblended[NUMSITES]; // when there is spatial variation
double LAMBDAblended[NUMSITES]; // when there is spatial variation
double BETAblended[NUMSITES]; // when there is spatial variation
double DELTAblended[NUMSITES]; // when there is spatial variation
double spatvarmean; // The mean of the two GRs in spatial variation
double rangevar; // The absolute difference between the two GRs in spatial variation


// Fissioning:

int uniquefamID = 0; // A unique family ID for every new agent.
int countallbirths;
double randbirth;
double probbirth;
int permutedfambir[MAXNUMFAMS];
int *permutedfambir2;

// In mutation:
double randmut;

// Movement:

int oldsite;
double potfit;
double sumattract;
double randnum;
int summovedistance;
int numbermoves;
int permutedfam1[MAXNUMFAMS];
int *permutedfam2;
double randmov;
double randmov2;
int randsite;
family *prevfampoint;
family *tempprevfampoint;

// In deaths:

int alldeaths;
int originalcount;
int countdead;
int countalldead;

// In end point saving:

int countalive;
int itsalive;
double sumeff;
double summob;
double sumdrift;
double sumfit;
double sumeff2;
double summob2;
double sumdrift2;
double sumfit2;
double meaneffstrats;
double meanmobstrats;
double meandrifts;
double meanfits;
double meaneffstrats2;
double meanmobstrats2;
double meandrifts2;
double meanfits2;
double sdeffstrats;
double sdmobstrats;
double sddrifts;
double sdfits;
double sumqualf;
double sumqualf2;
double meanqualf;
double meanqualf2;
double sdqualf;
double sumquala;
double sumquala2;
double meanquala;
double meanquala2;
double sdquala;



#endif
