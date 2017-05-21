load("data.rdata")

demodulate <- function(signal) {
  zeroes_and_ones = sapply(signal, function(x) {
    if (x <= 0) 0 else 1
  })
  
  discrete_values = rle(zeroes_and_ones)
  
  value_zero_one_list = Map(c, discrete_values$lengths, discrete_values$values)
  
  threshhold = (min(discrete_values$lengths) + max(discrete_values$lengths)) / 2
  
  demodulated_values = sapply(value_zero_one_list, function(x) {
    length = x[1]
    value = x[2]
    
    if (value <= 0)
      if (length <= threshhold) 0 else c(0, 0)
    else
      if (length <= threshhold) 1 else c(1, 1)
  })
  
  # extract odd indices (only edges are relevant)
  unlist(demodulated_values)[c(TRUE, FALSE)]
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


signal1 <- data$Signal3a
signal2 <- data$Signal3b

demodulated_signal1 <- demodulate(signal1)
demodulated_signal2 <- demodulate(signal2)

output1 <- bits_to_string(demodulated_signal1)
output2 <- bits_to_string(demodulated_signal2)
