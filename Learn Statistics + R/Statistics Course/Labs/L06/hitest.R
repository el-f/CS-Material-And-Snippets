setwd("C:/Projects/Statistics/L06")
rm(list = ls())
p_expected <-  c(0.5, 0.3, 0.18, 0.02)
observed <- c(115, 76, 45, 4)
h <- chisq.test(observed, p = p_expected)

expected <- 240 * p_expected
x2 <- sum((expected - observed)^2 / expected)

pv <- pchisq(x2, df = length(observed) - 1, lower.tail = FALSE) # df = h$paramater

print(paste("Pv(pchisq)=", round(pv, 4), ", Pv(chisq.test)=", round(h$p.value, 4)))
print(paste("x2(calc)=", round(x2, 3), ", x2(chisq.test)=", round(h$statistic, 3)))

p_obs <- observed / sum(observed)
print(paste("p(obs)=", round(p_obs, 4)))
print(paste("p(exp)=", round(p_expected, 4)))
