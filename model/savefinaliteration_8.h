//
//  savefinaliteration_8.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#ifndef Foraging_v5_1_savefinaliteration_8_h
#define Foraging_v5_1_savefinaliteration_8_h

// Save mean r, lambda, beta and delta if you have used variability (not inc the run-in period)
if ((variability == 1)&&(w == NUMITS-1))
{
    meanvargr = (double) sumvargr/(NUMITS - varrunintime);
    meanvarlambda = (double) sumvarlambda/(NUMITS - varrunintime);
    meanvarbeta = (double) sumvarbeta/(NUMITS - varrunintime);
    meanvardelta = (double) sumvardelta/(NUMITS - varrunintime);
    
    fprintf(variabilitymeangr, "%f\n", meanvargr);
    fprintf(variabilitymeanlamdba, "%f\n", meanvarlambda);
    fprintf(variabilitymeanbeta, "%f\n", meanvarbeta);
    fprintf(variabilitymeandelta, "%f\n", meanvardelta);
}

if ((sparvar == 1 | sparvar == 2 |sparvar == 3) &&(w == NUMITS-1))
{
    // Just using the 'gr' file to save the mean value in, but it doesn't actually mean that r was the parameter varied,
    // This can also be the mean lambda, beta or delta if they were the ones varied.
    //fprintf(variabilitymeangr, "%f\n", spatvarmean);
    //fprintf(variabilityrangegr, "%f\n", rangevar);
    
    
    // New type of saving, where I save everything at the end.
    
    
    for (int i=0; i<NUMSITES; i++)
    {
        fprintf(savesites, "%.1d, %.1d,%.1d,%.4f,%.4f\n", rr, sites[i].siteID,sites[i].countocc,sites[i].qual_f,sites[i].qual_a);
    }
    for (int i=0; i<numfams; i++)
    {
        fprintf(savefamilies, "%.1d, %.1d, %.4f, %.4f, %.4f, %.4f, %.1d\n", rr, families[i].famID, families[i].e_strat, families[i].m_strat, families[i].drifttest, families[i].fit, families[i].siteocc);
    }
}


if (abc == 0 & saveless ==2)
{
    fprintf(meanmobs, "%d, %d, %f, %f\n", rr, w, meanmobstrats,meaneffstrats);
}

// Find final means and SD for all types of runs.




