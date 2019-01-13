//
//  variablesFIO.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#ifndef Foraging_v5_1_variablesFIO_h
#define Foraging_v5_1_variablesFIO_h

#define ROUND_2_INT(f) ((int)(f >= 0.0 ? (f + 0.5) : (f - 0.5))) // A function to round a double to an int

if (abc == 1)
{
    // Choose the range of values for the parameters you want to vary.
    // Comment out/set to default values if you don't want to vary them.
    
    
    GR = (double)(rand() % 1001)/1000;    // 0 - 1
    
    LAMBDA = (double)(rand() % 1001)/1000;    // 0 - 1
    
    PHI = rand() % 5 + 1; // 1-5 integers // --------- 5
    
    BETA = (double)(rand() % 1001)/1000;    // 0 - 1

    DELTA = (double)(rand() % 101)/1000;    // 0 - 0.05, 0- 0.1
    
    kappam = rand() % 101 + 50; // 50-150 integers // --------- 100
    kappae = rand() % 101 + 50; // 50-150 integers // --------- 100
    
    fu = 0.14; //(double)(rand() % 501)/1000;   // 0 - 0.5 // --------- 0.14
    
    //ETA = (double)(rand() % 201)/1000; // 0 - 0.2 // --------- 0.05
    
    ETA = (double)(rand() % 101)/1000; // 0 - 0.1 // FOR THE FORAGER MODEL PAPER
    
    
    nmax = 6; //rand() % 5 + 2; // 2-6 integers // --------- 6
    deathfit = (double) 1/nmax;
    
    mut = 0.04;//(double)(rand() % 1001)/1000;    // 0 - 1 // --------- 0.04
    
    INITNUMFAMSbefore = INITNUMFAMS;
    
    //percentageinitocc = (double)(rand() % 1501 + 500)/10000; // 0.05 - 0.2 // --------- 0.1

    
    WDbefore = WD;
    if (variability == 1)
    {
        WD = (double)(rand() % 1001)/1000;  // 0 - 1
    }
    
    // -------------------------------------------------------------------------------------------------------------------
    // Temporal variability null run. Import the data file for mean r and lambda and use these values rather than find them
    // Make sure the file names are correctm and comment out any parameters you dont want to vary.
    
    if (variability == 2)
    {
        
        ifstream file_in_r("variabilitymeangr_7thdec_foraging_tempvariation_300runin_on.txt"); //
        ifstream file_in_l("variabilitymeanlamdba_7thdec_foraging_tempvariation_300runin_on.txt"); //
        //ifstream file_in_b("variabilitymeanbeta_22ndnov_farming_FIO4_variability2_on.txt"); //
        //ifstream file_in_d("variabilitymeandelta_22ndnov_farming_FIO4_variability2_on.txt"); //
        
        // Create the vector, initialized from the numbers in the file:
        vector<double> average_r((istream_iterator<double>(file_in_r)),istream_iterator<double>());
        vector<double> average_l((istream_iterator<double>(file_in_l)),istream_iterator<double>());
        //vector<double> average_b((istream_iterator<double>(file_in_b)),istream_iterator<double>());
        //vector<double> average_d((istream_iterator<double>(file_in_d)),istream_iterator<double>());
        
        GR = average_r.at(rr);
        LAMBDA = average_l.at(rr);
        //BETA = average_b.at(rr);
        //DELTA = average_d.at(rr);
    }

    
    
    // -------------------------------------------------------------------------------------------------------------------
    // Spatial variability. Chose 2 random values for the varied parameter (only one) for either side of the simulation
    
    if (sparvar == 1)
    {
        // ........................................
        // r and lambda are varied continuously in x and y axis from 0 to 1 (not random values needed)
        
        // The other non varied parameters are all the same for each site:
        // First of all set the blended value to be the default everywhere:
        for (int i= 0; i< NUMSITES ;i++)
        {
            GRblended[i] = GR;
            LAMBDAblended[i] = LAMBDA;
            BETAblended[i] = BETA;
            DELTAblended[i] = DELTA;
        }
        
        // r in x axis, lambda in right
        for (int i= 0; i< NUMSITES ;i++)
        {
            if (whichparamx == 1 && whichparamy == 2) // r and LAMBDA
            {
                GRblended[i] = (double)(i/spatialx)/(spatialx-1); // Floor of i/10 - since it's integer/integer but not converted to double.
                LAMBDAblended[i] = (double)(sites[i].coords[2])/(spatialy-1);
            }
            
            if (whichparamx == 1 && whichparamy == 4) // r and delta
            {
                GRblended[i] = (double)(i/spatialx)/(spatialx-1); // Floor of i/10 - since it's integer/integer but not converted to double.
                DELTAblended[i] = (double)(sites[i].coords[2])/(spatialy-1);
            }
            
            if (whichparamx == 2 && whichparamy == 4) // LAMBDA and delta
            {
                LAMBDAblended[i] = (double)(i/spatialx)/(spatialx-1); // Floor of i/10 - since it's integer/integer but not converted to double.
                DELTAblended[i] = (double)(sites[i].coords[2])/(spatialy-1);
            }
          
        }
        
        
       
        
        // ........................................
        // Two sides to the region with randomly picked parameter values
        
        /*
         // Since r, lambda, beta and delta are all between 0 and 1 I'll just use this code for each:
         
        GR1 = (double)(rand() % 1001)/1000;    // 0 - 1
        GR2 = (double)(rand() % 1001)/1000;    // 0 - 1
        
        // ........................................
        // Find the GR values for every site.
        
        
         // Blend of values:
         //for (int i=0; i<spatialx; i++)
         //{
         //for (int j=0; j<spatialy; j++)
         //{
         //GRblended[i*spatialy + j] = GR1 + ((double)(GR2-GR1)/(spatialx-1))*j;
         //}
         //}
         
        
        // The other non varied parameters are all the same for each site:
        // First of all set the blended value to be the default everywhere:
        for (int i= 0; i< NUMSITES ;i++)
        {
            GRblended[i] = GR;
            LAMBDAblended[i] = LAMBDA;
            BETAblended[i] = BETA;
            DELTAblended[i] = DELTA;
        }
        
        // Half with GR1 and half with GR2:
        // Change depending on which parameter you wanted to vary:
        for (int i= 0; i< ROUND_2_INT((double) NUMSITES/2) ;i++)
        {
            if (whichparam == 1)
            {
                GRblended[i] = GR1;
            } else if (whichparam == 2)
            {
                LAMBDAblended[i] = GR1;
            } else if (whichparam == 3)
            {
                BETAblended[i] = GR1;
            } else
            {
                DELTAblended[i] = GR1;
            }
            
        }
        for (int i = ROUND_2_INT((double) NUMSITES/2); i< NUMSITES ;i++)
        {
            if (whichparam == 1)
            {
                GRblended[i] = GR2;
            } else if (whichparam ==2)
            {
                LAMBDAblended[i] = GR2;
            } else if (whichparam == 3)
            {
                BETAblended[i] = GR2;
            } else
            {
                DELTAblended[i] = GR2;
            }
        }
        */
        
        // Save the mid value for use in the null run.
        spatvarmean = (double)(GR1 + GR2)/2;
        
        // Save the rannge between these:
        rangevar = abs(GR1 - GR2);
    }
    
    if (sparvar == 2)
    {
     // Just find randomly for whole region
        GR = (double)(rand() % 1001)/1000;    // 0 - 1
        LAMBDA = (double)(rand() % 1001)/1000;    // 0 - 1
        BETA = (double)(rand() % 1001)/1000;    // 0 - 1
        DELTA = (double)(rand() % 101)/1000;    // 0 - 0.05, 0- 0.1
        
    }
    if (sparvar == 3)
    {
        // Find randomly for every site
        for (int i= 0; i< NUMSITES ;i++)
        {
            GRblended[i] = (double)(rand() % 1001)/1000;    // 0 - 1
            LAMBDAblended[i] = (double)(rand() % 1001)/1000;    // 0 - 1
            BETAblended[i] = (double)(rand() % 1001)/1000;    // 0 - 1
            DELTAblended[i] =(double)(rand() % 101)/1000;    // 0 - 0.05, 0- 0.1
        }
    }
    

    
    // -------------------------------------------------------------------------------------------------------------------
    // Save the parameter values. Don't need to save them all if you only vary a few (comment out appropriately)
    
    
    if (legion == 0)
    {
        //fprintf(detailsabc,"%.3f, %.3f, %d, %.3f,%.3f, %d,%.3f,%.3f,", GR, LAMBDA,  kappam, fu, ETA, nmax, mut, percentageinitocc);
        
        //fprintf(detailsabc,"%.3f, %.3f, %.3f,%.3f,", GR, LAMBDA, fu, ETA);
        
        //fprintf(detailsabc,"%.3f, %.3f,", GR, LAMBDA);
        
        //fprintf(detailsabc,"%.3f, %.3f,%.3f,", GR, LAMBDA,WD);
        
        //fprintf(detailsabc,"%.3f, %.3f, %d, %.3f, %.3f, %d, %d, %.3f,%.3f, %d,%.3f,%.3f,", GR, LAMBDA, PHI, BETA, DELTA, kappam, kappae, fu, ETA, nmax, mut, percentageinitocc);
        
        //fprintf(detailsabc,"%.3f, %.3f, %.3f, %.3f, %.3f, %.3f,", GR, LAMBDA, BETA, DELTA, fu, ETA);
        
        //fprintf(detailsabc,"%.3f, %.3f, %.3f, %.3f,", GR, LAMBDA, BETA, DELTA);
        
        //fprintf(detailsabc,"%.3f, %.3f, %.3f, %.3f, %.3f,", GR, LAMBDA, BETA, DELTA, WD);
        
        fprintf(detailsabc,"%.3f, %.3f, %d, %.3f,", GR, LAMBDA, kappam, ETA);
        
    }
    else
    {
        //ofstream out("abc_17thfeb_legion.txt", ios::app);
        //out << GR <<"," << LAMBDA << "," << percentageinitocc << ","  ;
    }
}



