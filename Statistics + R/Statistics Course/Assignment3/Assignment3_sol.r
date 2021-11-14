setwd("C:/Projects/Statistics/Assignments/Assignment3")
rm(list = ls())
library(itertools)
library(car)

df <- read.csv("ArmyBodyweight.csv")
df$diffrence <- df$after - df$before
n_airforce <- length(df$force[df$force == "airforce"])
n_infantry <- length(df$force[df$force == "infantry"])
n_intlligence <- length(df$force[df$force == "intlligence"])
n_navy <- length(df$force[df$force == "navy"])
N <- nrow(df)

before_means <- aggregate(before ~ force, data = df, mean)
after_means <- aggregate(after ~ force, data = df, mean)
diff_means <- aggregate(diffrence ~ force, data = df, mean)

df$diff_shifted <- 0
df$diff_shifted[df$force == "airforce"] <- df$diffrence[df$force == "airforce"] - diff_means$diffrence[diff_means$force == "airforce"]
df$diff_shifted[df$force == "infantry"] <- df$diffrence[df$force == "infantry"] - diff_means$diffrence[diff_means$force == "infantry"]
df$diff_shifted[df$force == "intlligence"] <- df$diffrence[df$force == "intlligence"] - diff_means$diffrence[diff_means$force == "intlligence"]
df$diff_shifted[df$force == "navy"] <- df$diffrence[df$force == "navy"] - diff_means$diffrence[diff_means$force == "navy"]

h_shapiro <- shapiro.test(df$diff_shifted)

h_levene <- leveneTest(diffrence ~ force, df)

# H0: mu_airforce = mu_infantry = mu_intlligence = mu_navy
# H1: otherwise

anova_model <- aov(diffrence ~ force, data = df)
summary(anova_model)
h_anova <- summary(anova_model)[[1]]
print(paste("Can reject H0 and decide means are equal: ", h_anova["Pr(>F)"] < 0.05))


pairwise_comparisons <- data.frame(
  row.names = c(
    "airforce-infantry",
    "airforce-intlligence",
    "airforce-navy",
    "infantry-intlligence",
    "infantry-navy",
    "intlligence-navy"
  )
)

h_contrasts <- pairwise.t.test(df$diffrence, df$force)
pairwise_pvs <- h_contrasts$p.value
Paired_pv <- data.frame("Pv" = c(pairwise_pvs[1, 1], pairwise_pvs[2, 1], pairwise_pvs[3, 1], pairwise_pvs[2, 2], pairwise_pvs[3, 2], pairwise_pvs[3, 3]))
row.names(Paired_pv) <- c(
  "airforce-infantry",
  "airforce-intlligence",
  "airforce-navy",
  "infantry-intlligence",
  "infantry-navy",
  "intlligence-navy"
)

m <- length(Paired_pv$Pv)

Paired_pv$Bonferroni_CV <- 0.05 / m
for (r in rownames(Paired_pv)) {
  Paired_pv[r, "Bonferroni_H"] <- Paired_pv[r, "Pv"] < Paired_pv[r, "Bonferroni_CV"]
}

Paired_pv <-  Paired_pv[order(Paired_pv$Pv),]

for (i in 1:m) {
  Paired_pv[i, "HOLMES_CV"] <- 0.05 / (m + 1 - i)
  Paired_pv[i, "HOLMES_H"] <- Paired_pv[rownames(Paired_pv)[i], "Pv"] < Paired_pv[rownames(Paired_pv)[i], "HOLMES_CV"]
}

for (i in 1:m) {
  Paired_pv[i, "BH_CV"] <- 0.05 * i / m
  Paired_pv[i, "BH_H"] <- Paired_pv[rownames(Paired_pv)[i], "Pv"] < Paired_pv[rownames(Paired_pv)[i], "BH_CV"]
}

h_Tukey <- TukeyHSD(anova_model)$force