// Usually just calculated for the final iteration, but to check the mean strat converge over time I'll save for a few
if ((w == NUMITS-1) || (numfams == 0))
{
//if ((w % 100 == 0) || (w == NUMITS-1) || (numfams == 0))
//{
    if (countalive != 0) // Will have already calculated the number alive
    {
        sumeff = 0;
        summob = 0;
        sumdrift = 0;
        sumfit = 0;
        sumeff2 = 0;
        summob2 = 0;
        sumdrift2 = 0;
        sumfit2 = 0;
        
        for (int ii=0; ii<numfams; ii++) // Go through all the families
        {
            if (families[ii].fit >= deathfit) // If they are alive
            {
                sumeff = sumeff + families[ii].e_strat;
                summob = summob + families[ii].m_strat;
                sumdrift = sumdrift + families[ii].drifttest;
                sumfit = sumfit + families[ii].fit;
                
                // Sum of the squares
                sumeff2 = sumeff2 + pow(families[ii].e_strat,2);
                summob2 = summob2 + pow(families[ii].m_strat,2);
                sumdrift2 = sumdrift2 + pow(families[ii].drifttest,2);
                sumfit2 = sumfit2 + pow(families[ii].fit,2);
            }
        }
        // Calculate means:
        meaneffstrats = (double)sumeff/countalive;
        meanmobstrats = (double)summob/countalive;
        meandrifts = (double)sumdrift/countalive;
        meanfits = (double)sumfit/countalive;
        
        meaneffstrats2 = (double)sumeff2/countalive;
        meanmobstrats2 = (double)summob2/countalive;
        meandrifts2 = (double)sumdrift2/countalive;
        meanfits2 = (double)sumfit2/countalive;
        
        // Calculate standard deviations:
        sdeffstrats = pow(meaneffstrats2 - pow(meaneffstrats,2),0.5);
        sdmobstrats = pow(meanmobstrats2 - pow(meanmobstrats,2),0.5);
        sddrifts = pow(meandrifts2 - pow(meandrifts,2),0.5);
        sdfits = pow(meanfits2 - pow(meanfits,2),0.5);
        
    }
    else
    {
        // If there are no agents left, set these values to 2 to distingush this fact - will be obvious anyway since numfams = 0;
        meaneffstrats = 2.0;
        meanmobstrats = 2.0;
        meandrifts = 2.0;
        meanfits = 2.0;
        
        sdeffstrats = 2.0;
        sdmobstrats = 2.0;
        sddrifts = 2.0;
        sdfits = 2.0;
    }
    
    // Mean and SD of the foraging quality
    
    sumqualf = 0;
    sumqualf2 = 0;
    sumquala = 0;
    sumquala2 = 0;
    for (int ii=0; ii<NUMSITES; ii++) // Go through all the sites
    {
        sumqualf = sumqualf + sites[ii].qual_f;
        sumqualf2 = sumqualf2 + pow(sites[ii].qual_f,2);
        sumquala = sumquala + sites[ii].qual_a;
        sumquala2 = sumquala2 + pow(sites[ii].qual_a,2);
    }
    
    meanqualf = (double)sumqualf/NUMSITES;
    meanqualf2 = (double)sumqualf2/NUMSITES;
    
    meanquala = (double)sumquala/NUMSITES;
    meanquala2 = (double)sumquala2/NUMSITES;
    
    sdqualf = pow(meanqualf2 - pow(meanqualf,2),0.5);
    sdquala = pow(meanquala2 - pow(meanquala,2),0.5);
    
   
    if (abc == 1 && saveless==3)
    {
        // Just for checking that the number of iterations smooths out the result I want to save the means at various iterations
        //fprintf(detailsabc, "%d, %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f,", w, countalive, meaneffstrats, meanmobstrats, meanfits, meandrifts, meanqualf, meanquala);
    }
    
}


if (saveless == 3)
{
    // Save the mean values every iteration
    
    if (countalive != 0) // Will have already calculated the number alive
    {
        sumeff = 0;
        summob = 0;
        sumdrift = 0;
        sumfit = 0;
        sumeff2 = 0;
        summob2 = 0;
        sumdrift2 = 0;
        sumfit2 = 0;
        
        for (int ii=0; ii<numfams; ii++) // Go through all the families
        {
            if (families[ii].fit >= deathfit) // If they are alive
            {
                sumeff = sumeff + families[ii].e_strat;
                summob = summob + families[ii].m_strat;
                sumdrift = sumdrift + families[ii].drifttest;
                sumfit = sumfit + families[ii].fit;
                
                // Sum of the squares
                sumeff2 = sumeff2 + pow(families[ii].e_strat,2);
                summob2 = summob2 + pow(families[ii].m_strat,2);
                sumdrift2 = sumdrift2 + pow(families[ii].drifttest,2);
                sumfit2 = sumfit2 + pow(families[ii].fit,2);
            }
        }
        // Calculate means:
        meaneffstrats = (double)sumeff/countalive;
        meanmobstrats = (double)summob/countalive;
        meandrifts = (double)sumdrift/countalive;
        meanfits = (double)sumfit/countalive;
        
        meaneffstrats2 = (double)sumeff2/countalive;
        meanmobstrats2 = (double)summob2/countalive;
        meandrifts2 = (double)sumdrift2/countalive;
        meanfits2 = (double)sumfit2/countalive;
    }
    else
    {
        // If there are no agents left, set these values to 2 to distingush this fact - will be obvious anyway since numfams = 0;
        meaneffstrats = 2.0;
        meanmobstrats = 2.0;
        meandrifts = 2.0;
        meanfits = 2.0;
    }
    
    // Mean and SD of the foraging quality
    
    sumqualf = 0;
    sumqualf2 = 0;
    sumquala = 0;
    sumquala2 = 0;
    for (int ii=0; ii<NUMSITES; ii++) // Go through all the sites
    {
        sumqualf = sumqualf + sites[ii].qual_f;
        sumqualf2 = sumqualf2 + pow(sites[ii].qual_f,2);
        sumquala = sumquala + sites[ii].qual_a;
        sumquala2 = sumquala2 + pow(sites[ii].qual_a,2);
    }
    
    meanqualf = (double)sumqualf/NUMSITES;
    meanqualf2 = (double)sumqualf2/NUMSITES;
    
    meanquala = (double)sumquala/NUMSITES;
    meanquala2 = (double)sumquala2/NUMSITES;
    
    sdqualf = pow(meanqualf2 - pow(meanqualf,2),0.5);
    sdquala = pow(meanquala2 - pow(meanquala,2),0.5);
    
    
    if (abc == 1)
    {
        // Just for checking that the number of iterations smooths out the result I want to save the means at various iterations
        fprintf(detailsabc, "%d, %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f,", w, countalive, meaneffstrats, meanmobstrats, meanfits, meandrifts, meanqualf, meanquala);
    }
}


