library(wesanderson)
library(mclust)

setwd("/Users/lizgallagher/Code/agriculture-origins/analysis/The fast and the fit paper")

# ------------------------------------------------------------------

# 0. Import data and get simulations with >=15 agents in the final iteration
# 1. Fit clusters to the first 10,000 simulations
# 2. Predict clusters using the fitted model
# 3. Get the mean mobility for each cluster
# 4. Get the number of simulations in each cluster
# 5. Get the colours for each cluster -  most mobile cluster is red, least is blue
# 6. Key for colours
# 7. Relative density of parameters and outcomes for each cluster - Figure 5
# 8. Plot pairwise outputs in the cluster colours - Figure 4
# 9. Find default parameter values for each of the clusters.
# 10. Get the mean and the standard deviation for each of the clusters
# 11. Are the distributions of fitness values in the most and least mobile clusters significantly different?

# ------------------------------------------------------------------

# ------------------------------------------------------------------
# 0. Import data and get simulations with >=15 agents in the final iteration

dateuse = "foragingmodel20Nov2017"

fionum = 4 # We varied 4 parameters in this run of the model

details <- read.csv(paste("../../data/The fast and the fit paper/Rdetails_", dateuse, ".txt", sep = ""), sep = ",", header=T);
sims <- read.csv(paste("../../data/The fast and the fit paper/detailsabc_", dateuse, ".txt", sep = ""), sep = ",", header=F);

numits = details$NUMITS
repeats = details$repeats
numsites = details$NUMSITES

numsims = nrow(sims)

params = c("r", expression(lambda), expression(kappa[m]), expression(eta),
           "Initial mean mobility strategy","Initial mean null strategy",
           "Iterations alive", "Final number of agents", 
           "Final mean mobility strategy", "Final mean fitness", "Final mean null strategy", 
           "Final mean foraging quality");

mins = rep(NA, ncol(sims))
maxs = rep(NA, ncol(sims))
for (i in 1:ncol(sims))
{
  mins[i] = min(sims[,i], na.rm=TRUE)
  maxs[i] = max(sims[,i], na.rm=TRUE)
}

maxs[fionum+2+2+1:3] = 1 # since some are set to 2 if they die off

# Separate out the simulations with >= 15 agents alive in the last simulation

finsims = sims[which((sims[,fionum + 2 + 1]==numits-1) & (sims[,fionum + 2 + 2]!=0)),] # iterations alive = 199 and number alive !=0
nrow(finsims)*100/numsims
deadsims = sims[which((sims[,fionum + 2 + 1]!=numits-1) & (sims[,fionum + 2 + 2]==0)),]
nrow(deadsims)*100/numsims

selectfinsims = finsims[which(finsims[,fionum + 2 + 2]>=15),]; # The number of agents at the end is over a threshold of 10
deselectfinsims = sims[which(sims[,fionum + 2 + 2]<15),];


# ------------------------------------------------------------------
# 1. Fit clusters to the first 10,000 simulations

selectfinsims_num = selectfinsims[complete.cases(selectfinsims),]
df2 = data.frame(selectfinsims_num)
colnames(df2) <- params

# 10k: 

fit <- Mclust(df2[1:10000, fionum+2+c(2:4,6)]) # on all the raw outcomes (no PCA)

howmanclus = length(unique(fit$classification))
fitclass = fit$classification

# ------------------------------------------------------------------
# 2. Predict clusters using the fitted model

# Sometimes it's best to predict all. When there are loads of outcomes PCA will be useful, but 4 isnt many

clustpredict <- predict.Mclust(fit, df2[, fionum+2+c(2:4,6)])
clustpredict = clustpredict[[1]]

# ------------------------------------------------------------------
# 3. Get the mean mobility for each cluster

meanmobclusts = rep(NA, howmanclus)
for (j in 1:howmanclus)
{
  meanmobclusts[j] = mean(selectfinsims_num[which(clustpredict==j),fionum+2+3])
}
mob2sedord = order(meanmobclusts, decreasing = T)
mobclust = mob2sedord[1]
sedclust = mob2sedord[howmanclus]


# ------------------------------------------------------------------
# 4. Get the number of simulations in each cluster

