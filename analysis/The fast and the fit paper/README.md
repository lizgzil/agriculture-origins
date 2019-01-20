# Analysis of model results from the fast and the fit paper

In this analysis folder we use R to analyse the model results given in `data/The fast and the fit paper`. This data was used in the results of The fast and the fit paper (link to follow), so any figure numbers mentioned in here refer to those in that paper.

## Data

Please message me on Github, email me at e.gallagher.12@ucl.ac.uk or [download the data](https://figshare.com/account/projects/58973/articles/7609763) directly from figshare.
Due to large file sizes the data needed for `4. Fitness Oscillations.R` is not on figshare, so please email me directly for this.

## Code

`1. Visualise simulation inputs and outputs.R`

In this R code we look at the data generated from running the model 100,000 times with four parameters randomly varied. Amongst other things we look at the relationship between parameters and the outcomes, the different outcomes that occur in these simulations (Figure 3, `outputhist_foragingmodel20Nov2017.pdf`), and find the correlations between parameters and their simulation outcomes.

`2. Outcomes clustering.R`

In this R code we apply our Outcomes Clustering Method to the data generated from running the model 100,000 times with four parameters randomly varied. This involves first finding the simulation clusters and then comparing the clusters. Amongst other things, we plot the relative density of parameter and outcome values for each cluster (Figure 5, `density_clusters_paramsoutcomes_foragingmodel20Nov2017.pdf`) and the pairwise scatters of outcomes coloured by cluster (Figure 4, `outcomespairs_clusters_foragingmodel20Nov2017.png`). We also computer the statistical differences between fitnesses in the most and least mobile clusters.

`3. Model properties over time.R`

In this R code we look at how the simulation properties change over time for 100 simulations of the model. We generate Figure S6 in this code (`meansovertime_meanmob_foragingmodel20Nov2017_overtime.png`).

`4. Fitness Oscillations.R`

In this code we compare 50 simulations of the model with high mobility parameters, and 50 simulations of the model with low mobility parameters. Here we plot the oscillations in fitness for each of these (Figure S7, `fitness_overtime_lowsims_highsims_foragingmodel17May2018_highmoballinfo.png`), calculate the interquartile range for each simulation (Figure S8 and S9, `rangesovertimelow_foragingmodel17May2018_lowhighmoballinfo.pdf` and `rangesovertimehigh_foragingmodel17May2018_lowhighmoballinfo.pdf`), and perform a t-test to check whether the mean interquartile range of these fitness values is statistically significant. 

## Figures

All figures and tables generated in this analysis are stored in `analysis/The fast and the fit paper/figures`. Some of these will be recognisable from the paper.





