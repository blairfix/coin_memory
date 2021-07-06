library(here)

dir = here()
setwd(dir)

# source files
setwd("./src")


streak_test = c(3, 5, 10, 15)

for(i in streak_test){
  
  # source file
  src = readLines("main.cpp")
    
  # streak length
  find = "streak_length = 10"
  replace = paste("streak_length = ", i, sep = "")
  print(replace)
  src = gsub(find, replace, src)
  
  # file out
  find = "trial.csv"
  replace = paste("trial_", i, ".csv", sep = "")
  src = gsub(find, replace, src)
  
  # export
  writeLines(src, "tmp.cpp")
  
  # compile
  command = "g++  -O3 -fopenmp -std=c++11 -I path/to/boost_1_75_0  tmp.cpp  -o tmp -llapack -lopenblas -lgomp -lpthread -larmadillo -march=native"
  system(command)
  
  # run
  system("./tmp")
  
  # move files
  command = paste("mv ", replace, " ../", replace, sep = "")
  system(command)
  
  
}

unlink("tmp.cpp")
unlink("tmp")