// ........................................
// ===== Find a set of initial conditions if you want to use the same every repeat, found in the first repeat:
// if farming == 0 then the initial effort strategie are all 1

// New initial conditions after made every 1000 repeats, or can write (r==0) if you just want one set
if ((sameinitialcond == 1) & (rr % 1000 == 0)) // NEED TO CHANGE IN initialisationeachrepeat_2 TOO
{
    for (int i = 0; i < INITNUMFAMS; i++)
    {
        initialfitnesses[i] = (double)(rand() % (100-ROUND_2_INT(deathfit*100)+1))/100 + deathfit; // Fitness randomly assigned between [deathfit,1] (shouldn't make a dead group) changed 27/08/2016
        initialefforts[i] = (double)(rand() % (100-ROUND_2_INT(INITLOWERE*100)+1))/100 + INITLOWERE; // Effort randomly assigned between [INITLOWERE,1]
        initialmobilities[i] = (double)(rand() % (100-ROUND_2_INT(INITLOWERM*100)+1))/100 + INITLOWERM; // Mobility randomly assigned between [INITLOWERM,1] changed 27/08/2016
        initialdrifts[i] = (double)(rand() % (100-ROUND_2_INT(INITLOWERM*100)+1))/100 + INITLOWERM; // Drift randomly assigned between [INITLOWERM,1] changed 08/09/2016
        
        
        // If the strategies are 0 or 1 set to (0.01) and (0.99)
        
        if (initialefforts[i] < 0.01)
        {
            initialefforts[i] = 0.01;
        }
        if (initialefforts[i] > 0.99)
        {
            initialefforts[i] = 0.99;
        }
        
        if (farming == 0)
        {
            initialefforts[i] = 1; // If you dont want to use the farming model, make all their strategies full foragers
        }
        
        if (initialmobilities[i] < 0.01)
        {
            initialmobilities[i] = 0.01;
        }
        if (initialmobilities[i] > 0.99)
        {
            initialmobilities[i] = 0.99;
        }
        
        if (initialdrifts[i] < 0.01)
        {
            initialdrifts[i] = 0.01;
        }
        if (initialdrifts[i] > 0.99)
        {
            initialdrifts[i] = 0.99;
        }
        
        initialsites[i] = rand() % NUMSITES; // Go to a random site in between [0, NUMSITES -1], changed 27/08/2016
    }
    
    for (int i = 0; i < NUMSITES; i++)
    {
        initialqf[i] = (double)(rand() % (100-ROUND_2_INT(MINQF*100)+1))/100 + MINQF; // Foraging quality randomly assigned between [MINQF,1] (shouldn't be 0) changed 27/08/2016
        initialqa[i] = (double)(rand() % (100-ROUND_2_INT(MINQA*100)+1))/100 + MINQA; // Farming quality randomly assigned between [MINQA,1] (shouldn't be 0) changed 27/08/2016
        
        if (farming == 0)
        {
            initialqa[i] = 0;
        }
    }
    
}
#endif
