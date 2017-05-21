# Markus Reiter

# convert string to number
layer4_down <- function(str) {
  str = paste(sprintf("%04d", utf8ToInt(str)), collapse = "")
  number =  as.numeric(paste(str, collapse = ""))
  print(sprintf("%f", number))
  number
}

# convert number to string
layer4_up <- function(number) {
  print(sprintf("%f", number))
  
  length <- ceiling(log10(number) / 4)
  list <- seq(length, 1) * 4
  
  numbers = sapply(list, function(x) {
    # there is some weird rounding error in here
    (number %% 10^(x)) %/% 10^(x-4)
  })
  
  paste(sapply(numbers, intToUtf8), collapse = "")
}


# convert number to list of lists of 4 digits
layer3_down <- function(number) {
  length <- ceiling(log10(number) / 4)
  list <- seq(length, 1) * 4
  
  numbers <- sapply(list, function(x) {
    (number %% 10^(x)) %/% 10^(x-4)
  })
  
  lapply(strsplit(sprintf("%04d", numbers), ""), as.numeric)
}

# convert list of lists of 4 digits to number
layer3_up <- function(list_of_numbers) {
  as.numeric(paste(as.character(unlist(list_of_numbers)), collapse = ""))
}


# add header
layer2_down <- function(header, number) {
  c(list(header), number)
}

# remove header
layer2_up <- function(number_with_header, n) {
  length <- length(number_with_header)
  number_with_header[2:length]
}


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

layer1_down <- function(list) {
  sapply(list, function(row) {
    sapply(row, function( x) {
      bin <- d_to_b(x)
      c(rep(0, 4 - length(bin)), bin)
    })
  })
}

layer1_up <- function(list) {
  # split into groups of 4 bits
  list <- split(list, ceiling(seq_along(list) / 4))
  
  list <- sapply(list, b_to_d)
  
  # split into groups of 4 digits
  split(list, ceiling(seq_along(list) / 4))
}


a__str_in        <- "abc def" # layer5_down
b__num_in        <- layer4_down(a__str_in)
c__num_list_in   <- layer3_down(b__num_in)
d__header_in     <- layer2_down(c(8, 8, 8, 8), c__num_list_in)
e__bits_in       <- layer1_down(d__header_in)
f__bits_out      <- layer1_up(e__bits_in)
g__header_out    <- layer2_up(f__bits_out, 1)
h___num_list_out <- layer3_up(g__header_out)
i__str_out       <- layer4_up(h___num_list_out) #layer5_up


