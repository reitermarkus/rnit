# b)

pol_div <- function(p, q){
  # temporary array for xor'ing
  tmp <- p[1:length(q)]
  
  result <- c()
  
  i <- length(q)
  while(i <= length(p)) {
    result <- c(result, tmp[1])
    
    i <- i + 1

    if(tmp[1] == 1){ 
      tmp2 <- xor(tmp, q) 
    } else {
      tmp2 <- xor(tmp, rep(0, length(q)))
    }
    
    # remove first and add last from dividend
    tmp <- c(tmp2[2:length(q)], p[i])
  }
  
  # add the remainder to the end of the result
  c(result, tmp[1:(length(tmp) - 1)]) 
}

res <- pol_div(c(1, 1, 0, 1, 1, 0, 1, 1), c(1, 0, 0, 1))
res <- pol_div(c(1, 0 , 1, 1, 1, 0, 0), c(1, 0, 1))
res <- pol_div(c(1, 0, 0, 1, 0), c(1, 0, 0, 1))


# c)

crc_calculate <- function(bin_vec, method){
  padding <- rep(0, length(method) - 1)
  
  result <- pol_div(c(bin_vec, padding), method)
  
  # remainder
  tail(result, length(method) - 1)
}


# d)

crc_check <- function(bin_vec, method){
  result <- pol_div(bin_vec, method)
  
  remainder <- tail(result, length(method) - 1)
  
  # check if remainder is 0
  all(!remainder)
}


# available methods
usb       <- c(1, 0, 0, 1, 0, 1)
bluetooth <- c(1, 1, 0, 1, 0, 1)
isdn      <- c(1, 0, 0, 0, 0, 0, 1, 1, 1)
crc_16    <- c(1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)


bits = c(1, 0, 1, 1, 1)

crc <- crc_calculate(bits, crc_16)

# comment out to make crc invalid
# crc[1] = !crc[1]

crc_checksum <- crc_check(c(bits, crc), crc_16)
