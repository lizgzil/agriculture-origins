
setwd("/Users/lizgallagher/Code/agriculture-origins/analysis/The fast and the fit paper")

# The analysis here goes into S7 of the supplementary material

# ------------------------------------------------------------------

# L1. Import data for the low mobility simulations
# L2. For each simulation import the family data and pull out the fitness over time for each family
# L3. Find the interquartile range (or other spread measure of these fitnesses?)
# H1. Import data for the high mobility simulations
# H2. For each simulation import the family data and pull out the fitness over time for each family
# H3. Find the interquartile range (or other spread measure of these fitnesses?)
# 4. Compare the spread measures for high and low oscillations - histograms - Figure S8 and S9
# 5. Compare the spread measures for high and low oscillations - line plots - Figure S7
# 6. t test of IQR of high and low mobility simulations

# ------------------------------------------------------------------

# The data file for this is quite big, so I didn't want to copy it to my data folder, but kept it in it's original location

# Look at personal fitness over time in both very mobile and un mobile simulations.
# Low mobility sim: r = 0.92, lambda = 0.03, kappa = 100, eta = 0.03
# High mobility sim: r = 0.43, lambda = 0.7, kappa = 100, eta = 0.001

# low mobility foragingmodel17May2018_lowmoballinfo r = 0.66, lambda = 0.13, kappa = 100, eta = 0.04
# high mobility foragingmodel17May2018_highmoballinfo r = 0.53, lambda = 0.64, kappa = 100, eta = 0.01

# ------------------------------------------------------------------
# L1. Import data for the low mobility simulations

dateuse = "foragingmodel17May2018_lowmoballinfo";

exten = paste("/Users/lizgallagher/Library/Developer/Xcode/DerivedData/Farming_v6_1-dxzxlqmnzrrmgihferlkqzitcohz/Build/Products/Debug/",dateuse,sep ="");
details <- read.csv(paste(exten,"/Rdetails_",dateuse,".txt",sep = ""),sep = ",",header=T);
enddeets <- read.csv(paste(exten,"/endmeans_",dateuse,".txt",sep = ""),sep = ",",header=T);

numits = details$NUMITS
repeats = details$repeats

# ------------------------------------------------------------------
# L2. For each simulation import the family data and pull out the fitness over time for each family

numsampsims = 50;
numsampfamseach = 100;

simstolookat = sample(0:99,numsampsims);

mobsall = rep(NA,numits+2)
fitsall = rep(NA,numits+2)

counter = 1
for (s in simstolookat) # simulation number (0 to 99)
{
  thissim <- read.csv(paste(exten,"/families",s,"_",dateuse,".txt",sep = ""),sep = ",",header=T);
  
  # Only really want to study after the burn in period, but when is this?
  randfams = sample(thissim$famID,numsampfamseach)
  
  thissimmobs = rep(NA,numits+2)
  thissimfits = rep(NA,numits+2)
  for (f in randfams)
  {
    thisfam = thissim[which(thissim$famID == f),]
    
    thisfammobs = rep(NA,numits+2)
    thisfammobs[1] = s
    thisfammobs[2] = f
    thisfammobs[(thisfam$Iteration+1)+2] = thisfam$m_strat
    
    thisfamfits = rep(NA,numits+2)
    thisfamfits[1] = s
    thisfamfits[2] = f
    thisfamfits[(thisfam$Iteration+1)+2] = thisfam$fitness
    
    if (f ==randfams[1])
    {
      thissimmobs = thisfammobs
      thissimfits = thisfamfits
    } else
    {
      thissimmobs = rbind(thissimmobs,thisfammobs)
      thissimfits = rbind(thissimfits,thisfamfits)
    }
  }
  
  if (s ==simstolookat[1])
  {
    mobsall = thissimmobs
    fitsall = thissimfits
  } else
  {
    mobsall = rbind(mobsall,thissimmobs)
    fitsall = rbind(fitsall,thissimfits)
  }
  
  print(counter)
  counter  = counter+1
}

# ------------------------------------------------------------------
# L3. Find the interquartile range (or other spread measure of these fitnesses?)

startfromit = 1
iqralllow = rep(NA, nrow(mobsall))
minalllow = rep(NA, nrow(mobsall))
maxalllow = rep(NA, nrow(mobsall))
sdalllow = rep(NA, nrow(mobsall))
meanalllow = rep(NA, nrow(mobsall))
meamobnalllow = rep(NA, nrow(mobsall))

for (f in 1:nrow(mobsall))
{ 
  
  iqralllow[f] = IQR(fitsall[f,(startfromit+3):(numits+2)], na.rm = TRUE, type = 7)
  minalllow[f] = min(fitsall[f,(startfromit+3):(numits+2)],na.rm = TRUE)
  maxalllow[f] = max(fitsall[f,(startfromit+3):(numits+2)],na.rm = TRUE)
  sdalllow[f] = sd(fitsall[f,(startfromit+3):(numits+2)],na.rm = TRUE)
  meanalllow[f] = mean(fitsall[f,(startfromit+3):(numits+2)],na.rm = TRUE)
  meamobnalllow[f] = mean(mobsall[f,(startfromit+3):(numits+2)],na.rm = TRUE)
}

