//
//  main.cpp
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

// ===========================================================================================================
// ===== Included dependencies

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h> //abs
#include <iomanip> // set precision
#include <random>  // For Binomial distribution
#include <string.h> // To use strcat
#include <cstdlib>      // std::rand, std::srand
#include <algorithm>    // std::max
#include <time.h>       /* time */
#include <math.h>       // pow, floor, round
#include <sys/time.h> // linux millisecond random numbers. For Legion

#include "structures.h"                 // Defines the two structures: 'site' and 'family'
#include "permute.h"                    // A function to permute a list randomly: input is the size of the list, output is a list of numbers randomly ordered.
#include "randn.h"    // A function to find normally distributed values from
#include "pmcc.h"    // A function to calculate pearsons correlation coefficient between two vectors
#include "beta_distribution.h" 

// A function to find the coordinated of a site (3D coordinates)
#include "hexcoords.h"

// ===========================================================================================================
// ===== Functions

#define ROUND_2_INT(f) ((int)(f >= 0.0 ? (f + 0.5) : (f - 0.5))) // A function to round a double to an int

// Finding the number of digits in a number (for unique simulation family files)
unsigned GetNumberOfDigits (unsigned i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

// ===== Set the values for the run
#include "variables.h"

// ===== Allocate memory for things you will definitely use each repeat of the model.
#include "preallocation.h"


// ---------------------------------------------------------------------------------------------------------------------
//                                        ------------- MAIN: -------------
// ---------------------------------------------------------------------------------------------------------------------

using namespace std;

int main() {
    
    // ===== Make and open the files to save things in:
    #include "makeoutputfiles.h"
    
    // ===========================================================================================================
    // ===== Some warnings
    
    if (INITNUMFAMS > MAXNUMFAMS)
        cout << "WARNING - INITNUMFAMS > MAXNUMFAMS, this will probably cause errors." << endl;
    
    if (spatialx * spatialy != NUMSITES)
        cout << "WARNING - spatialx*spatialy != NUMSITES, this will cause errors." << endl;
    
    if ((sameinitialcond == 1) && (INITNUMFAMS != 10 | NUMSITES != 25) )
        cout << "WARNING - Make sure chosen initial values are the same length as initial number of families or number of sites.";

    if ( (sparvar == 1) && (abc == 0) )
        cout <<"WARNING - IF SPATIAL VARIATION IS ON ABC SHOULD BE ON TOO" << endl;
    
    if ( (sparvar == 1) && (variability == 1) )
        cout <<"WARNING - YOU CAN'T DO SPATIAL AND TEMPORAL VARIABILITY TOGETHER" << endl;
    
    if ( (sparvar == 1 | sparvar == 2| sparvar == 3) && (saveless == 3) )
        cout <<"WARNING - YOU WILL BE SAVING TO FAMILIES AND SITES MULTIPLE TIMES" << endl;

    // ===========================================================================================================
    // ===== Random number seeds
    
    if (legion == 0)
    {
        // Seed random numbers:
        srand((unsigned int) time(NULL));
    }
    else
    {
        // Seed random numbers for runs which happen more than once a second:
        struct timeval tv; // another linux way
        gettimeofday(&tv, NULL);
        srand(tv.tv_usec); // seed from the milliseconds
    }
    
    // For binomial picks
    std::default_random_engine generator;
    
    // ------------------------------------------------------------------------------------------------
    //                ------- 1. Initialisation of structures before repeats start: --------
    // ------------------------------------------------------------------------------------------------
    
#include "initialisationbeforerepeats_1.h"

    // ------------------------------------------------------------------------------------------------
    //                           ------------- REPEATS: -------------
    // ------------------------------------------------------------------------------------------------
    
    for (int rr=0; rr<repeats; rr++) // How many times you want to repeat this experiment
    {
        cout << rr << endl;
        
        summovedistance = 0;
        numbermoves = 0;
        countallbirths = 0;
        
        // ........................................
        // If using FIO, then this will randomly pick parameter values:
        // This file also finds values for initial conditions when rr == 0 and sameinitialcond == 1
        
#include "variablesFIO.h"
        
        double originalGR = GR;   // Save original because they can end up changing if variability == 1
        double originalLAMBDA = LAMBDA;
        double originalBETA = BETA;
        double originalDELTA = DELTA;
        
        if (abc == 1 & sameinitialcond == 1 & INITNUMFAMSbefore!=INITNUMFAMS)
        {
            cout << "WARNING - don't vary the initial percentage of agents in FIO if you want to use the same initial conditions each time!" << endl;
        }
        if ((WD != WDbefore) & (variability == 0))
        {
            cout << "WARNING - CHANGING THE RANDOM WALK WALK DISTANCE, WD, EVEN THOUGH YOU ARE NOT USING VARIBILITY" << endl;
        }
        if ((WD == WDbefore) & (variability == 1))
        {
            cout << "WARNING - NOT CHANGING THE RANDOM WALK WALK DISTANCE, WD, IN FIO EVEN THOUGH YOU ARE USING VARIBILITY" << endl;
        }
        
        if ((varrunintime > stopvarrunintime) & (variability == 1))
        {
            cout << "WARNING - varrunintime > stopvarrunintime" << endl;
        }
        if ((varrunintime == stopvarrunintime) & (variability == 1))
        {
            cout << "WARNING - varrunintime == stopvarrunintime" << endl;
        }
       
        // ........................................
        // Making unique family files to save information for each family in:
        
        FILE * savefamiliesuniquesims;
        if ((abc == 0)&&(saveless!=2))
        {
            // Open a file for each simulation's family details
            // How many digits are in 'repeats' (this is the maximum length)
            
            char fileSpec4b[strlen(save4)+GetNumberOfDigits(rr)+strlen(extension)+1];
            snprintf(fileSpec4b, sizeof(fileSpec4b), "%s%d%s", save4, rr, extension);
            savefamiliesuniquesims = fopen(fileSpec4b, "a+");
            
            fprintf(savefamiliesuniquesims, "Iteration, famID, e_strat, m_strat, drifttest, fitness, siteocc\n");
        }
        
                
        // -----------------------------------------------------------------------------------------------
        //                  ------- 2. Initialisation of structures each repeat: --------
        // -----------------------------------------------------------------------------------------------
        
        // Get the initial number of families, after finding parameter values:
        if (farming == 0)
        {
            INITNUMFAMS = ROUND_2_INT(percentageinitocc*NUMSITES*nmax);
        } else
        {
            INITNUMFAMS = ROUND_2_INT(percentageinitocc*NUMSITES*nmax);// I don't times by phi to find the initial num
        }
        
#include "initialisationeachrepeat_2.h"
        

        // -----------------------------------------------------------------------------------------------
        //                            ------------- ITERATIONS: -------------
        // -----------------------------------------------------------------------------------------------

        for (int w=0; w<NUMITS; w++)
        {
            // ........................................
            // Varying GR and LAMBDA (and BETA and DELTA) if there is variability selected
            
            if (variability == 1)
            {
                // STEP 2:
                // This was every iteration after varrunintime has a different GR and LAMBDA value, randomly picked.

                
                if (w == 0)
                {
                    // If it's the first iteration for this simulation then reset the parameter values, if you are not using FIO:
                    if (abc == 0)
                    {
                        GR = originalGR;
                        LAMBDA = originalLAMBDA;
                        BETA = originalBETA;
                        DELTA = originalDELTA;
                    }
                    
                    sumvargr = 0;
                    sumvarlambda = 0;
                    sumvarbeta = 0;
                    sumvardelta = 0;

                }
                
                if (w >= varrunintime & w < stopvarrunintime) // The iterations there is variability for
                {
                    previousGR = GR;
                    previousLAMBDA = LAMBDA;
                    previousBETA = BETA;
                    previousDELTA = DELTA;
                    
                    // Type 1. New values are picked randomly in the whole range:
                    //GR = (double)(rand() % 1001)/1000;    // 0 - 1
                    //LAMBDA = (double)(rand() % 1001)/1000;    // 0 - 1
                    
                    // Type 2. New values are picked from a random walk with size WD:
                    
                    GR = (double)(rand() % (ROUND_2_INT(((previousGR + WD) - (previousGR - WD))*1000) + 1) + (previousGR - WD)*1000)/1000; // [previousGR - WD, previousGR + WD]
                    LAMBDA = (double)(rand() % (ROUND_2_INT(((previousLAMBDA + WD) - (previousLAMBDA - WD))*1000) + 1) + (previousLAMBDA - WD)*1000)/1000; // [previousLAMBDA - WD, previousLAMBDA + WD]
                    
                    BETA = (double)(rand() % (ROUND_2_INT(((previousBETA + WD) - (previousBETA - WD))*1000) + 1) + (previousBETA - WD)*1000)/1000; // [previousBETA - WD, previousBETA + WD]
                    DELTA = (double)(rand() % (ROUND_2_INT(((previousDELTA + WD) - (previousDELTA - WD))*1000) + 1) + (previousDELTA - WD)*1000)/1000; // [previousDELTA - WD, previousDELTA + WD]
                    
                    
                    // Make sure they are within the limits:
                    if (GR < 0)
                    {
                        GR = 0;
                    }
                    if (GR > 1)
                    {
                        GR = 1;
                    }
                    if (LAMBDA < 0)
                    {
                        LAMBDA = 0;
                    }
                    if (LAMBDA > 1)
                    {
                        LAMBDA = 1;
                    }
                    if (BETA < 0)
                    {
                        BETA = 0;
                    }
                    if (BETA > 1)
                    {
                        BETA = 1;
                    }
                    if (DELTA < 0)
                    {
                        DELTA = 0;
                    }
                    if (DELTA > 0.1)
                    {
                        DELTA = 0.1;
                    }
                    
                    sumvargr = sumvargr + GR;
                    sumvarlambda = sumvarlambda + LAMBDA;
                    sumvarbeta = sumvarbeta + BETA;
                    sumvardelta = sumvardelta + DELTA;
                }
                
                
                // For every iteration save r and lambda when variability == 1.
                
                if (w != (NUMITS-1))
                {
                    fprintf(variabilitygr, "%.3f,", GR);
                    fprintf(variabilitylamdba, "%.3f,", LAMBDA);
                }
                else
                {
                    fprintf(variabilitygr, "%.3f\n", GR);
                    fprintf(variabilitylamdba, "%.3f\n", LAMBDA);
                }
                
                
                // Save the ratio every iteration when no FIO:
                if (abc == 0)
                {
                    if (w == (NUMITS-1))
                        fprintf(variabilitygrandlamdba, "%.3f\n", (double)GR/LAMBDA);
                    else
                        fprintf(variabilitygrandlamdba, "%.3f,", (double)GR/LAMBDA);
                }
                else
                { // Save the ratio in the last iteration when FIO:
                    if (w == (NUMITS-1))
                        fprintf(variabilitygrandlamdba, "%.3f\n", (double)GR/LAMBDA);
                }
                
                
            }
            
            
            // -----------------------------------------------------------------------------------------------
            //                  ------- 3. Save the info for this iteration: --------
            // -----------------------------------------------------------------------------------------------
            
#include "savebeginningiteration_3.h"
            
            // -----------------------------------------------------------------------------------------------
            //                  ------- 4. Families cultivate and/or forage: --------
            // -----------------------------------------------------------------------------------------------
            
#include "foragingcultivation_4.h"
            
            // -----------------------------------------------------------------------------------------------
            //            ------- 5. DEATH. Will any of the families at the sites die? --------
            // -----------------------------------------------------------------------------------------------
            
#include "death_5.h"
            
            // -----------------------------------------------------------------------------------------------
            //                ------- 6. BIRTH. Will there be any family birth? --------
            // -----------------------------------------------------------------------------------------------

#include "birth_6.h"
            
            // -----------------------------------------------------------------------------------------------
            //                ------- 6_5. MUTATION. --------
            // -----------------------------------------------------------------------------------------------
            
#include "mutation_6_5.h"
            
            // -----------------------------------------------------------------------------------------------
            //         ------- 7. MOVEMENT. Is it time for any sites to be abandoned? --------
            // -----------------------------------------------------------------------------------------------

#include "movement_7.h"
            
            // -----------------------------------------------------------------------------------------------
            //               -------  DEATH. Will any of the families at the sites die --------
            // -----------------------------------------------------------------------------------------------
            // This will just be for those agents who's fitness was lowered to much whilst moving.
            
            countalldead = 0; // from all the sites
            originalnumfams = numfams; // before death happened.
            
            for (int i=0; i<NUMSITES; i++)
            {
                originalcount = sites[i].countocc; // Store original count of number of agents at this site, before you change it every iteration.
                for (int j=0; j<originalcount; j++) // won't go through loop if there is no-one at this site
                {
                    
                    if ((sites[i].fam_occ[j] != &nonfam[0])&&((*sites[i].fam_occ[j]).fit<deathfit)) // The family that occupies this site is not the none family and it's fitness is less than a threshold of DEATHFIT (very low, but not = 0)
                    {
                        
                        if (abc == 0)
                        {
                            if (saveless==0)
                            {
                                fprintf(exfams, "%d,%d,%d\n", rr,w,(*sites[i].fam_occ[j]).famID);
                            }
                            
                        }
                        
                        countalldead = countalldead + 1;
                        
                        (*sites[i].fam_occ[j]).siteocc = NUMSITES; // The family now occupies the 'outside' site
                        (*sites[i].fam_occ[j]).oldsiteocc = NUMSITES;
                        (*sites[i].fam_occ[j]).mcount = 0;         // Counter set back to 0
                        (*sites[i].fam_occ[j]).fit = 0;            //
                        sites[i].countocc = sites[i].countocc - 1; // Counter of number of occupying agents is decreased.
                        sites[i].fam_occ[j] = &nonfam[0];          // The site is now 'occupied' by the 'none' family. //NEEDCHANGE
                        
                        numfams = numfams - 1; // The number of families decreases.
                    }
                }
                
                // So now you have a number of agents at this site, some of which have died. Go through the list and shift down if there is a gap.
                
                countdead = 0;
                for (int j=0; j<originalcount; j++) // won't go through loop if there is no-one at this site
                {
                    if (sites[i].fam_occ[j] == &nonfam[0]) // If this family just died
                    {
                        countdead = countdead + 1;
                    }
                    else
                    {
                        sites[i].fam_occ[j-countdead] = sites[i].fam_occ[j]; // Move agent ID down
                    }
                }
                // So now, the list of occupying families should all be alive, and go from sites[i].fam_occ[0 - countocc]
            }
            
            
            for (int i=0; i<NUMSITES; i++)
            {
                if (sites[i].countocc == 0)
                {
                    sites[i].occ = 0;  // If there is a 0 count of agents, then the site is now unoccupied
                }
            }
            
            
            // Families outside the sites with 0 fitness will already have these properties.
            
            
            // ...............................................................
            // 2.5. REORDERING. Make sure the first numfams agents are the living ones.
            
            // countalldead agents died. There used to be originalnumfams alive.
            
            
            countdead = 0;
            for (int j=0; j<originalnumfams; j++) // Go through all the families which are alive or just died.
            {
                if (families[j].fit < deathfit) // If this family just died
                {
                    countdead = countdead + 1;
                }
                else
                {
                    // If this family is still alive move it down countdead rows
                    // It's family ID remains the same! (needed so we don't need to update who's at the site)
                    
                    // The site this family occupies, must have it's fam_occ list replaced from the old family pointer to the reshuffled one.
                    
                    for (int fo=0; fo<sites[families[j].siteocc].countocc; fo++) // Go through the list of families which occupy the site this family is at
                    {
                        if (sites[families[j].siteocc].fam_occ[fo] == &families[j]) // When you get to the old pointer, update it.
                        {
                            sites[families[j].siteocc].fam_occ[fo] = &families[j-countdead];
                            break;
                        }
                    }
                    
                    families[j-countdead].famID = families[j].famID;
                    families[j-countdead].fit = families[j].fit;
                    families[j-countdead].e_strat = families[j].e_strat;
                    families[j-countdead].m_strat = families[j].m_strat;
                    families[j-countdead].drifttest = families[j].drifttest;
                    families[j-countdead].mcount = families[j].mcount;
                    families[j-countdead].siteocc = families[j].siteocc;
                    families[j-countdead].oldsiteocc = families[j].oldsiteocc;
                }
            }
            

            
            // .................................................................
            // Find the average effort and mobilities of all the living agents for this iteration.
            
            sumeff = 0;
            summob = 0;
            sumdrift = 0;
            countalive = 0;
            for (int ii=0; ii<numfams; ii++) // Go through all the families
            {
                if (families[ii].fit >= deathfit) // If they are alive
                {
                    sumeff = sumeff + families[ii].e_strat;
                    summob = summob + families[ii].m_strat;
                    sumdrift = sumdrift + families[ii].drifttest;
                    countalive ++;
                }
            }
            
            if (countalive != 0)
            {
                meaneffstrats = (double)sumeff/countalive;
                meanmobstrats = (double)summob/countalive;
                meandrifts = (double)sumdrift/countalive;
                
            }
            else
            {
                // If there aren't any agents alive then set their value to 2 so we don't confuse the mean with 0
                meaneffstrats = 2;
                meanmobstrats = 2;
                meandrifts = 2;
            }
            
            
            // -----------------------------------------------------------------------------------------------
            //             ------- 8.  SAVING things at the end of the iterations: --------
            // -----------------------------------------------------------------------------------------------
            // If number of agents is 0, save things and exit loop for next run of the model.
            
#include "savefinaliteration_8.h"
            
        } // end of iterations w.

        fclose(savefamiliesuniquesims);

    } // end of the repeated simulations, rr.
    
    
    /*
    if (abc == 1)
    {
        // Just to give them a final line:
        fprintf(endfamilymobs, "%.3f\n",2.0);
        fprintf(endfamilynulls, "%.3f\n",2.0);
    }
    */
    
    // ===============================
    
    fclose(detailsabc);
    fclose(exfams);
    fclose(birthstuff);
    fclose(savefamilies);
    fclose(savesites);
    fclose(famsocc);
    fclose(numfamilies);
    fclose(endmeans);
    fclose(endfamilymobs);
    fclose(endinfo);
    fclose(meanmobs);
    fclose(endfamilynulls);
    fclose(variabilitygrandlamdba);
    fclose(initialfaminfo);
    fclose(initialsiteinfo);
    fclose(variabilitymeanlamdba);
    fclose(variabilitymeangr);
    fclose(variabilitymeanbeta);
    fclose(variabilitymeandelta);
    fclose(variabilityrangegr);
    fclose(variabilitylamdba);
    fclose(variabilitygr);
    
    return 0;
}



