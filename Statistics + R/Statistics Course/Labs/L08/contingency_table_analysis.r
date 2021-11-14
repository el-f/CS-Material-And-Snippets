'this tutorial practices analysis of contigency tables by ch2/fisher exact test'

setwd("C:/Projects/Statistics/L08")
rm(list = ls())
# init data from question in a table format
df <- data.frame(Israel = c(45, 15), Abroad = c(31, 17), row.names = c("won", "lost"))
'hypothesis testing statement:'
H0 <- "the probability of winning is independent of field location"
H1 <- "the probability of winning is different between home/abroad fileds"


# calculate expected frequencies 
df_expected <- data.frame()
for (i in seq_len(nrow(df))) {
  for (j in seq_len(ncol(df))) {
    df_expected[i, j] <- sum(df[i,]) * sum(df[, j]) / sum(df)
  }
}

# Calculate the cell chi2 and total chi2
x2 <- (df_expected - df)^2 / df_expected
x2_tot <- sum(x2)
# calculate pvalue for the total chi2 calculated
pv <- pchisq(x2_tot, df = 1, lower.tail = F)

# calculate critical chi2 value at 5% significance level
x2_c <- qchisq(.95, df = 1)
# state conclusion based on probability:
H0_bool <- pv > .05
print(paste("according to Pv, at 5% significance, accept H0 = ", H0_bool))

# state conclusion based on chi2 value:
H0_bool <- x2_tot < x2_c
print(paste("according to table chi2, accept H0 = ", H0_bool))
if (H0_bool == T) {
  print(H0)
} else {
  print(H1)
}

# alternative non-parametric test for any 2X2 contingency table:
h <- fisher.test(df, conf.level = 0.95)

