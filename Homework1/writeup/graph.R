library(tidyverse)
library(ggthemes)
library(latex2exp)

data <- read_csv("problem2.csv") %>%
  mutate(threads = as.factor(threads))

p <- ggplot(data) + geom_line(aes(log2(n), p, color=threads)) +
  ggtitle("Parallel Efficiency", subtitle = "Multithreaded Grid Simulation") +
  xlab(TeX("$\\log_2(n)$")) + ylab(TeX("$p(n, T)$")) +
  theme_economist_white() + scale_color_wsj()

ggsave("p2.pdf", width=6, height=5)
