# this tutorial reviews the Wilcoxon-rank-sum test 
# for comparison between distribution expectation values of two unpaired groups 
# Eventually, we will compare its performance to unpaired t-test

setwd("C:/Projects/Statistics/L10")
rm(list = ls())
# load data from 'weightliftingScores.csv' file
df <- read.csv("weightliftingScores.csv")

# view data in boxplots
boxplot(df, ylab = "total weight (kg)")
# no outliers

# stack data into one feature vector and one group vector
df_flat <- data.frame(stack(df))

# omit nan rows
df_flat <- na.omit(df_flat)

# create mutual distribution
# find group means
means <- aggregate(values ~ ind, df_flat, mean)
# create additional column for mutual distribution of both groups
df_flat$shifted <- 0
# subtract mean of each group from values respectively
df_flat$shifted[df_flat$ind == "USA"] <- df_flat$values[df_flat$ind == "USA"] - means$values[means$ind == "USA"]
df_flat$shifted[df_flat$ind == "Russia"] <- df_flat$values[df_flat$ind == "Russia"] - means$values[means$ind == "Russia"]
# display histogram for normality checking "by eye"
hist(df_flat$shifted, breaks = 15)
# perform shapiro-wilk test for statistical validation of normality of mutual distribution
h_shapiro <- shapiro.test(df_flat$shifted)
# shapiro's pv<0.05 therefor reject normality assumption of mutual distribution

# build Wilcoxon rank-sum test:
# H0: D_USA = D_Russia
# H1: D_Russia<D_USA   # the russian rank distribution is shifted to the left of USA rank distribution
# rank all observations, mean if equal
df_flat$g_ranks <- length(df_flat$values) - rank(df_flat$values, ties.method = "average") + 1
# sum ranks by group
ranksums <- aggregate(g_ranks ~ ind, df_flat, sum)
# count sample size for each group (n1,n2)
ranksums$n <- c(length(df_flat$ind[df_flat$ind == "USA"]),
                length(df_flat$ind[df_flat$ind == "Russia"]))
# calculate rank expectation values for each group
ranksums$expectation <- (sum(ranksums$n) + 1) * ranksums$n / 2
# calculate mutual standard deviation
rank_sd <- sqrt(
  ranksums$n[1] *
    ranksums$n[2] *
    (sum(ranksums$n) + 1) / 12
)
# calculate statistical estimate of Wilcoxon test
z <- (ranksums$g_ranks[2] - ranksums$expectation[2]) / rank_sd
pv <- pnorm(z)
# pv < 0.05 therefor Russia's ranks are smaller (higher in olympic rank) than USA's
# in 95% confidence level
wilcoxon_h <- wilcox.test(values ~ ind, data = df_flat,
                          conf.level = 0.95, alternative = "less")
tteset_h <- t.test(values ~ ind, data = df_flat, conf.level = 0.95, alternative = "less")
# pv of ttest is greater than pv of wilcoxon
# this means it is easier to reject H0 with wilcoxon.
# wilcoxon is less conservative for non-parametric data

