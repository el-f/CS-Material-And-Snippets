setwd("C:/Projects/Statistics/L03")
rm(list = ls())
library(ggplot2)
library(tidyr)


# pnorm -> get p from z
# qnorm -> get quantile from p

# 1.
mu <- 20
sdev <- 5
num <- 500
x <- rnorm(n = num, mean = mu, sd = sdev)
x_bar <- mean(x)
n_bins <- 25
x_span <- seq(0.9 * min(x), 1.1 * max(x), length = n_bins)
hist <- hist(x, breaks = x_span)
summary(x)
ci_high <- x_bar + qnorm(0.965) * sdev / sqrt(num)
ci_low <- x_bar - qnorm(0.965) * sdev / sqrt(num)
bool <- ci_low < x_bar && x_bar < ci_high

# 2.
mu1 <- 85
sdev1 <- 80
mu2 <- 275
sdev2 <- 120

x1 <- 93  # 18 months
x2 <- 287 # 24 months
z1 <- (x1 - mu1) / sdev1
z2 <- (x2 - mu2) / sdev2
b_z <- round(z1, 4) == round(z2, 4)
p1 <- pnorm(x1, mean = mu1, sd = sdev1) # pnorm = ingegral from -inf to x1 under expectation mu1
p2 <- pnorm(x2, mean = mu2, sd = sdev2)
b_p <- round(p1, 4) == round(p2, 4)

all_p <- p1
all_z <- z1
qnorm(all_p)
pnorm(all_z)
qnorm(0.95)


# 3.
t_c <- qt(.98, 15 - 1)
t95 <- qt(.95, 20 - 1)
t95_30 <- qt(.95, 30 - 1)
p <- pt(2.204, 20 - 1)

ci_high_2 <- 17.9 + qt(0.965, 500-1) * 5 / sqrt(500)
ci_low_2 <- 17.9 - qt(0.965, 499) * 5 / sqrt(500)


# BOXPLOT
df <- read.csv("L3/iris.csv")
boxplot(df$sepal_width, df$petal_width, names = c("speal_width", "petal_width"))
summary(df$sepal_width)

# 4.
cl <- .98
n <- 18
m <- 4.5

