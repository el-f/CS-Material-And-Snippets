# Created by: Elazar Fine
# Created on: 9/12/2020

setwd("C:/Projects/CS Material And Snippets/Learn Statistics + R/Statistics Course/Assignment1")
rm(list = ls())
library(mlbench)
library(Rmisc)

################## 1 ##################

data(Ozone)
df <- (Ozone[, c("V1", "V7")])
df <- na.omit(df)
df$V1 <- as.numeric(df$V1)
df$V7 <- as.numeric(df$V7)
month <- df$V1
humidity <- df$V7

#1A
hist(
  humidity,
  breaks = 20,
  main = "LAX Humidity (%)",
  xlab = "Humidity (%)",
  xlim = c(0, 100),
  ylim = c(0, 60)
)

#1B
non_low_humidity <- humidity[humidity > min(humidity)] # min(humidity) = 19

hist(
  non_low_humidity,
  breaks = 20,
  main = "LAX Humidity (%)\n No low values",
  xlab = "Humidity (%)",
  xlim = c(0, 100),
  ylim = c(0, 60)
)

summer_humidity <- df[month >= 7 & month <= 9,]$V7
summer_humidity <- as.numeric(summer_humidity)

hist(
  summer_humidity,
  breaks = 10,
  main = "LAX Summer Humidity (%)\n (July - September)",
  xlab = "Humidity (%)",
  xlim = c(0, 100),
  ylim = c(0, 60)
)

sigma <- 7
mu0 <- 74
summer_mean <- round(mean(summer_humidity), 4)
summer_sd <- round(sd(summer_humidity), 4)
conf_level <- 0.95
alpha <- 1 - conf_level

z <- abs((summer_mean - mu0) / (sigma / sqrt(length(summer_humidity))))
pv <- 2 * (pnorm(z, lower.tail = F)) # two sided way

q1_h1 <- alpha > pv
if (q1_h1) {
  print("(Q1) H0 is rejected")
} else {
  print("(Q1) H0 is correct")
}

ci <- CI(summer_humidity, 1 - alpha / 2) # 1-alpha/2 = 0.975

mean_in_ci <- as.numeric(ci["lower"]) < summer_mean & summer_mean < as.numeric(ci["upper"])

################## 2 ##################

#2B
observed_litters <- table(c(
  rep.int(0, 8),           # 8 with 0 females
  rep.int(1, 27),          # 27 with 1 female
  rep.int(2, 20),          # 20 with 2 females
  rep.int(3, 25),          # 25 with 3 females
  rep.int(4, 10)           # 10 with 4 females
))

barplot(
  observed_litters,
  xlab = "# of females per litter",
  ylab = "# of litters",
  ylim = c(0, 30)
)

#2D
chisq_crit <- qchisq(0.95, df = 4)
chisq_obs <- 302 / 27
q2_pv <- pchisq(chisq_obs, df = 4, lower.tail = F)

q2_h1 <- chisq_obs > chisq_crit
q2_h1_alt <- .05 > q2_pv

if (q2_h1) {
  print("(Q2) H0 is rejected")
} else {
  print("(Q2) H0 is correct")
}


################## CLEAN UP ##################

CLEAN_UP <- F # change this to toggle cleanup

if (CLEAN_UP) {
  # Clear environment
  rm(list = ls())

  # Clear packages
  detach("package:datasets", unload = TRUE)  # For base

  # Clear plots
  dev.off()  # But only if there IS a plot

  # Clear console
  cat("\014")  # ctrl+L

  # Clear mind :)
}