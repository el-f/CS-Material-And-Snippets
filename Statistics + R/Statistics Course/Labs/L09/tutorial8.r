setwd("C:/Projects/Statistics/L09")
rm(list = ls())
library("car")

# paired t-test
# load&clean data
# test normality
# perform t-test
# load data& clean it
data <- read.csv("crab_breedings.csv")
data <- na.omit(data)
# look for outliers within groups
# observe the boxplot
boxplot(data[, c(2, 3)], ylab = "Breedings", main = "Anual crab breedings")
# discard outlier instances from the data
data <- data[abs(data$X2012 - mean(data$X2012)) < 3 * sd(data$X2012),] # based on X2012 column
data <- data[abs(data$X2011 - mean(data$X2011)) < 3 * sd(data$X2011),] # based on X2011 column

# mutual normality testing:
# creat paired difference column
data$diff <- data$X2012 - data$X2011
# show histogram
hist(data$diff, breaks = 10,
     xlab = 'x2012-x2011',
     main = "distribution of difference between groups")
# test normality using shapiro-wilk w test
shapiro_h <- shapiro.test(data$diff)
# since Pv=0.037 <.05 we cannot accept normality
# therefor conduct a non-parametric test to paired sample means
h_wilc_paired <- wilcox.test(data$X2011, data$X2012, conf.level = 0.95,
                            alternative = "two.sided")

# Important Note: 
# if data would have distributed normaly, 
# we would proceed to test equality of variances using leveneTest
# if Pv(leveneTest)>0.05, meaning equal variances,  
# then we would perform t.test 
# otherwise, we would perform Welch's test for normal distributions and unequal variances.

# UNPAIRED T-TEST
# load data from csv file, notice that each group has different column length
# re-organize pre-proccess data for further tests (cleaning+labeling)
# test normality of mutual distribution
# perform levene test for equality of variances
# under normal distribution assumption
# perform comparison of group means with t-test or Welch's test 

# data loading and pre-processing
data <- read.csv("cargas.csv")
# if data is not well organized as groups re-organize it
# turn all -999's to NaN's so that we can later remove them
data[data == -999] <-  NaN
# group/stack data by column category
data_flat <- data.frame(stack(data[1:2]))
# remove all NaN's
data_flat <- na.omit(data_flat)
# first observation of the data using boxplot 
# what is your intuition regarding the test hypothesis?
boxplot(values ~ ind, data = data_flat)

# test equality of variances using Levene test:
levene_h <- leveneTest(values ~ ind, data = data_flat)

##  test normality of mutual data:
# mutual distribution presentation
# center both groups around to distribute around 0 by subtracting their group means
means <- aggregate(values ~ ind, data_flat, mean)
sds <- aggregate(values ~ ind, data_flat, sd)
data_flat["vals_shifted"] <-  0
data_flat$vals_shifted[data_flat$ind == 'USA'] <-
  data_flat$values[data_flat$ind == 'USA'] - means$values[means$ind == 'USA']
data_flat$vals_shifted[data_flat$ind == 'Japan'] <-
  data_flat$values[data_flat$ind == 'Japan'] - means$values[means$ind == 'Japan']
# create mutual histogram to examine normality of distribution
# does the data distribute normaliy in your opinion?
hist(data_flat$vals_shifted, breaks = 10,
     xlab = bquote('y-' * bar(y) * ' (miles/galone)'),
     main = "mutual group distribution")

# test normality using shapiro-wilk w test:
# if Pv(Shapiro)>0.05 the data distributes normaly
shapiro_h <- shapiro.test(data_flat$vals_shifted)

## if variances are equal and mutual normality is validated, perform t-test
ttest_h <- t.test(values ~ ind, data = data_flat,
                 paired = FALSE, var.equal = TRUE,
                 conf.level = 0.95, alternative = "less")

### if variances are NOT equal, but normality is achieved, perform welch's anova test 
### for comparison of means in unpaired groups
welch_h <- oneway.test(values ~ ind, data = data_flat, var.equal = FALSE)
# alternatively, use t-test with unequal variances 
# in this test p-value is accurate by welch test, statistic estimate is not accurate
welch_h2 <- t.test(values ~ ind, data = data_flat,
                  paired = FALSE, var.equal = FALSE,
                  conf.level = 0.95, alternative = "less")

### if shapiro-wilk test failed to show normality, 
### use the non-parametric wilcoxon signed-test
wilcoxon_h <- wilcox.test(values ~ ind, data = data_flat,
                         conf.level = 0.95, alternative = "less")
# if Pv(wilcoxon)<0.05 we reject H0 and decide H1

# From comparison of means to binary comparison of distributions with chi2/Fisher tests
# Above or equal to 20 is considered economic car, 
# below 20 miles/galon is considered wasteful car.
# categorization of data into contingency table
data_flat$economy <-  data_flat$values >= 20
#table = xtabs(~ind+economy,data=data_flat)
cont_table <- data.frame(row.names = c(TRUE, FALSE),
                        "USA" = c(length(data_flat$economy[data_flat$ind == 'USA' & data_flat$economy == TRUE]),
                                  length(data_flat$economy[data_flat$ind == 'USA' & data_flat$economy == FALSE])),
                        "Japan" = c(length(data_flat$economy[data_flat$ind == 'Japan' & data_flat$economy == TRUE]),
                                    length(data_flat$economy[data_flat$ind == 'Japan' & data_flat$economy == FALSE])))
# H0: Pi(USA)=Pi(Japan)
# H1: Pi(USA)!=Pi(Japan)
# calculate P-expected
expected_table <- data.frame()
for (i in seq_len(nrow(cont_table))) {
  for (j in seq_len(ncol(cont_table))) {
    expected_table[i, j] <- sum(cont_table[i,]) * sum(cont_table[, j]) / sum(cont_table)
  }
}
# Calculate the cell chi2 and total chi2
x2 <- (expected_table - cont_table)^2 / expected_table
x2_tot <- sum(x2)

# calculate pvalue for the total chi2 calculated
pv <- pchisq(x2_tot, df = 1, lower.tail = F)
# or shortly, perform chi2 test:
h_chi2 <- chisq.test(cont_table)

# alternative non-parametric test for any 2X2 contingency table:
h_fisher <- fisher.test(cont_table, conf.level = 0.95)
# calculate the odd-ratio of the observed data:
p_observed <- data.frame()
for (i in seq_len(nrow(cont_table))) {
  for (j in seq_len(ncol(cont_table))) {
    p_observed[i, j] <- cont_table[i, j] / sum(cont_table[, j])
  }
}
OR <- p_observed[1, 1] * p_observed[2, 2] / (p_observed[1, 2] * p_observed[2, 1])
#Important notice: 
# compare the OR to the one calculated in Fisher
# observe the CI of the OR by Fisher