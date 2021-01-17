# Multiple hypothesis testing ANOVA
setwd("C:/Projects/Statistics/L12")
rm(list = ls())
library("car")

df <- read.csv("MultiWeightliftingScores.csv")
jpeg("anova_boxplot.jpg")
boxplot(vals ~ ind, data = df, cex.axis = 1.5, cex.lab = 2, cex.main = 2)
dev.off()

# test mutual normality
means <- aggregate(vals ~ ind, df, mean)
n_USA <- length(df$vals[df$ind == 'USA'])
n_Russia <- length(df$vals[df$ind == 'Russia'])
n_China <- length(df$vals[df$ind == 'China'])
sds <- aggregate(vals ~ ind, df, sd)
df["vals_shifted"] <- 0
df$vals_shifted[df$ind == 'USA'] <-
  df$vals[df$ind == 'USA'] - means$vals[means$ind == 'USA']
df$vals_shifted[df$ind == 'Russia'] <-
  df$vals[df$ind == 'Russia'] - means$vals[means$ind == 'Russia']
df$vals_shifted[df$ind == 'China'] <-
  df$vals[df$ind == 'China'] - means$vals[means$ind == 'China']

# test mutual distribution's normality
shapiro_h <- shapiro.test(df$vals_shifted)


# NEED TO TEST LEVENE AS WELL
h_levene <- leveneTest(vals ~ ind, data = df)


# building an F statistic
k <- 3
n <- length(df$vals) # n is the size of the entire dataset
df1 <- k - 1  # where k is the amount of groups.
df2 <- n - k

# ms_bw
# sum(ni*(yi_bar-y_bar_bar)^2)/k-1
y_bar_total <- mean(df$vals)
ms_bw <- sum(n_Russia * (means$vals[means$ind == 'Russia'] - y_bar_total)^2 +
               n_USA * (means$vals[means$ind == 'USA'] - y_bar_total)^2 +
               n_China * (means$vals[means$ind == 'China'] - y_bar_total)^2) / df1

# ms_err
# sum(sum((yij-mean_yi)^2)/n-k
ms_err <- (sum((df$vals[df$ind == 'Russia'] - means$vals[means$ind == 'Russia'])^2) +
  sum((df$vals[df$ind == 'USA'] - means$vals[means$ind == 'USA'])^2) +
  sum((df$vals[df$ind == 'China'] - means$vals[means$ind == 'China'])^2)) / df2

# calculate f statistic
# f = ms_bw/ms_err
f <- ms_bw / ms_err

# calculate Pvalue associated with the F statistic
pv <- pf(f, df1 = df1, df2 = df2, lower.tail = F)

# perform ANOVA test using r function
anova_model <- aov(vals ~ ind, data = df)
h_anova <- summary(anova_model)[[1]]

# statistical inference:
print(paste("Pvalue=", round(pv, 5), " H0 can be rejected: ", pv < .05))

pairwise_comparisons_1 <- TukeyHSD(anova_model)$ind
