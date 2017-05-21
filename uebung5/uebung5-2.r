if (!("igraph" %in% installed.packages())) {
  install.packages("igraph")
}

library(igraph)

load("graph.rdata")


# 2. a)

num_edges <- ecount(g)
num_vertices <- vcount(g)

vertex_degrees <- degree(g)
num_leaves <- length(vertex_degrees[vertex_degrees == 1])


# 2. b)

num_neighbours_4 <- degree(g)[4]
num_neighbours_299 <- degree(g)[299]

eccentricity_4 <- eccentricity(g, V(g)[4])
eccentricity_299 <- eccentricity(g, V(g)[299])


# 2. c)

# minimum of all eccentricities
g_radius <- radius(g)

# maximum of all eccentricities
g_diameter <- diameter(g, directed = FALSE, unconnected = FALSE)

# for undirected graph: (2 * count of edges) / (count of vertices * (count of vertices - 1))
# for directed graph:   count of edges       / (count of vertices * (count of vertices - 1)) 
g_density <- graph.density(g)


# 2. d)

deg_dist <- degree_distribution(g)
plot(deg_dist, type = "l", xlab = "Degree", ylab = "Probability")


# 2. e)

g_subgraph <- induced_subgraph(g, V(g)[degree(g, V(g)) > 4])
g_subgraph_connected <- is_connected(g_subgraph)
plot(g_subgraph)