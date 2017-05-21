load("data.rdata")

# assign every value in sequence a phase
demodulate <- function(val, phases = list(c(0,0), c(0, 1), c(1, 0), c(1, 1))) {
  if (val < 0 & val >= -0.5) return (phases[[1]])
  if (val >= 0.5)            return (phases[[2]])
  if (val < 0.5 & val > 0)   return (phases[[3]])
  if (val < -0.5)            return (phases[[4]])
}

b_to_d <- function(bvek) {
  stopifnot(all(bvek %in% 0:1)) # input vector valid?
  sum(bvek * 2^(rev(1:length(bvek) - 1))) # decimal value
}

bits_to_string <- function(bits) {
  matrix = matrix(bits, ncol = 8, byrow = TRUE)
  
  int_list = apply(matrix, 1, function(row) {
    b_to_d(unlist(row))
  })
  
  paste(intToUtf8(int_list), collapse = "")
}


signal <- data$Signal2a

# plot to see phases; every 100 elements = 1 phase
plot(signal[1:700], type = "l")

# create rate accordingly
rate_seq <- seq(from = 90, to = length(signal), by = 100)
signal_rate <- signal[rate_seq]

binary_phases <- sapply(signal_rate, demodulate)

output <- bits_to_string(binary_phases)
