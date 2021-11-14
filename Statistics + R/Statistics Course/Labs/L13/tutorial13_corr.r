# Correlation
setwd("C:/Projects/Statistics/L13")
rm(list = ls())
library(mlbench)
# load data
data("Ozone")
# organize dataframe for analysis
y <- Ozone[, c("V4", "V5")]
y <- na.omit(y)
colnames(y) <- c("Ozone", "Pressure")
# print dataframe summary 
# this is equivalent to barplot and even better when means are very different
print(summary(y))

# present scatterplot of ozone as a function of pressure
jpeg("scatter.jpg")
par(mar = c(4.5, 5, 4, 3.5))
plot(y$Ozone, y$Pressure,
     xlab = "Ozone(F)", ylab = "Pressure(%)",
     cex.axis = 1.5, cex.lab = 2)
dev.off()
# calculate rij
means <- colMeans(y)
sds <- c(sd(y$Ozone), sd(y$Pressure))
y$Z_Ozone <- (y$Ozone - means[1]) / sds[1]
y$Z_Pressure <- (y$Pressure - means[2]) / sds[2]
y$R_Ozone_Pressure <- y$Z_Ozone * y$Z_Pressure

# derive r as mean of rij
R_Ozone_Pressure <- sum(y$R_Ozone_Pressure) / (nrow(y) - 1)

# 1st Solution for statistical estimate
r_star <- 0.5*log((1+R_Ozone_Pressure)/(1-R_Ozone_Pressure))
z <- r_star*sqrt(nrow(y)-3)
pv_Ozone_Pressure_alt <-  2*pnorm(z,lower.tail = F)

# 2nd Solution for statistical estimation - Correct form!
t <- R_Ozone_Pressure * sqrt(nrow(y) - 2) / sqrt(1 - R_Ozone_Pressure^2) #
pv_Ozone_Pressure <- 2 * pt(t, df = nrow(y) - 2, lower.tail = F)

# built-in R function for Pearson correlation: 
r_pearson <- cor.test(y$Ozone, y$Pressure, method = "pearson")

# Statistical inference:
print(paste("the correlation between Ozone and Pressure is significant: ", pv_Ozone_Pressure < 0.05))
