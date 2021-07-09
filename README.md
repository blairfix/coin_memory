# coin_memory

`coin_memory` is a program for simulating a coin toss and observing the probability of tails after a string of heads. For an infinite sample size, this probability is 50%. However, for small samples, the coin appears to favor tails and thus have a 'memory'.

The file `tail_prob.h` implements the basic simulation function. (If you are an R user, the file `tail_prob.cpp` implements an R version of the code, which can be compiled with Rcpp.)

```
tail_prob(sample_size, n_samples, streak_length)
```

Let's walk through the inputs. 

* `sample_size`: the number of times you want to toss the coin
* `n_samples`: the number of times you want to repeate the sample
* `streak_length`: the length of the streak of heads afterwhich to look for tails

`tail_prob` returns the average probability of tails after the streak, weighted equally across all samples.

The program `main.cpp` implements the `tail_prob` function over a log-spaced vector of sample sizes (from 10 to 1 million). For each sample size, the program returns the average probability of tails, follow a streak of heads of length `streak_length`. It also returns the standard deviation of probability across the `n_samples` of each sample size.

The script `RUNALL.R` implements `main.cpp` for various streak lengths.

For a simple example of a simulated coin toss, see the script `coin_toss_example.R`. 
