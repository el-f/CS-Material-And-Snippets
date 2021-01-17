# Title     :
# Objective : Practice Kolmogorov-Smirnov Test
# Created by: Denis
# Created on: 04-Dec-20


setwd("C:/Users/Denis/Documents/Afeka Studies/Year 2 - Sem A/Statistics/Statistics/Practice6")
rm(list = ls())

# load data and show distributions
df <- read.csv("../k-s_data.csv", header = TRUE)
hist(df$groupA, breaks = 8) # show histogram of groupA
hist(df$groupB, breaks = 8) # show histogram of groupB

# construct cdf table of the two groups
# compose x spanning vector acording to data limits
grades <- seq(round(0.8 * min(df)), 100, length = round(length(df$groupA) / 3))

# initiate a dataframe for the calculation of CDFs of the two groups and their distances (D)

# data.frame - creates and array of colsSize = 4
# cdf - התפלגות מצטברת
cdfsArr <- data.frame("x" = grades,
                      "cdf_A" = numeric(length(grades)),
                      "cdf_B" = numeric(length(grades)),
                      "D" = numeric(length(grades)))

# loop over X bin by bin and calculate CDFs of groupA and groupB values
for (grade in seq(seq_along(grades))) {
  # CDF is the number of elements that are equal or smaller than grades[grade] normalized by the entire sample size
  cdfsArr[grade, "cdf_A"] <- length(df$groupA[df$groupA <= grades[grade]]) / length(df$groupA)
  cdfsArr[grade, "cdf_B"] <- length(df$groupB[df$groupB <= grades[grade]]) / length(df$groupB)
  # D vector is the bin-differences between groups in absolute value
  cdfsArr[grade, "D"] <- abs(cdfsArr[grade, "cdf_A"] - cdfsArr[grade, "cdf_B"])
}

# calculate maximal D from cdfs["D"]
# D_max is the desired statistical estimate of the K-S test
D_max <- max(cdfsArr["D"])

KS_Test <- ks.test(df$groupA, df$groupB)
print(paste('D_max from ks.test()=', KS_Test$statistic))
print(paste("D_max from man calc=", D_max))

# starting creation of an image
jpeg("KS_CDF.jpg")

par(mar = c(5, 5.5, 3, 6))
plot(grades,
     cdfsArr$cdf_A,
     col = 'black',
     type = "l",
     lwd = 2,
     cex.lab = 2,
     ylim = c(0, 1.05),
     ylab = "",
     cex.axis = 1.5)

par(new = TRUE) # draw on the same graph
plot(grades,
     cdfsArr$cdf_B,
     col = 'red',
     type = "l",
     lwd = 2,
     ylim = c(0, 1.05),
     ylab = "",
     cex.lab = 2,
     cex.axis = 1.5)

par(new = TRUE) # draw on the same graph
plot(grades,
     cdfsArr$D,
     col = 'blue',
     type = "l",
     lwd = 2,
     ylim = c(0, 1.05),
     ylab = "CDF",
     cex.lab = 2,
     cex.axis = 1.5)

# draw everything
legend("topleft",
       c("groupA", "groupB", "D"), # names
       col = c("black", "red", "blue"), # colorize each name
       lty = 1:1,
       lwd = 2,
       cex = 1.5)

# end creation of an image
dev.off()