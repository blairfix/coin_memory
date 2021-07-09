library(stringr)

# generate random coin toss (in binary)
coin_toss = round( runif(1000) )

# collapse to character string
coin_string = paste(coin_toss, collapse="")

# count occurrence of heads after 2 heads
n_heads = str_count(coin_string, paste0("(?=","111",")"))

# count occurrence of tails after 2 heads
n_tails = str_count(coin_string, paste0("(?=","110",")"))

# probability of tails
p_tails = n_tails / (n_tails + n_heads)
