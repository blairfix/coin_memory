# hp_mod

`hp_mod` is an R function that generates a distribution of hierarchical power in a modeled society. It is based on a model first proposed by Herbert Simon (see reference below). In this model, firms are hierarchically organized with a fixed 'span of control'. This means that each superior commands the same number of subordinates, with the number of subordinates equal to the span of control. See Simon's paper for more details:

* Simon, H. A. (1957). The compensation of executives. Sociometry, 20(1), 32-35.

Given an input vector of firm sizes, `hp_mod` first organizes these firms into hierarchies using the algorithm found [here](https://github.com/blairfix/hierarchy). It then calculates the 'hierarchical power' of every individual in each firm. What's hierarchical power, you ask? It's a measure of control over subordinates. I define hierarchical power as the number of subordinates + 1. Here's an example:

![hp example](https://economicsfromthetopdown.files.wordpress.com/2019/08/finding_subordinates.png)

Check out the `hierarchical_power` function [here](https://github.com/blairfix/hierarchical_power). For example uses of this metric, see: 

*  *Personal Income and Hierarchical Power*. Journal of Economic Issues. 2019; 53(4): 928-945. [SocArXiv preprint](https://osf.io/preprints/socarxiv/pb475/).

* *[Energy, hierarchy and the origin of inequality](https://journals.plos.org/plosone/article?id=10.1371/journal.pone.0215692)*. PLOS ONE. 2019; 14(4):e0215692.



### Inputs

* `firm_vec` = a vector of firm sizes (number of employees in each firm)
* `span` =  the number of subordinates controlled by each superior. `span` must be greater than 1.

### Output
`hp_mod` returns a vector containing the hierarchical power of each individual in the modeled society. 


### Example:

```R

library(RcppArmadillo)
library(Rcpp)

sourceCpp("hp_mod.cpp")

# vector of firm sizes
firm_vec = c(2, 5)

# span of control
span = 2

# get distribution of hierarchical power
hp_mod(firm_vec, span)

     [,1]
[1,]    1
[2,]    2
[3,]    1
[4,]    1
[5,]    2
[6,]    2
[7,]    5

```

### A more useful example

Download and install the `hmod` package (found [here](https://github.com/blairfix/hmod)) to run the following model. We'll make a size distribution of firms that follow a power law. Then we'll generate a distribution of hierarchical power. Finally, we'll calculate the Gini index of hierarchical power concentration. The result, you'll find, depends on the power-law exponent of the firm-size distribution and span of control.


```R
# load hmod package
library(hmod)

# generate firm size distribution from power law 
firm_vec = rpld(n = 10^6, xmin = 1, alpha = 2.1)

# get distribution of hierarchical power
hp_dist = hp_mod(firm_vec, span = 3)

# get gini index of hierarchical power concentration
gini(hp_dist)

[1] 0.6861835
```





### Installation
To use `hp_mod`, install the following R packages:
 * [Rcpp](https://cran.r-project.org/web/packages/Rcpp/index.html) 
 * [RcppArmadillo](https://cran.r-project.org/web/packages/RcppArmadillo/index.html) 

Put the source code (`hp_mod.cpp`, `hierarchical_power.h` and `hierarchy_fix_span.h`) in the directory of your R script. Then source it with the command `sourceCpp('hp_mod.cpp')`.




