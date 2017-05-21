load("data.rdata")

multiply_matrix_by_chip <- function(matrix, chip) {
  matrix %*% diag(chip)
}

demultiplex <- function(data, chip) {
  chip_length <- length(chip)
  data_matrix <- matrix(data, ncol = chip_length, byrow = TRUE)
  multiplied_matrix <- multiply_matrix_by_chip(data_matrix, chip)
  row_sums <- rowSums(multiplied_matrix)
  sapply(row_sums, function(x) {
    if (x <= 0) 0 else 1
  })
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

signal <- data$Signal4
chip1 <- data$Chip1
chip2 <- data$Chip2

demultiplexed_chip1 = bits_to_string(demultiplex(signal, chip1))
demultiplexed_chip2 = bits_to_string(demultiplex(signal, chip2))
