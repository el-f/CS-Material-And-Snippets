# weight of egg - X ~ N(u, 14^2)
# H0 - u = 40
# H1 - u > 40

mean <- 43.5
n <- 15
u0 <- 40
alpha <- 0.04

# A
z_1_minus_alpha <- qnorm(1 - alpha)

sigma_over_sqrt_n <- 14 / sqrt(n)

C <- u0 + z_1_minus_alpha * sigma_over_sqrt_n

is_H0 <- mean < C

# B

pv <- dnorm(mean)