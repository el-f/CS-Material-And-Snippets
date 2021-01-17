setwd("C:/Projects/Statistics/L3")
rm(list = ls())
library(mlbench)
# list the contents of the library
library(help = "mlbench")
data(Ozone)
# slice only month (V1) and Ozone (V4) columns
y = Ozone[, c("V1", "V4")]
# turn all variables to numeric
y$V1 = as.numeric(y$V1)
# clean Nans
summary(y)
y = na.omit(y)
#plot a histogram of the Ozone
hist(y$V4)
# choose only June rows and assign them in a new dataframe
y_summer = y[y$V1 == 6,]$V4
# plot histogram with 8 bins
x = seq(min(y_summer), max(y_summer), length = 8)
hist(y_summer, breaks = x)

# hypothesized mu0 for june is 15
mu0 = 15
# extract sample size
n = length(y_summer)
# calculate sample standard deviation
sample_sd = sd(y_summer)
# calculate sample mean
sample_mean = mean(y_summer)
# print them out
print(paste("sample sd=", round(sample_sd, 2)))
print(paste("sample Mean=", round(sample_mean, 2)))

# calcualte t-statistic of the sample mean around the population mean
# calculate the p-value associated with this t-statistic
alpha = .05
h = t.test(x = y_summer, mu = mu0, conf.level = 0.95)
help(t.test)
t = sqrt(n) * (sample_mean - mu0) / sample_sd
pv = 2 * pt(abs(t), df = n - 1, lower.tail = F)
print(paste("t-statistic = ", round(h$statistic, 2), round(t, 2)))
print(paste("p-value = ", round(h$p.value, 3), round(pv, 3)))

# build confidence interval
tc = qt(0.975, df = n - 1)
ci_up = sample_mean + tc * sample_sd / sqrt(n)
ci_low = sample_mean - tc * sample_sd / sqrt(n)
H1 = mu0 > ci_up | mu0 < ci_low
print(paste("reject H0:", H1))
tstat = abs(mu0 - sample_mean) * sqrt(n) / sample_sd
# 2-sided Pvalue calculation for t test 
pv = 2 * pt(tstat, df = n - 1, lower.tail = F)
# critical t value for t-test hypothesis testinng
tc = qt(1 - alpha / 2, df = n - 1)
# hypothesis testing result
print(paste("H1=", tstat > tc, pv < alpha))
