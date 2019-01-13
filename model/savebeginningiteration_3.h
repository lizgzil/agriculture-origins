//
//  savebeginningiteration_3.h
//  Farming_v6_1
//
//  Created by Liz Gallagher on 02/11/2016.
//  Copyright (c) 2016 Liz Gallagher. All rights reserved.
//

#ifndef Foraging_v5_1_savebeginningiteration_3_h
#define Foraging_v5_1_savebeginningiteration_3_h

if (abc == 0)
{
    for (int i=0; i<numfams; i++)
    {
        if (saveless != 2)
        {
            // Just save for certain iteration numbers, only iteration numbers which are multiples of 10?
            if ((w+1) % saveres == 0)
            {
                fprintf(savefamiliesuniquesims, "%.1d, %.1d, %.4f, %.4f, %.4f, %.4f, %.1d\n", w, families[i].famID, families[i].e_strat, families[i].m_strat, families[i].drifttest, families[i].fit, families[i].siteocc);
                
            }
            
        }
        
    }
    if (saveless==0)
    {
        for (int i=0; i<NUMSITES; i++)
        {
            fprintf(savesites, "%.1d, %.1d,%.1d,%d,%.1d,%.4f,%.4f", rr, w, sites[i].siteID,sites[i].occ,sites[i].countocc,sites[i].qual_f,sites[i].qual_a);
            
            fprintf(famsocc, "%.1d, %.1d,%.1d,%d,",rr,w,sites[i].siteID,sites[i].countocc);
            
            if (sites[i].countocc == 0)
            {
                fprintf(famsocc," ");
            }
            else
            {
                for (int j=0; j<sites[i].countocc; j++)
                {
                    fprintf(famsocc, "%d,", (*sites[i].fam_occ[j]).famID);
                }
            }
            
            fprintf(savesites,"\n");
            fprintf(famsocc,"\n");
        }
    }
    if (saveless!=2)
    {
        fprintf(numfamilies, "%d,%d, %d\n", rr, w,numfams);
        
        
        for (int i=0; i<NUMSITES; i++)
        {
            fprintf(savesites, "%.1d, %.1d,%.1d,%d,%.1d,%.4f,%.4f", rr, w, sites[i].siteID,sites[i].occ,sites[i].countocc,sites[i].qual_f,sites[i].qual_a);
            fprintf(savesites,"\n");
        }
        
    }
}
else
{
    
    if ((saveless == 3) & (w == (NUMITS-1)))
    {
        // Save all sites and families every iteration
        
        for (int i=0; i<NUMSITES; i++)
        {
           //fprintf(savesites, "%.1d, %.1d,%.1d,%.1d,%.4f,%.4f\n", rr, w, sites[i].siteID,sites[i].countocc,sites[i].qual_f,sites[i].qual_a);
        }
        
        for (int i=0; i<numfams; i++)
        {
            //(savefamilies, "%.1d, %.1d, %.1d, %.4f, %.4f, %.4f, %.4f, %.1d\n", rr, w, families[i].famID, families[i].e_strat, families[i].m_strat, families[i].drifttest, families[i].fit, families[i].siteocc);
        }
    }
    
}


#endif
