if (!("igraph" %in% installed.packages())) {
  install.packages("igraph")
}

library(igraph)

B  <- "Bregenz"
MUC <- "München"
IBK <- "Innsbruck"
K  <- "Klagenfurt"
S <- "Salzburg" 
L <- "Linz"
SP <- "Sankt Pölten"
G <- "Graz"
E  <- "Eisenstadt"
W  <- "Wien"

from <- c(B, B, IBK, IBK, IBK, K, K, K, S, S, L, L, G, G, SP, W)
to   <- c(IBK,MUC, MUC,G,K, S,L,W, MUC,L, G,SP, E,W, W, E)

x <- c(12, -15, 5, 55, 27, 45, 100, 75, 63, 85)
y <- c(0.07, 0, -0.015, -0.08, 0.03, 0.06, -0.01, -0.06, 0.050, 0.045)

nodes <- c(MUC, B, IBK, K, S, L, E, G, SP, W)

nodes <- data.frame(nodes, x ,y) 
edges <- data.frame(from, to)

spy_map <- graph_from_data_frame(vertices = nodes, d = edges, directed =FALSE) %>% 
  set_edge_attr("label", value = c(0.2, 0.2, 0.6, 0.5, 0.4, 0.5, 0.4, 0.3, 0.5, 0.3, 
                                   0.2, 0.2, 0.1, 0.1, 0.2, 0.1))

plot.igraph(spy_map, vertex.size=22, asp = 0)
