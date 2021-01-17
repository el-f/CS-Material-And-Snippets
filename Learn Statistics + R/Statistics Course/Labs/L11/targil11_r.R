# MULTIPLE COMPARISON ANALYSIS
setwd("C:/Projects/Statistics/L11")
rm(list = ls())
library(itertools)
# compare each city to critical distribution (%) 
# and decide if ill distribution is considered high risky or low risk
# where high risk is if % of ill is greater than the one in critical distribution

data <- read.csv("multipleTestingData.csv")

df_observed <- data[, 3:length(colnames(data))]
rownames(df_observed) <- data[, 1]
p_expected <- data[, 2]
results <- data.frame()
for (c in colnames(df_observed)) {
  df <- data.frame("expected" = p_expected, c = data[c])
  h_fisher <- fisher.test(df, alternative = "less")
  or <- as.numeric(h_fisher$estimate[1])
  pv <- as.numeric(h_fisher$p.value[1])
  results <- rbind(results, data.frame("Pv" = pv, row.names = c))
}
# control the FWER using bonferroni correction 
# to decide which hypothesis can be rejected
# significance level = alpha/m, alpha  = 0.05
m <- length(results$Pv)
results$Bonferroni_CV <- 0.05 / m
for (r in rownames(results)) {
  results[r, "Bonferroni_H"] <- results[r, "Pv"] < results[r, "Bonferroni_CV"]
}
# control the FWER using Holmes correction 
# to decide which hypothesis can be rejected
# significance level = alpha/(m+1-i), 
# alpha  = 0.05
# order results by ascending order
results <- results[order(results$Pv),]
# calculate Holmes criterion
for (i in 1:m) {
  results[i, "HOLMES_CV"] <- 0.05 / (m + 1 - i)
  results[i, "HOLMES_H"] <- results[rownames(results)[i], "Pv"] < results[rownames(results)[i], "HOLMES_CV"]
}

# control the FDR using B-H correction 
# to decide which hypothesis can be rejected
# significance level = alpha*i/m, 
# alpha  = 0.05
# order results by ascending order
# calculate B-H criterion
for (i in 1:m) {
  results[i, "BH_CV"] <- 0.05 * i / m
  results[i, "BH_H"] <- results[rownames(results)[i], "Pv"] < results[rownames(results)[i], "BH_CV"]
}
