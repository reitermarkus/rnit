if (!("curl" %in% installed.packages())) {
  install.packages("curl")
}

library(curl)


host_for_group <- function(group_id) {
  group_id <- 100 + group_id
  paste("http://192.168.83.", group_id, sep = "")
}


weltformel_url <- function(host) {
  robots <- paste(host, "/robots.txt", sep = "")

  tryCatch(
    {
      result <- curl_fetch_disk(robots, tempfile())

      file <- result$content

      robots_lines <- readLines(file)

      regex <- "Disallow:\\s+(/geheim\\-\\d+/weltformel.txt)"
      matches <- regexpr(regex, robots_lines, perl = TRUE)

      extracted_matches <- gsub(regex, "\\1", regmatches(robots_lines, matches))

      if (length(extracted_matches) == 0) {
        return()
      }

      paste(host, extracted_matches, sep = "")
    },
    error = function(e) {
      print(paste("Could not connect to ", host, "."))
      return()
    }
  )
}

hosts <- host_for_group(seq(1, 60))

sapply(hosts, function(host) {
  response <- weltformel_url(host)

  if(!is.null(response)) {
    print(response)
  }
})