################ HIGH MOB

# ------------------------------------------------------------------
# H1. Import data for the high mobility simulations


dateuse = "foragingmodel17May2018_highmoballinfo";

exten = paste("/Users/lizgallagher/Library/Developer/Xcode/DerivedData/Farming_v6_1-dxzxlqmnzrrmgihferlkqzitcohz/Build/Products/Debug/",dateuse,sep="");
details <- read.csv(paste(exten,"/Rdetails_",dateuse,".txt",sep = ""),sep = ",",header=T);
enddeets <- read.csv(paste(exten,"/endmeans_",dateuse,".txt",sep = ""),sep = ",",header=T);

numits = details$NUMITS
repeats = details$repeats

mobsallhi = rep(NA,numits+2)
fitsallhi = rep(NA,numits+2)

# ------------------------------------------------------------------
# H2. For each simulation import the family data and pull out the fitness over time for each family

counter = 1
for (s in simstolookat) # simulation number (0 to 99)
{
  thissim <- read.csv(paste(exten,"/families",s,"_",dateuse,".txt",sep = ""),sep = ",",header=T);
  
  # Only really want to study after the burn in period, but when is this?
  randfams = sample(thissim$famID,numsampfamseach)
  
  thissimmobs = rep(NA,numits+2)
  thissimfits = rep(NA,numits+2)
  for (f in randfams)
  {
    thisfam = thissim[which(thissim$famID == f),]
    
    thisfammobs = rep(NA,numits+2)
    thisfammobs[1] = s
    thisfammobs[2] = f
    thisfammobs[(thisfam$Iteration+1)+2] = thisfam$m_strat
    
    thisfamfits = rep(NA,numits+2)
    thisfamfits[1] = s
    thisfamfits[2] = f
    thisfamfits[(thisfam$Iteration+1)+2] = thisfam$fitness
    
    if (f ==randfams[1])
    {
      thissimmobs = thisfammobs
      thissimfits = thisfamfits
    } else
    {
      thissimmobs = rbind(thissimmobs,thisfammobs)
      thissimfits = rbind(thissimfits,thisfamfits)
    }
  }
  
  if (s ==simstolookat[1])
  {
    mobsallhi = thissimmobs
    fitsallhi = thissimfits
  } else
  {
    mobsallhi = rbind(mobsallhi,thissimmobs)
    fitsallhi = rbind(fitsallhi,thissimfits)
  }
  
  print(counter)
  counter  = counter+1
}

# ------------------------------------------------------------------
# H3. Find the interquartile range (or other spread measure of these fitnesses?)

startfromit = 1
iqrallhigh = rep(NA, nrow(mobsallhi))
minallhigh = rep(NA, nrow(mobsallhi))
maxallhigh = rep(NA, nrow(mobsallhi))
sdallhigh = rep(NA, nrow(mobsallhi))
meanallhigh = rep(NA, nrow(mobsallhi))
meanmoballhigh = rep(NA, nrow(mobsallhi))

for (f in 1:nrow(mobsallhi))
{ 
  
  iqrallhigh[f] = IQR(fitsallhi[f,(startfromit+3):(numits+2)], na.rm = TRUE, type = 7)
  minallhigh[f] = min(fitsallhi[f,(startfromit+3):(numits+2)],na.rm = TRUE)
  maxallhigh[f] = max(fitsallhi[f,(startfromit+3):(numits+2)],na.rm = TRUE)
  sdallhigh[f] = sd(fitsallhi[f,(startfromit+3):(numits+2)],na.rm = TRUE)
  meanallhigh[f] = mean(fitsallhi[f,(startfromit+3):(numits+2)],na.rm = TRUE)
  meanmoballhigh[f] = mean(mobsallhi[f,(startfromit+3):(numits+2)],na.rm = TRUE)
}

# ------------------------------------------------------------------
# 4. Compare the spread measures for high and low oscillations - histograms - Figure S8 and S9


pdf(paste("figures/rangesovertimelow_",dateuse,".pdf",sep=""), width = 9, height = 2, bg = "white")
par(mfrow=c(1,3), cex.lab=1.5, mar = c(5,6,1,2), cex.axis= 1.2)
hist(iqralllow, xlab = "IQR of fitness",main = "", xlim = c(0,1),col ="grey")
hist(meanalllow, xlab = "Mean fitness",main = "", xlim = c(0,1),col ="grey")
hist(meanalllow, xlab = "Mean mobility strategy", xlim = c(0,1),main = "",col ="grey")
dev.off()


