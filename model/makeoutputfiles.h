//
//  makeoutputfiles.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#ifndef Foraging_v5_1_makeoutputfiles_h
#define Foraging_v5_1_makeoutputfiles_h

char const *save1 = "detailsabc";
char const *save2 = "details";
char const *save3 = "Rdetails";
char const *save4 = "families";
char const *save5 = "sites";
char const *save6 = "birthstuff";
char const *save7 = "exfams";
char const *save8 = "numfamilies";
char const *save9 = "famsocc";
char const *save12 = "endmeans";
char const *save15 = "endfamilymobs";
char const *save16 = "endinfo";
char const *save17 = "meanmobs";
char const *save18 = "endfamilynulls";
char const *save20 = "variabilitygrandlamdba";
char const *save21 = "initialfaminfo";
char const *save22 = "initialsiteinfo";
char const *save23 = "variabilitymeangr";
char const *save24 = "variabilitymeanlamdba";
char const *save25 = "variabilitymeanbeta";
char const *save26 = "variabilitymeandelta";
char const *save27 = "variabilityrangegr";
char const *save28 = "variabilitygr";
char const *save29 = "variabilitylamdba";

FILE * detailsabc;
FILE * details;
FILE * Rdetails;
FILE * savefamilies;
FILE * savesites;
FILE * birthstuff;
FILE * exfams;
FILE * numfamilies;
FILE * famsocc;
FILE * endmeans;
FILE * endfamilymobs;
FILE * endinfo;
FILE * meanmobs;
FILE * endfamilynulls;
FILE * variabilitygrandlamdba;
FILE * initialfaminfo;
FILE * initialsiteinfo;
FILE * variabilitymeangr;
FILE * variabilitymeanlamdba;
FILE * variabilitymeanbeta;
FILE * variabilitymeandelta;
FILE * variabilityrangegr;
FILE * variabilitygr;
FILE * variabilitylamdba;

char fileSpec2[strlen(save2)+strlen(extension)+1];
snprintf(fileSpec2, sizeof(fileSpec2), "%s%s", save2, extension);
details = fopen(fileSpec2, "a+");

char fileSpec3[strlen(save3)+strlen(extension)+1];
snprintf(fileSpec3, sizeof(fileSpec3), "%s%s", save3, extension);
Rdetails = fopen(fileSpec3, "a+");

if (sameinitialcond == 1)
{
    char fileSpec21[strlen(save21)+strlen(extension)+1];
    snprintf(fileSpec21, sizeof(fileSpec21), "%s%s", save21, extension);
    initialfaminfo = fopen(fileSpec21, "a+");
    
    char fileSpec22[strlen(save22)+strlen(extension)+1];
    snprintf(fileSpec22, sizeof(fileSpec22), "%s%s", save22, extension);
    initialsiteinfo = fopen(fileSpec22, "a+");
}

