#!/bin/bash


g++  -O3 -fopenmp -std=c++11 -I path/to/boost_1_75_0  main.cpp  -o main -llapack -lopenblas -lgomp -lpthread -larmadillo -march=native 