pdf(paste("figures/rangesovertimehigh_",dateuse,".pdf",sep=""), width = 9, height = 2, bg = "white")
par(mfrow=c(1,3), cex.lab=1.5, mar = c(5,6,1,2), cex.axis= 1.2)
hist(iqrallhigh, xlab = "IQR of fitness",main = "", xlim = c(0,1),col ="grey")
hist(meanallhigh, xlab = "Mean fitness",main = "", xlim = c(0,1),col ="grey")
hist(meanmoballhigh, xlab = "Mobility mobility strategy", xlim = c(0,1),main = "",col ="grey")
dev.off()


# ------------------------------------------------------------------
# 5. Compare the spread measures for high and low oscillations - line plots - Figure S7

# Colour fitness line by red (ended at >0.5 mob) or blue (ended at <=0.5 mob)

colseach = rainbow(20)

png(filename = paste("figures/fitness_overtime_lowsims_highsims_",dateuse,".png",sep=""), width = 2500, height = 1700, bg = "white")
par(mfrow = c(2,2), oma=c(2,0.5,0.5,0.5), mar = c(12,17,8,2), mgp =c(10,3,0), cex.lab = 7,cex.axis = 5)
plot(1,1,bty = "n",col="white",xlab="Iteration",ylab="Fitness",yaxt="n",xaxt="n", xlim = c(0,1000), ylim = c(0,1))
axis(1)
axis(2)
par(new = T)
for (f in 1:nrow(mobsall))
{
  tempfmpbs = mobsall[f,!is.na(mobsall[f,])]
  tempfmpbs = tempfmpbs[length(tempfmpbs)]
  
  colmob = rgb(tempfmpbs,0,1-tempfmpbs)
  
  plot(1:numits,fitsall[f,3:(numits+2)], type = 'l', xlim = c(0,1000), ylim = c(0,1),
       xaxt = "n", yaxt = "n", bty = "n",
       xlab = "",ylab = "",lwd = 0.1, col = colmob)
  par(new = T)
}
par(new = F)

plot(1,1,bty = "n",col="white",xlab="Iteration",ylab="Fitness",yaxt="n",xaxt="n", xlim = c(0,1000), ylim = c(0,1))
axis(1)
axis(2)
par(new = T)
ff=1
for (f in sample(nrow(mobsall),20))
{
  tempfmpbs = mobsall[f,!is.na(mobsall[f,])]
  tempfmpbs = tempfmpbs[length(tempfmpbs)]
  
  colmob = colseach[ff]
  
  plot(1:numits,fitsall[f,3:(numits+2)], type = 'l', xlim = c(0,1000), ylim = c(0,1),
       xaxt = "n", yaxt = "n", bty = "n",
       xlab = "",ylab = "",lwd = 2, col = colmob)
  par(new = T)
  ff=ff+1
}

# Colour fitness line by red (ended at >0.5 mob) or blue (ended at <=0.5 mob)
par(new = F)

plot(1,1,bty = "n",col="white",xlab="Iteration",ylab="Fitness",yaxt="n",xaxt="n", xlim = c(0,1000), ylim = c(0,1))
axis(1)
axis(2)
par(new = T)
for (f in 1:nrow(mobsallhi))
{
  tempfmpbs = mobsallhi[f,!is.na(mobsallhi[f,])]
  tempfmpbs = tempfmpbs[length(tempfmpbs)]
  
  colmob = rgb(tempfmpbs,0,1-tempfmpbs)
  
  plot(1:numits,fitsallhi[f,3:(numits+2)], type = 'l', xlim = c(0,1000), ylim = c(0,1),
       xaxt = "n", yaxt = "n", bty = "n",
       xlab = "",ylab = "",lwd = 0.1, col = colmob)
  par(new = T)
}

par(new = F)

plot(1,1,bty = "n",col="white",xlab="Iteration",ylab="Fitness",yaxt="n",xaxt="n", xlim = c(0,1000), ylim = c(0,1))
axis(1)
axis(2)
par(new = T)
ff=1
for (f in sample(nrow(mobsallhi),20))
{
  tempfmpbs = mobsallhi[f,!is.na(mobsallhi[f,])]
  tempfmpbs = tempfmpbs[length(tempfmpbs)]
  
  colmob = colseach[ff]
  
  plot(1:numits,fitsallhi[f,3:(numits+2)], type = 'l', xlim = c(0,1000), ylim = c(0,1),
       xaxt = "n", yaxt = "n", bty = "n",
       xlab = "",ylab = "",lwd = 2, col = colmob)
  par(new = T)
  ff=ff+1
}

dev.off()



# ------------------------------------------------------------------
# 6. t test of IQR of high and low mobility simulations


t.test(iqralllow,iqrallhigh)

# Welch Two Sample t-test
# data:  iqralllow and iqrallhigh
# t = -22.7183, df = 8662.343, p-value < 2.2e-16
# alternative hypothesis: true difference in means is not equal to 0
# 95 percent confidence interval:
#   -0.06998971 -0.05887105
# sample estimates:
#   mean of x mean of y 
# 0.1404010 0.2048314 