numeach = rep(NA, howmanclus)
for (j in 1:howmanclus)
{
  numeach[j] = nrow(selectfinsims_num[which(clustpredict==j),])
  print(j)
}


# ------------------------------------------------------------------
# 5. Get the colours for each cluster -  most mobile cluster is red, least is blue

colst = wes_palette("Zissou", howmanclus, type = "continuous")

cols = colst[order(rev(mob2sedord
), decreasing = F)]

# ------------------------------------------------------------------
# 6. Key for colours

pdf(paste("figures/clusters_key_",dateuse,".pdf",sep=""), width = 3, height = 2)
par( oma=c(0,1,1,1),mar=c(0,1,1,1), cex = 0.8)
plot(1,1,col="white",bty = "n",xlab="",ylab="",yaxt="n",xaxt="n")
legend("topright",paste(c("Most mobile",rep("",howmanclus-2),"Least mobile")," (n = ",numeach[mob2sedord],")",sep="") ,
       col = cols[mob2sedord], bty = "n", lty = 1, lwd = 2, cex = 1)
dev.off()


# ------------------------------------------------------------------
# 7. Relative density of parameters and outcomes for each cluster - Figure 5

maxs_smol = maxs
maxs_smol[10] = 0.75

maxd = c(0.015,0.012,0.004,0.02,0,0,0,0.06,0.02,0.014,0.006,0.02)
mind = rep(0,length(maxd))

pdf(paste("figures/density_clusters_paramsoutcomes_",dateuse,".pdf",sep=""), width = 7, height = 3)
par(mfrow=c(2,5), oma=c(1,1,1,1),mar=c(4,4,1,1), mgp = c(2.7,1,0), ps = 10) #, cex = 0.8)

for (i in c(1:fionum, fionum+2+c(2:6)))
{
  for (j in 1:howmanclus)
  {
    if (j==mobclust | j==sedclust)
    {
      linethick = 2.5 # thicker lines for the most and least mobile
    } else
    {
      linethick = 1.2
    }
    
    d = density(selectfinsims_num[which(clustpredict==j),i], from = mins[i], to = maxs_smol[i])
    
    plot(d$x,d$y/sum(d$y), type="l", main="", xlab = "", ylab = "", xaxt="n", yaxt="n", bty="n",
         xlim=c(mins[i],maxs_smol[i]), lwd = linethick,ylim = c(mind[i],maxd[i]), col = cols[j])
    par(new=TRUE)
  }
  axis(1)
  axis(2)
  
  
  # for some reason a for loop doesnt like the \n in title names
  
  if (i<=fionum)
  {
    title(xlab  = params[i], ylab = "Relative density")
  } else if (i == fionum+2+2)
  {
    title(xlab  = "Final number of\nagents", ylab = "Relative density")
  } else if (i == fionum+2+3)
  {
    title(xlab  = "Final mean\nmobility strategy", ylab = "Relative density")
  } else if (i == fionum+2+4)
  {
    title(xlab  = "Final mean\nfitness", ylab = "Relative density")
  } else if (i == fionum+2+5)
  {
    title(xlab  = "Final mean\nnull strategy", ylab = "Relative density")
  } else if (i == fionum+2+6)
  {
    title(xlab  = "Final mean\nforaging quality", ylab = "Relative density")
  }
  
  par(new=FALSE)
  if (i == 4)
  {
    par(mar=c(0,0,0,0))
    plot(1,1,col="white",bty = "n",xlab="",ylab="",yaxt="n",xaxt="n")
    legend("center", c("Most mobile", "Least mobile"), 
           col = cols[c(mobclust, sedclust)], bty = "n", lty = 1, lwd = 2)
    # back to normal:
    par(mar=c(4,4,1,1)) 
    
  }
}
dev.off()



# ------------------------------------------------------------------
# 8. Plot pairwise outputs in the cluster colours - Figure 4

ptsz = 0.4

pairs = combn(c(fionum+2+c(2:4,6)), 2)

png(filename = paste("figures/outcomespairs_clusters_",dateuse,".png",sep=""), width = 2280, height = 1400, bg = "white") 
par(mfrow=c(2,3))

