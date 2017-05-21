load("data.rdata")

code_table <- data$codes4B5B

encode <- function(string) {
  string <- utf8ToInt(string)
  bitstream <- intToBits(string)
  bit_matrix <- matrix(bitstream, ncol = 2, byrow = TRUE)
  codes <- apply(bit_matrix, 1, function(row) {
    paste(row, collapse = "")
  })
  
  encoded_list <- sapply(codes, function(code) {
    code_table[[code]]
  }, simplify = FALSE)
  
  unlist(encoded_list)
}

encoded <- encode("Heiner that.")
