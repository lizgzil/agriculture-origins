library(wesanderson)

setwd("/Users/lizgallagher/Code/agriculture-origins/analysis/The fast and the fit paper")

# This code produces Fig. S6 in the supplementary material

# ------------------------------------------------------------------

# 0. Import data and get simulations agents alive in the final iteration
# 1. Plot means over time for each simulation. Coloured by final mean effort and mean mob

# ------------------------------------------------------------------

# ------------------------------------------------------------------
# 0. Import data and get simulations agents alive in the final iteration

dateuse = "foragingmodel20Nov2017_overtime"

fionum = 4 # We varied 4 parameters in this run of the model

details <- read.csv(paste("../../data/The fast and the fit paper/Rdetails_", dateuse, ".txt", sep = ""), sep = ",", header=T);
sims <- read.csv(paste("../../data/The fast and the fit paper/detailsabc_", dateuse, ".txt", sep = ""), sep = ",", header=F);

numits = details$NUMITS
repeats = details$repeats
numsites = details$NUMSITES

params = c("r", expression(lambda), expression(kappa[m]), expression(eta))

# This file saves mean qa and effort strategy even though it is the forager model, so I dont care whats in there
outcomenames = c("Iterations alive", "Final number of agents", 
                 "Final mean effort strategy", "Final mean mobility strategy", "Final mean fitness", "Final mean null strategy", 
                 "Final mean foraging quality","Final mean farming quality");

nn = numits; # Number of times recorded
ipp = 2 # The initial things
pp = fionum + ipp # Number of parameters and initial things
rr = 8; # Number of things recorded each time

ws = sims[,c(pp+1+(1:nn -1)*rr)]

# Colour by final mean mob and eff
finalcolsims = rgb(sims[,pp+numits*rr +4],0.8*sims[,pp+numits*rr +3],1-sims[,pp+numits*rr +4])
finalcolsimsalpha = rgb(sims[,pp+numits*rr +4],0.8*sims[,pp+numits*rr +3],1-sims[,pp+numits*rr +4],0.5)

finsims = sims[which((sims[,pp+numits*rr +1]==numits-1) & (sims[,pp+numits*rr +2]!=0)),] # iterations alive = 199 and number alive !=0
dim(finsims[complete.cases(finsims),])


# ------------------------------------------------------------------
# 1. Plot means over time for each simulation. Coloured by final mean effort and mean mob

colsgw = wes_palette("Zissou", 3, type = "continuous")
colfunc <- colorRampPalette(c(colsgw[1], colsgw[2], colsgw[3]))
cols = colfunc(101)

linewdt = 0.3
enditeration = 500

colby = 2
colbyname = "meanmob"
png(filename = paste("figures/meansovertime_",colbyname,"_",dateuse,".png",sep=""), width = 1533, height = 1100, bg = "white")
par(mfrow=c(2,2), oma=c(0.5,0.5,0.5,0.5), mar = c(12,12,5,2), mgp =c(7,2.5,0), cex.lab = 4.5, cex.axis = 4)

for (j in c(1,3,4,6))
{
  columns = sims[, fionum+ipp+1+j + ((1:enditeration)-1)*rr]
  ylabs = c("Number of agents", "Mean effort strategy","Mean mobility strategy", 
            "Mean fitness", "Mean null strategy", "Mean foraging quality", "Mean farming quality")[j]
  
  for (i in 1:100)
  {
    colhere = 'black'
    
    if (i==1)
    {
      plot(1:enditeration, c(t(columns[i,])), 
           type = "l", ylim = c(min(columns, na.rm = T),max(columns, na.rm = T)),xlim = c(0,enditeration), 
           col = colhere, ylab = "", xlab = "", lwd = linewdt, xaxt="n", yaxt="n", bty="n")
      par(new=TRUE)
    } else
    {
      plot(1:enditeration, c(t(columns[i,])),
           type = "l", ylim = c(min(columns, na.rm = T),max(columns, na.rm = T)), xlim = c(0,enditeration),
           col = colhere, ylab = "", xlab ="", xaxt="n", yaxt="n", bty="n", lwd = linewdt)
      par(new=TRUE)
    }
  }
  axis(1)
  axis(2)
  title(ylab = ylabs, xlab = "Iteration")
  par(new=FALSE)
  print(j)
}
dev.off()