par(cex.lab=5, cex.axis=5,cex.sub=8,cex.main = 4)
par(mar = c(15, 20,7, 3), oma = c(3,3, 3, 3), mgp = c(12, 4, 0))

for (jj in 1:ncol(pairs))
{
xtype = pairs[1,jj]
ytype = pairs[2,jj]

# Plotted in a random order:

plot(selectfinsims_num[,xtype], selectfinsims_num[,ytype], pch = 16, cex = ptsz, 
     col = cols[clustpredict], xaxt="n", yaxt="n", bty="n",
     xlab ="", ylab ="", xlim = c(mins[xtype],maxs[xtype]), ylim = c(mins[ytype],maxs[ytype])) 

par(new=FALSE)
axis(1)
axis(2)
title(xlab = params[xtype], ylab = params[ytype])
}
dev.off()


# ------------------------------------------------------------------
# 9. Find default parameter values for each of the clusters.

# Get highest density value

colsused = c(1:fionum,fionum+2+c(2:4,6))
df = matrix(NA, howmanclus, length(colsused)+1)
for (c in 1:howmanclus)
{
  thisclust = selectfinsims_num[which(clustpredict==c),]
  
  df[c,1] = nrow(thisclust)
  
  for (i in 1:length(colsused))
  {
    z <- density(thisclust[,colsused[i]])
    df[c,i+1] = z$x[z$y==max(z$y)]
  }
} 

df = df[mob2sedord,] # In order from most to least mobile clusters

colnames(df) <- c("Number of simulations",params[colsused])

df = round(df,3)

write.csv(df, paste("figures/mostpopularvalues_clusters_",dateuse,".csv",sep=""),row.names=T) 



# ------------------------------------------------------------------
# 10. Get the mean and the standard deviation for each of the clusters

# 95% CIs = mean +- 1.96*(sd/sqrt(n))
# PP = (sd/sqrt(n))

colsused = c(1:fionum,fionum+2+c(2:4,6))
dfmean = matrix(NA, howmanclus, length(colsused)+1)
dfsd = matrix(NA, howmanclus, length(colsused)+1)
dfPP = matrix(NA, howmanclus, length(colsused)+1)


for (c in 1:howmanclus)
{
  thisclust = selectfinsims_num[which(clustpredict==c),]
  
  dfmean[c,1] = nrow(thisclust)
  dfsd[c,1] = nrow(thisclust)
  dfPP[c,1] = nrow(thisclust)
  
  for (i in 1:length(colsused))
  {
    dfmean[c,i+1] = mean(thisclust[,colsused[i]])
    dfsd[c,i+1] = sd(thisclust[,colsused[i]])
    dfPP[c,i+1] = sd(thisclust[,colsused[i]])/sqrt(nrow(thisclust))
  }
} 

dfmean = dfmean[mob2sedord,] # In order from most to least mobile clusters
dfsd = dfsd[mob2sedord,] # In order from most to least mobile clusters
dfPP = dfPP[mob2sedord,] # In order from most to least mobile clusters


colnames(dfmean) <- c("Number of simulations",params[colsused])
colnames(dfsd) <- c("Number of simulations",params[colsused])
colnames(dfPP) <- c("Number of simulations",params[colsused])

dfmean = round(dfmean,3)
dfsd = round(dfsd,3)
dfPP = round(dfPP,5)


write.csv(dfmean, paste("figures/Means_clusters_",dateuse,".csv",sep=""),row.names=T) 
write.csv(dfsd, paste("figures/SDs_clusters_",dateuse,".csv",sep=""),row.names=T) 
write.csv(dfPP, paste("figures/SDdividedbysqrtn_clusters_",dateuse,".csv",sep=""),row.names=T) 


# ------------------------------------------------------------------
# 11. Are the distributions of fitness values in the most and least mobile clusters significantly different?

i = 10 # Fitness info

d1 = selectfinsims_num[which(clustpredict==mobclust),i]
d2 = selectfinsims_num[which(clustpredict==sedclust),i]

# Are distributions the same?
ks.test(d1, d2)
# Are means the same?
t.test(d1, d2)
