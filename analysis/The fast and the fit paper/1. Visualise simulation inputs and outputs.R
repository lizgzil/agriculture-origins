library(wesanderson)
library(Hmisc)

setwd("/Users/lizgallagher/Code/agriculture-origins/analysis/The fast and the fit paper")

# ------------------------------------------------------------------

# 0. Import data
# 1. Separate out the simulations with >= 15 agents alive in the last simulation
# 2. Number of agents at the end
# 3. Scatter parameter values against final mean mobility
# 4. Scatter plots of all pairs of outcomes (no null)
# 5. Scatters of all pairs of outcomes (no null), coloured by a third parameter
# 6. Output value histograms - Figure 3
# 7. Correlations of outcomes and parameters

# ------------------------------------------------------------------

# ------------------------------------------------------------------
# 0. Import data

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

maxs[fionum+2+2+1:3] = 1 # since some of these variables are set to 2 if they die off

it_alive_index = 7 # column number for "Iterations alive"
fin_num_index = 7 # column number for "Final number of agents"

num_agents_threshold = 15 # threshold for the final number of agents

# ------------------------------------------------------------------
# 1. Separate out the simulations with >= 15 agents alive in the last simulation

finsims = sims[which((sims[,it_alive_index]==numits-1) & (sims[,fin_num_index]!=0)),] # iterations alive = 199 and number alive !=0
deadsims = sims[which((sims[,it_alive_index]!=numits-1) & (sims[,fin_num_index]==0)),]

selectfinsims = finsims[which(finsims[,fin_num_index]>=num_agents_threshold),]; # The number of agents at the end is over a threshold of 10
deselectfinsims = sims[which(sims[,fin_num_index]<num_agents_threshold),];

# ------------------------------------------------------------------
# 2. Number of agents at the end

vp = num_agents_threshold
pdf(paste("figures/numberofagentshist_",dateuse,".pdf",sep=""), height=5, width=6) # height=9, width=24
hist(finsims[,fin_num_index], breaks = 10000, xlab = params[17],main = "")
abline(v=vp, col = "red", lty = 2)
text(vp+190,15000,paste("Number of agents =", vp), col = "red")
dev.off()

# ------------------------------------------------------------------
# 3. Scatter parameter values against final mean mobility

ptsz = 0.3

# 2x2
png(filename = paste("figures/scatter_params_meanmob_",dateuse,".png",sep=""), width = 1600, height = 1300, bg = "white")
par(mfrow=c(2,2))
par(cex.lab=4, cex.axis=4.5, cex.sub=4, cex.main = 4)
par(mar = c(15, 25, 4, 4), oma = c(0, 0, 0, 0), mgp = c(12, 4, 0))

for (jj in c(1:fionum)) # c(1:9,11:12)
{
  xtype = jj;
  ytype = fionum+2+3
  
  # All data:
  jitx = 0;
  jitx =  (xtype==3 | xtype == 4)
  plot(jitter(selectfinsims[,xtype],jitx*2.5), selectfinsims[,ytype], pch = 16, cex = ptsz, 
       col = "black", xaxt="n", yaxt="n", bty="n",
       xlab ="", ylab ="", xlim = c(mins[xtype],maxs[xtype]), ylim = c(mins[ytype],maxs[ytype])) 
  axis(1)
  axis(2)
  title(xlab = params[xtype], ylab = params[ytype])
  par(new=FALSE)
}
dev.off()

# ------------------------------------------------------------------
# 4. Scatter plots of all pairs of outcomes (no null)

pairs = combn(c(fionum + 2 + c(2:4,6)),2)

ptsz = 0.3

png(filename = paste("figures/scatter_outcomespairs_",dateuse,".png",sep=""), width = 2250, height = 1333, bg = "white") # width = 2000, height = 2700
par(mfrow=c(2,3))
par(cex.lab=5, cex.axis=4, cex.sub=4, cex.main = 4)
par(mar = c(15, 25, 4, 4), oma = c(5, 5, 1, 1), mgp = c(12, 4, 0))
for (i in 1:ncol(pairs))
{
  plot(selectfinsims[,pairs[1,i]], selectfinsims[,pairs[2,i]], pch = 16, cex = ptsz, 
       xlab = params[pairs[1,i]], ylab = params[pairs[2,i]], xaxt = "n", yaxt = "n", bty = "n")

  legend("bottomright",legend = bquote(rho == .(round(cor(selectfinsims[,pairs[1,i]], selectfinsims[,pairs[2,i]]),3))), 
         cex = 5, bty = "n", 
         text.col = "red")
  axis(1)
  axis(2)
}
dev.off()

# ------------------------------------------------------------------
# 5. Scatters of all pairs of outcomes (no null), coloured by a third parameter

colsgw = wes_palette("Zissou", 3, type = "continuous")
colfunc <- colorRampPalette(c(colsgw[1], colsgw[2], colsgw[3]))
colsg = colfunc(101)

pairs = combn(c(fionum + 2 + c(2,6,4,3)),3) # In this the colour will never be number of agents (makes things easier)

ptsz = 0.5

png(filename = paste("figures/scatter_outcomes_3D_",dateuse,".png",sep=""), width = 2400, height = 1700, bg = "white") # width = 2000, height = 2700
par(mfrow=c(2,3))
layout(matrix(c(1:6), 2, 3, byrow = TRUE), widths=c(3,3,1))
par(cex.lab=7, cex.axis=6, cex.sub=4, cex.main = 5)
par(mar = c(25, 30, 8, 4), oma = c(1, 1, 3, 1), mgp = c(12, 4, 0))
for (i in 1:ncol(pairs))
{
  plot(selectfinsims[,pairs[1,i]], selectfinsims[,pairs[2,i]], pch = 16, cex = ptsz, 
       xlab = params[pairs[1,i]], ylab = params[pairs[2,i]], xaxt = "n", yaxt = "n", bty = "n",
       col = colsg[round(selectfinsims[,pairs[3,i]]*100)+1])
  title(main = paste("Colour -", params[pairs[3,i]]))
  
  axis(1)
  axis(2)
  
  if (i == 2)
  {
    l = length(colsg);
    image(z=t(as.matrix(1:l)), col= colsg, xlab='', ylab='', xaxt='n', yaxt='n')
    axis(2, cex.axis=5, las=2, at=c(0,1/2,1),  labels= c(0,1/2,1))
  }
}
dev.off()


# ------------------------------------------------------------------
# 6. Output value histograms - Figure 3

pdf(paste("figures/outputhist_",dateuse,".pdf",sep=""), width = 7.5, height = 4)
par(mfrow=c(2,3), oma=c(0,0,0,0),mar=c(4,4,2,3),cex.lab = 1.3)
for (i in c(fionum + 2 + 2:6))
{
  hist(selectfinsims[,i], main="", xlab = params[i], xlim=c(mins[i],maxs[i]), breaks = 20) 
}
dev.off()

# ------------------------------------------------------------------
# 7. Correlations of outcomes and parameters

usecols = c(1:(fionum+2), fionum+2+2:6)

df = data.frame(round(cor(selectfinsims[,usecols], use="complete.obs"),3))

# remove all repeats
for (i in 1:nrow(df))
{
  df[i,i:ncol(df)] = ""; 
}

colnames(df) <- params[usecols]
rownames(df) <- params[usecols]
write.csv(df, paste("figures/correlation_allpairs_",dateuse,".csv", sep=""),row.names=T)  
rcorr(as.matrix(selectfinsims[,usecols]), type = "pearson")
