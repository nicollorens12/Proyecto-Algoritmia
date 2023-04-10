# Load required libraries
#install.packages("ggplot2")
#install.packages("dplyr")
library(ggplot2)
library(dplyr)

# Read the data from CSV file
data <- read.csv("Data_LT.csv")

# 1. Compare the execution time for different graph datasets at different values of R
p1 <- ggplot(data, aes(x = R, y = Execution.time, group = Graph, color = Graph)) +
  geom_line() +
  labs(title = "Execution Time for Different Graph Datasets at Different R Values",
       x = "R Value",
       y = "Execution Time (seconds)") +
  theme_minimal()

# 2. Examine the relationship between graph size and execution time
p2 <- ggplot(data, aes(x = Size, y = Execution.time, color = as.factor(R))) +
  geom_point() +
  labs(title = "Relationship between Graph Size and Execution Time",
       x = "Graph Size",
       y = "Execution Time (seconds)",
       color = "R Value") +
  theme_minimal()

# 3. Analyze the distribution of execution times across graph datasets
p3 <- ggplot(data, aes(x = Graph, y = Execution.time, fill = Graph)) +
  geom_boxplot() +
  labs(title = "Distribution of Execution Times across Graph Datasets",
       x = "Graph Dataset",
       y = "Execution Time (seconds)") +
  theme_minimal() +
  theme(axis.text.x = element_text(angle = 90, hjust = 1, vjust = 0.5))

# 4. Compare the execution times at a specific value of R (e.g., R = 5) across all graph datasets
specific_r_value <- 5
data_specific_r <- data %>% filter(R == specific_r_value)

p4 <- ggplot(data_specific_r, aes(x = Graph, y = Execution.time, fill = Graph)) +
  geom_bar(stat = "identity") +
  labs(title = paste("Execution Times at R =", specific_r_value, "across All Graph Datasets"),
       x = "Graph Dataset",
       y = "Execution Time (seconds)") +
  theme_minimal() +
  theme(axis.text.x = element_text(angle = 90, hjust = 1, vjust = 0.5))

# Display the plots
p1
p2
p3
p4

# Compare the execution time for different graph datasets at different values of R (Faceted)
p1_faceted <- ggplot(data, aes(x = R, y = Execution.time, group = Graph, color = Graph)) +
  geom_line() +
  labs(title = "Execution Time for Different Graph Datasets at Different R Values",
       x = "R Value",
       y = "Execution Time (seconds)") +
  theme_minimal() +
  facet_wrap(~ Graph, ncol = 4) # Adjust 'ncol' to change the number of columns in the grid

# Display the faceted plot
p1_faceted
