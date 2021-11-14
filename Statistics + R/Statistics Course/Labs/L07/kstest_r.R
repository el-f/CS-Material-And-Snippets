'this tutorial practices kolmogorov-smirnov test'

setwd("C:/Projects/Statistics/L07")
rm(list = ls())

# load data and show distributions
df <- read.csv("k-s_data.csv", header = TRUE)
hist(df$groupA, breaks = 8)
hist(df$groupB, breaks = 8)
# construct cdf table of the two groups
# compose x spanning vector acording to data limits
x <- seq(round(0.8 * min(df)), 100, length = round(length(df$groupA) / 3))
x
# initiate a dataframe for the calculation of CDFs of the two groups and their distances (D)
cdfs <- data.frame("x" = x,
                   "cdf_A" = numeric(length(x)),
                   "cdf_B" = numeric(length(x)),
                   "D" = numeric(length(x)))
# loop over X bin by bin and calculate CDFs of groupA and groupB values
for (i in seq(seq_along(x))) {
  # CDF is the number of elements that are equal or smaller than x[i] normalized by the entire sample size
  cdfs[i, "cdf_A"] <- length(df$groupA[df$groupA <= x[i]]) / length(df$groupA)
  cdfs[i, "cdf_B"] <- length(df$groupB[df$groupB <= x[i]]) / length(df$groupB)
  # D vector is the bin-differences between groups in absolute value
  cdfs[i, "D"] <- abs(cdfs[i, "cdf_A"] - cdfs[i, "cdf_B"])
}
# calculate maximal D from cdfs["D"] 
# D_max is the desired statistical estimate of the K-S test
D_max <- max(cdfs["D"])

h <- ks.test(df$groupA, df$groupB)
print(paste('D_max from ks.test()=', h$statistic))
print(paste("D_max from man calc=", D_max))

jpeg("KS_CDF.jpg")
par(mar = c(5, 5.5, 3, 6))
plot(x, cdfs$cdf_A, col = 'black', type = "l", lwd = 2,
     cex.lab = 2, ylim = c(0, 1.05), ylab = "", cex.axis = 1.5)
par(new = TRUE)
plot(x, cdfs$cdf_B, col = 'red', type = "l", lwd = 2,
     ylim = c(0, 1.05), ylab = "",
     cex.lab = 2, cex.axis = 1.5)
par(new = TRUE)
plot(x, cdfs$D, col = 'blue', type = "l", lwd = 2,
     ylim = c(0, 1.05), ylab = "CDF",
     cex.lab = 2, cex.axis = 1.5)
legend("topleft",
       c("groupA", "groupB", "D"),
       col = c("black", "red", "blue"), lty = 1:1, lwd = 2, cex = 1.5)
dev.off()