if (abc == 0)
{
    if (saveless == 2)
    {
        // Only save the end iteration info
        char fileSpec16[strlen(save16)+strlen(extension)+1];
        snprintf(fileSpec16, sizeof(fileSpec16), "%s%s", save16, extension);
        endinfo = fopen(fileSpec16, "a+");
        
        char fileSpec17[strlen(save17)+strlen(extension)+1];
        snprintf(fileSpec17, sizeof(fileSpec17), "%s%s", save17, extension);
        meanmobs = fopen(fileSpec17, "a+");
    }
    else
    {
        
        char fileSpec4[strlen(save4)+strlen(extension)+1];
        snprintf(fileSpec4, sizeof(fileSpec4), "%s%s", save4, extension);
        savefamilies = fopen(fileSpec4, "a+");
        
        char fileSpec12[strlen(save12)+strlen(extension)+1];
        snprintf(fileSpec12, sizeof(fileSpec12), "%s%s", save12, extension);
        endmeans = fopen(fileSpec12, "a+");
        
        char fileSpec5[strlen(save5)+strlen(extension)+1];
        snprintf(fileSpec5, sizeof(fileSpec5), "%s%s", save5, extension);
        savesites = fopen(fileSpec5, "a+");
        
        char fileSpec8[strlen(save8)+strlen(extension)+1];
        snprintf(fileSpec8, sizeof(fileSpec8), "%s%s", save8, extension);
        numfamilies = fopen(fileSpec8, "a+");
        
        if (saveless == 0)
        {
            // Save even more
            char fileSpec6[strlen(save6)+strlen(extension)+1];
            snprintf(fileSpec6, sizeof(fileSpec6), "%s%s", save6, extension);
            birthstuff = fopen(fileSpec6, "a+");
            
            char fileSpec7[strlen(save7)+strlen(extension)+1];
            snprintf(fileSpec7, sizeof(fileSpec7), "%s%s", save7, extension);
            exfams = fopen(fileSpec7, "a+");
            
            char fileSpec9[strlen(save9)+strlen(extension)+1];
            snprintf(fileSpec9, sizeof(fileSpec9), "%s%s", save9, extension);
            famsocc = fopen(fileSpec9, "a+");
        }
    }
}
else
{
    // For abc
    
    char fileSpec1[strlen(save1)+strlen(extension)+1];
    snprintf(fileSpec1, sizeof(fileSpec1), "%s%s", save1, extension);
    detailsabc = fopen(fileSpec1, "a+");
    
    if (saveless == 3)
    {
        // Save all sites and families every iteration
        
        char fileSpec4[strlen(save4)+strlen(extension)+1];
        snprintf(fileSpec4, sizeof(fileSpec4), "%s%s", save4, extension);
        savefamilies = fopen(fileSpec4, "a+");
        
        char fileSpec5[strlen(save5)+strlen(extension)+1];
        snprintf(fileSpec5, sizeof(fileSpec5), "%s%s", save5, extension);
        savesites = fopen(fileSpec5, "a+");
    }
    
    /*
    char fileSpec15[strlen(save15)+strlen(extension)+1];
    snprintf(fileSpec15, sizeof(fileSpec15), "%s%s", save15, extension);
    endfamilymobs = fopen(fileSpec15, "a+");
    
    char fileSpec18[strlen(save18)+strlen(extension)+1];
    snprintf(fileSpec18, sizeof(fileSpec18), "%s%s", save18, extension);
    endfamilynulls = fopen(fileSpec18, "a+");
    
    char fileSpec8[strlen(save8)+strlen(extension)+1];
    snprintf(fileSpec8, sizeof(fileSpec8), "%s%s", save8, extension);
    numfamilies = fopen(fileSpec8, "a+");
     */
}

if (variability == 1) // Save every iteration for non FIO, and just last for with FIO
{
    char fileSpec20[strlen(save20)+strlen(extension)+1];
    snprintf(fileSpec20, sizeof(fileSpec20), "%s%s", save20, extension);
    variabilitygrandlamdba = fopen(fileSpec20, "a+");
    
    char fileSpec23[strlen(save23)+strlen(extension)+1];
    snprintf(fileSpec23, sizeof(fileSpec23), "%s%s", save23, extension);
    variabilitymeangr = fopen(fileSpec23, "a+");
    
    char fileSpec24[strlen(save24)+strlen(extension)+1];
    snprintf(fileSpec24, sizeof(fileSpec24), "%s%s", save24, extension);
    variabilitymeanlamdba = fopen(fileSpec24, "a+");
    
    char fileSpec25[strlen(save25)+strlen(extension)+1];
    snprintf(fileSpec25, sizeof(fileSpec25), "%s%s", save25, extension);
    variabilitymeanbeta = fopen(fileSpec25, "a+");
    
    char fileSpec26[strlen(save26)+strlen(extension)+1];
    snprintf(fileSpec26, sizeof(fileSpec26), "%s%s", save26, extension);
    variabilitymeandelta = fopen(fileSpec26, "a+");
    
    char fileSpec28[strlen(save28)+strlen(extension)+1];
    snprintf(fileSpec28, sizeof(fileSpec28), "%s%s", save28, extension);
    variabilitygr = fopen(fileSpec28, "a+");
    
    char fileSpec29[strlen(save29)+strlen(extension)+1];
    snprintf(fileSpec29, sizeof(fileSpec29), "%s%s", save29, extension);
    variabilitylamdba = fopen(fileSpec29, "a+");
    
}