// Save all the strategies of the agents in the final iteration. Just write in a big list. Will also save how many final agents there were (in detailsabc) so you can chop it up in R

/*
if (((abc == 1)&&(w == NUMITS-1)) || ((abc == 1)&&(numfams==0)))
{
    for (int ii=0; ii<numfams; ii++) // Go through all the families
    {
        if (families[ii].fit >= deathfit) // If they are alive
        {
            fprintf(endfamilymobs, "%.3f,", families[ii].m_strat);
            fprintf(endfamilynulls, "%.3f,", families[ii].drifttest);
        }
    }
}
*/



// Save means at the last iteration if you aren't doing ABC and saveless == 2

if (((abc==0)&&(w == NUMITS-1)) || ((abc==0)&&(numfams == 0)))
{
    if (saveless ==2)
    {
        fprintf(endinfo, "%d, %d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n", rr, w, numfams, meaneffstrats, sdeffstrats, meanmobstrats, sdmobstrats, meandrifts, sddrifts, meanfits, sdfits, meanqualf, sdqualf, meanquala, sdquala);
        break; // Goes to next run.
    }
}

// Save means at the last iteration if you aren't doing ABC (much quicker doing this here rather than in R

if ((abc==0)&&(w == NUMITS-1)&&(saveless !=2))
{
    fprintf(endmeans, "%d, %d, %f, %f, %f \n", rr, w, meaneffstrats, meanmobstrats, meandrifts);
}


// Save things for abc at the end

if (((abc == 1)&&(w == NUMITS-1)) || ((abc == 1)&&(numfams==0)))
{
 /*
    for (int ii=w; ii<(NUMITS-1); ii++)
    {
        fprintf(numfamilies, ",");
    }
    fprintf(numfamilies, "\n");
    */
    
    itsalive = w;
    
    // The means and sds are already set to 2 if they didnt survive, so this will be correct even if itslive!=0
    
    //fprintf(detailsabc, "%d, %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %d\n",  itsalive, countalive, meaneffstrats, meanmobstrats, meanfits, meandrifts, meanqualf, meanquala, sdeffstrats, sdmobstrats, sdfits, sddrifts, sdqualf, sdquala, (double)summovedistance/numbermoves,countallbirths);
    
    if (farming == 1)
    {
        fprintf(detailsabc, "%d, %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f\n",  itsalive, countalive, meaneffstrats, meanmobstrats, meanfits, meandrifts, meanqualf, meanquala);
    }
    if (farming == 0)
    {
        fprintf(detailsabc, "%d, %d, %.3f, %.3f, %.3f, %.3f\n",  itsalive, countalive, meanmobstrats, meanfits, meandrifts, meanqualf);
    }

    
    break; // Goes to next run.
}




#endif
