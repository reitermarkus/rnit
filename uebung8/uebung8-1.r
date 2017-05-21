if (!("igraph" %in% installed.packages())) {
  install.packages("igraph")
}

library(igraph)

A <- "A"
B <- "B"
C <- "C"
D <- "D"
E <- "E"


from <- c(A, B, B, C, C, D, D, E)
to   <- c(B, A, C, D, E, A, B, D)

edges <- data.frame(from, to)

graph1 <- graph_from_data_frame(edges, directed = TRUE)

plot.igraph(graph1, vertex.size=22, asp = 0)
print(page.rank(graph1))


from <- c(A, A, B, C, D, E)
to   <- c(B, C, C, D, E, A)

edges <- data.frame(from, to)

graph2 <- graph_from_data_frame(edges, directed = TRUE)

plot.igraph(graph2, vertex.size=22, asp = 0)
print(page.rank(graph2))