if (sparvar == 1 | sparvar == 2 | sparvar == 3)
{
    char fileSpec23[strlen(save23)+strlen(extension)+1];
    snprintf(fileSpec23, sizeof(fileSpec23), "%s%s", save23, extension);
    variabilitymeangr = fopen(fileSpec23, "a+");
    
    char fileSpec27[strlen(save27)+strlen(extension)+1];
    snprintf(fileSpec27, sizeof(fileSpec27), "%s%s", save27, extension);
    variabilityrangegr = fopen(fileSpec27, "a+");
    
    
    char fileSpec4[strlen(save4)+strlen(extension)+1];
    snprintf(fileSpec4, sizeof(fileSpec4), "%s%s", save4, extension);
    savefamilies = fopen(fileSpec4, "a+");
    
    char fileSpec5[strlen(save5)+strlen(extension)+1];
    snprintf(fileSpec5, sizeof(fileSpec5), "%s%s", save5, extension);
    savesites = fopen(fileSpec5, "a+");
}


// Print the headings/titles of the files (nice readable version):
fprintf(details, "------- Options:\nabc,farming,seedinit,legion,variability,varrunintime,WD,sparvar,whichparam,saveless,saveres,sameinitialcond\n");
fprintf(details, "%d ,%d,%d,%d,%d,%d,%.4f,%d,%d,%d,%d,%d \n\n", abc,farming,seedinit,legion,variability,varrunintime,WD,sparvar,whichparamx,whichparamy,saveless,saveres,sameinitialcond);

fprintf(details, "------- Standard parameters:\nrepeats,NUMITS,MAXNUMFAMS,NUMSITES,spatialx,spatialy,seedstrat,INITLOWERM,INITLOWERE,MINQF,MINQA,percentageinitocc,INITNUMFAMS\n");
fprintf(details, "%d,%d,%d,%d,%d,%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%d\n\n", repeats,NUMITS,MAXNUMFAMS,NUMSITES,spatialx,spatialy,seedstrat,INITLOWERM,INITLOWERE,MINQF,MINQA,percentageinitocc,INITNUMFAMS);

fprintf(details, "------- Variable parameters (4d.p):\n GR,LAMBDA, PHI, BETA, DELTA,nmax, deathfit,fl,fu,kappam,kappae,mut, ETA\n");
fprintf(details, "%.4f,%.4f    , %d , %.4f  , %.4f   ,%d   , %.4f      ,%.4f,%.4f,%d    ,%d    ,%.4f , %.4f \n\n", GR,LAMBDA, PHI, BETA, DELTA,nmax, deathfit,fl,fu,kappam,kappae,mut, ETA);

fclose(details);

/*
// Print the headings/titles of the files (nice readable version):
fprintf(details, "------- Options:\nlegion, abc, saveless, saveres,  sameinitialcond,  variability\n");
fprintf(details, "  %d,       %d,          %d,       %d,    %d,    %d\n\n", legion, abc, saveless, saveres, sameinitialcond, variability);

fprintf(details, "------- Standard parameters:\nrepeats, NUMITS, NUMSITES, MAXNUMFAMS,  spatialx, spatialy, INITLOWERM, INITLOWERE, MINQF, MINQA\n");
fprintf(details, "  %d,       %d,          %d,  %d,     %d,    %d, %.4f, %.4f, %.4f, %.4f\n\n", repeats, NUMITS, NUMSITES, MAXNUMFAMS, spatialx, spatialy, INITLOWERM, INITLOWERE, MINQF, MINQA);

fprintf(details, "------- Variable parameters (4d.p):\n GR, LAMBDA, PHI, BETA, DELTA, nmax, mut, deathfit, percentageinitocc, INITNUMFAMS, fl, fu, kappam, kappae, ETA\n");
fprintf(details, "%.4f, %.4f, %d, %.4f, %.4f,  %d,  %.4f, %.4f,   %.4f, %d, %.4f, %.4f, %d,%d,%.4f \n\n", GR, LAMBDA, PHI, BETA, DELTA, nmax, mut, deathfit, percentageinitocc, INITNUMFAMS, fl, fu, kappam, kappae, ETA);

fclose(details);
*/

