setwd("C:/Projects/CS Material And Snippets/Learn Statistics + R/Statistics Course/Assignment2")
rm(list = ls())
library(car)


df <- read.csv("triglycerides.csv")

hist(df$CHD)

hist(df$control)

boxplot(df, ylab = "Total Triglycerides Count")

#stack data into 1 feature vector and one group vector
df_flat <- data.frame(stack(df))

df_flat <- na.omit(df_flat) #omit NaNs

h_levene <- leveneTest(values ~ ind, data = df_flat)

means <- aggregate(values ~ ind, df_flat, mean)

df_flat$shifted <- 0
df_flat$shifted[df_flat$ind == "CHD"] <- df_flat$values[df_flat$ind == "CHD"] - means$values[means$ind == "CHD"]
df_flat$shifted[df_flat$ind == "control"] <- df_flat$values[df_flat$ind == "control"] - means$values[means$ind == "control"]

hist(
  df_flat$shifted,
  breaks = 10,
  xlab = bquote('y-' * bar(y) * ' (Triglycerides Count)'),
  ylab = 'Frequency',
  main = "Mutual Distribution"
)

# normality shepiro-wilk test
h_shapiro <- shapiro.test(df_flat$shifted)
# pv > 0.05 -> accept normality assumption of mutual distribution

h_ttest <- t.test(
  values ~ ind,
  data = df_flat,
  var.equal = TRUE,
  paired = FALSE,
  alternative = "greater"
)
q1h0 <- h_ttest['p.value'] > 0.05

# Q2
df_flat$normal <- df_flat$values <= 170
# categorization of data into contingency table
cont_table <- data.frame(
  row.names = c('NORMAL LEVEL COUNT', 'HIGH LEVEL COUNT'),
  "CHD" = c(
    length(df_flat$normal[df_flat$ind == 'CHD' & df_flat$normal == TRUE]),
    length(df_flat$normal[df_flat$ind == 'CHD' & df_flat$normal == FALSE])
  ),

  "control" = c(
    length(df_flat$normal[df_flat$ind == 'control' & df_flat$normal == TRUE]),
    length(df_flat$normal[df_flat$ind == 'control' & df_flat$normal == FALSE])
  )
)

# H0: CHD/control <====>  LEVEL
# H1: CHD/control <=//=>  LEVEL
h_fisher <- fisher.test(cont_table, conf.level = 0.95)
q2h0_fisher <- (h_fisher['p.value'] > 0.05)


# Alternative: (worse here since small sample sizes)
expected_table <- data.frame()
for (i in seq_len(nrow(cont_table))) {
  for (j in seq_len(ncol(cont_table))) {
    expected_table[i, j] <- sum(cont_table[i,]) * sum(cont_table[, j]) / sum(cont_table)
  }
}

# Calculate the cell chi2 and total chi2
x2 <- (expected_table - cont_table)^2 / expected_table
x2_total <- sum(x2)
df <- (2 - 1) * (2 - 1)
x2_crit <- qchisq(0.95, df = df)
x2pv <- pchisq(x2_total, df = df, lower.tail = T)

# H0: D(CHD)=D(control)
# H1: D(CHD)!=D(control)
h_chisq <- chisq.test(cont_table)

q2h0_chisq <- x2_crit > x2_total
q2h0_chisq_alt <- h_chisq['p.value'] > 0.05
q2h0_chisq_alt2 <- x2pv > 0.05

################## CLEAN UP ##################

CLEAN_UP <- F # change this to toggle cleanup

if (CLEAN_UP) {
  # Clear environment
  rm(list = ls())

  # Clear packages
  # detach("package:datasets", unload = TRUE)  # For base

  # Clear plots
  dev.off()  # But only if there IS a plot

  # Clear console
  cat("\014")  # ctrl+L

  # Clear mind :)
}