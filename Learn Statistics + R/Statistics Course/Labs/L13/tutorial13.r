# Multiple hypothesis testing ANOVA
setwd("D:/afeka_st/targil13/")
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

# test equality of means with levene test
levene_h <- leveneTest(vals ~ ind, data = df)

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
print(paste("ANOVA Pvalue=", round(pv, 5), " H0 can be rejected: ", pv < .05))

# Manual Pairwise comparison of means:
# Using Tukey studentized distribution:
# manual calculation q: q_i_j = (yi_M-yj_M)/sqrt(0.5*mse*((1/ni)+(1/nj)))
# Using contrast t-test distribution:
# manual calculation t: t_i_j = (yi_M-yj_M)/sqrt(mse*((1/ni)+(1/nj)))
# create an empty dataframe
pairwise_comparisons <- data.frame(row.names = c("Russia-China", "USA-China", "USA-Russia"))
# fill it in entry by entry:
# USA-Russia - Tukey studentized 
pairwise_comparisons["USA-Russia", "q"] <-
  (means$vals[means$ind == "Russia"] - means$vals[means$ind == "USA"]) / sqrt(0.5 * ms_err * (1 / n_Russia + 1 / n_USA))
pairwise_comparisons["USA-Russia", "p_q"] <-
  ptukey(pairwise_comparisons["USA-Russia", "q"], nmeans = 3, df = n - k, lower.tail = F)
# statistical inference:
print(paste("USA-Russia means are different: ",
            pairwise_comparisons["USA-Russia", "p_q"] < 0.05))
# USA-Russia - contrast t:
pairwise_comparisons["USA-Russia", "t"] <-
  (means$vals[means$ind == "Russia"] - means$vals[means$ind == "USA"]) / sqrt(ms_err * (1 / n_Russia + 1 / n_USA))
pairwise_comparisons["USA-Russia", "p_t"] <-
  2 * pt(pairwise_comparisons["USA-Russia", "t"], df = n - k, lower.tail = F)

# USA-China - Tukey studentized 
pairwise_comparisons["USA-China", "q"] <-
  (means$vals[means$ind == "China"] - means$vals[means$ind == "USA"]) / sqrt(0.5 * ms_err * (1 / n_China + 1 / n_USA))
pairwise_comparisons["USA-China", "p_q"] <-
  ptukey(pairwise_comparisons["USA-China", "q"], nmeans = 3, df = n - k, lower.tail = F)
# statistical inference:
print(paste("USA-China means are different: ", pairwise_comparisons["USA-China", "p_q"] < 0.05))
# USA-China - contrast t:
pairwise_comparisons["USA-China", "t"] <-
  (means$vals[means$ind == "China"] - means$vals[means$ind == "USA"]) / sqrt(ms_err * (1 / n_China + 1 / n_USA))
pairwise_comparisons["USA-China", "p_t"] <-
  2 * pt(pairwise_comparisons["USA-China", "t"], df = n - k, lower.tail = F)

# Russia-China - Tukey Studentized:
pairwise_comparisons["Russia-China", "q"] <-
  (means$vals[means$ind == "China"] - means$vals[means$ind == "Russia"]) / sqrt(0.5 * ms_err * (1 / n_China + 1 / n_Russia))
pairwise_comparisons["Russia-China", "p_q"] <-
  ptukey(pairwise_comparisons["Russia-China", "q"], nmeans = 3, df = n - k, lower.tail = F)
# statistical inference:
print(paste("Russia-China means are different: ", pairwise_comparisons["Russia-China", "p_q"] < 0.05))
# Russia-China - contrast t:
pairwise_comparisons["Russia-China", "t"] <-
  (means$vals[means$ind == "China"] - means$vals[means$ind == "Russia"]) / sqrt(ms_err * (1 / n_China + 1 / n_Russia))
pairwise_comparisons["Russia-China", "p_t"] <-
  2 * pt(pairwise_comparisons["Russia-China", "t"], df = n - k, lower.tail = F)

# built-in Tukey-HSD algo:
pairwise_comparisons_TukeyHSD <- TukeyHSD(anova_model)$ind

# Built-in pairwise comparisons using contrast-t-test
h_contrasts <- pairwise.t.test(df$vals, df$ind, p.adj = "none")
pairwise_pvs <- h_contrasts$p.value
Paired_pv <- data.frame("Pv" = c(pairwise_pvs[1, 1], pairwise_pvs[2, 1], pairwise_pvs[2, 2]))
row.names(Paired_pv) <- c("Russia-China", "USA-China", "USA-Russia")
# You can perform Bonferroni, Holm and BH corrections
# on the contrast-t p-values to control the FWER/FDR
# conclude accordinly