// Print the headings/titles of the files (version for R):
fprintf(Rdetails, "legion, abc, saveless, saveres,  sameinitialcond,  variability,repeats, NUMITS, NUMSITES, MAXNUMFAMS, spatialx, spatialy, INITLOWERM, INITLOWERE, MINQF, MINQA, GR, LAMBDA, PHI, BETA, DELTA, nmax, mut, deathfit, percentageinitocc, INITNUMFAMS, fl, fu, kappam, kappae, ETA\n");
fprintf(Rdetails, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d, %d,%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%d,%.4f,%.4f,%d,%.4f, %.4f,%.4f,%d,%.4f,%.4f,%d,%d,%.4f\n",legion, abc, saveless, saveres,  sameinitialcond,  variability,repeats, NUMITS, NUMSITES, MAXNUMFAMS, spatialx, spatialy, INITLOWERM, INITLOWERE, MINQF, MINQA, GR, LAMBDA, PHI, BETA, DELTA, nmax, mut, deathfit, percentageinitocc, INITNUMFAMS, fl, fu, kappam, kappae, ETA);
fclose(Rdetails);



if (abc == 0)
{
    // Save more details if there is no abc
    
    if (saveless == 0)
    {
        fprintf(savefamilies, "Run, Iteration, famID, fit, e_strat, m_strat, drifttest, mcount, siteocc, oldsiteocc \n");
        fprintf(savesites, "Run, Iteration, siteID, occ, countocc, qual_f, qual_a\n");
        
        fprintf(numfamilies, "Run, Iteration, Number of families\n");
        fprintf(birthstuff, "Run number, Iteration, Parent ID, Baby ID\n");
        fprintf(exfams, "Run number, Iteration, FamID of families which died\n");
        fprintf(famsocc, "Run, Iteration, siteID, how many occupy, occupants\n");
    }
    else if (saveless == 1)
    {
        fprintf(savefamilies, "Run, Iteration, famID, e_strat, m_strat, drifttest\n");
        fprintf(savesites, "Run, Iteration, siteID, occ, countocc, qual_f, qual_a\n");
        fprintf(numfamilies, "Run, Iteration, Number of families\n");
    }
    else
    {
        fprintf(endinfo, "Run, Week, NumberAgents, MeanEff, SDEff, MeanMob, SDMob, MeanNull, SDNull, MeanFit, SDFit, MeanQf, SDQf, MeanQa, SDQa \n");
        fprintf(meanmobs, "Run, Week, MeanMob, MeanEff\n");
    }
}
else
{
    //fprintf(detailsabc, "GR, LAMBDA, PHI, BETA, DELTA, kappam, kappae, fu, ETA, nmax, mut, percentageinitocc, initialmeaneff, initialmeanmob, initialmeannull, itsalive, countalive, meaneffstrats, meanmobstrats, meanfits, meandrifts, meanqualf, meanquala \n");
    
    //fprintf(detailsabc, "GR, LAMBDA, PHI, BETA, DELTA, kappam, kappae, fu, ETA, nmax, mut, percentageinitocc, initialmeaneff, initialmeanmob, initialmeannull, itsalive, countalive, meaneffstrats, meanmobstrats, meanfits, meandrifts, meanqualf, meanquala, sdeffstrats, sdmobstrats, sdfits, sddrifts, sdqualf, sdquala, averagemovedistance,countallbirths \n");
}


#endif
