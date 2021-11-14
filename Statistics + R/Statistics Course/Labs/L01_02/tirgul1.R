setwd("C:/Projects/Statistics/L01_02")
rm(list = ls())
library(ggplot2)
library(tidyr)
library(data.table)

df <- read.csv("L1_2/iris.csv")

y <- df$sepal_width

mm <- mean(y)
m_calc <- sum(y) / length(y)
m_bool <- mm == m_calc


s <- round(sd(y), 4)
ss <- sd(y)
s_calc <- round(sqrt((1 / (length(y) - 1)) * sum((y - mean(y))^2)), 4)
serr <- round(s_calc / sqrt(length(y)), 4)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

n <- 10
x <- seq(0, n, 1) # 0:n

bp <- dbinom(x, 10, 0.3)
#barplot(bp)

jpeg("L1/binom_dist.jpg")  #  Annotation?
names(bp) <- x
par(mar = c(5, 5, 1.5, 6))
barplot(
  bp,
  main = "Binomic Distribution",
  xlab = "number of success",
  ylab = "probabilty (%)"
)
# save to file, don't show
dev.off()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

x <- 3
p <- 0.4
q <- 1 - p
p_x_binom <- (factorial(n) / (factorial(x) * factorial(n - x))) *
  p^x *
  q^(n - x)
mu <- n * p
std <- sqrt(n * p * q)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

x <- seq(0, 15, 1)
lambda <- 3
y <- dpois(x, lambda = lambda)
barplot(
  y,
  main = "pois Distribution",
  xlab = "number of success",
  ylab = "probabilty (%)"
)
dev.off()
i <- 5
p_x_pois <- (exp(-lambda) * (lambda^i)) / factorial(i)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

y <- df$petal_width
h <- hist(y)
petal_mean <- mean(y)
petal_sd <- sd(y)
x <- seq(0, max(y), length = 25)
a <- hist(y, breaks = x, main = "Petal width dist", xlab = "petal witdh (cm)",
          ylab = "frequency (#)")
legend("topright",
       c(sprintf("Mean=%3.2f", petal_mean),
         sprintf("std=%3.2f", petal_sd)
       ),
       col = "black", cex = 1.5, box.lwd = 0, bty = 'n'
)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

boxplot(df$sepal_width, df$petal_width,
        names = c("sepal width", "petal width"), cex.axis = 2)
summary(df$sepal_width)
