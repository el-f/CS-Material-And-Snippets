# File:   08_Summary.R
# Course: R: An Introduction (with RStudio)

setwd("C:/Projects/CS Material And Snippets/Learn R/Tutorial")

# INSTALL AND LOAD PACKAGES ################################

library(datasets)  # Load/unload base packages manually

# LOAD DATA ################################################

head(iris)

# SUMMARY() ################################################

summary(iris$Species)       # Categorical variable
summary(iris$Sepal.Length)  # Quantitative variable
summary(iris)               # Entire data frame

# CLEAN UP #################################################

# Clear packages
# detach("package:datasets", unload = TRUE)   # For base
#
# # Clear console
# cat("\014")  # ctrl+L

# Clear mind :)
