# File:   01_InstallingR.R
# Course: R: An Introduction (with RStudio)

setwd("C:/Projects/CS Material And Snippets/Learn R/Tutorial")

# LOAD DATA ################################################

library(datasets)  # Load built-in datasets

# SUMMARIZE DATA ###########################################

head(iris)         # Show the first six lines of iris data
summary(iris)      # Summary statistics for iris data
plot(iris)         # Scatterplot matrix for iris data

# CLEAN UP #################################################

# Clear packages
detach("package:datasets", unload = TRUE)  # For base

# Clear plots
# dev.off()  # But only if there IS a plot
