# Markus Reiter

b_to_d <- function(bvek) {
  stopifnot(all(bvek %in% 0:1)) # input vector valid?
  sum(bvek * 2^(rev(1:length(bvek) - 1))) # decimal value
}

d_to_b <- function(d) {
  highest_power <- max(0, floor(log2(d)))
  powers <- seq(highest_power, 0)
  sapply(powers, function(x) {
    rest = d - (2^(x + 1) * d %/% 2^(x + 1))
    if (2^x <= rest) 1 else 0
  })
}

binary_input <- c(1, 0, 1, 0, 1)
decimal <- b_to_d(binary_input)
binary <- d_to_b(decimal)
decimal_output <- b_to_d(binary)
