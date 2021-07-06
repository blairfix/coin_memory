#include <armadillo>
#include <boost/progress.hpp>
#include <chrono>
#include <iostream>
#include <math.h>
#include <vector>

#include "tail_prob.h"

/*
This implements the tail_prob function over a
log-spaced vector of sample sizes (from 10 to 1 million).
For each sample size, the program returns the average probability of tails,
follow a streak of heads of length streak_length. It also returns
the standard deviation of probability across the n_samples of each
sample size.

*/


int main(){

    // variables
    int n_trial =  400;
    int n_sample = 40000;
    int streak_length = 10;

    // make vector of log spaced sample sizes from 10^1 to 10^6
    arma::vec sample_vec = arma::logspace(1, 6, n_trial);

    // output matrix
    arma::mat output(n_trial, 3);

    // progress bar and timer
    auto start_time = std::chrono::system_clock::now();
    boost::progress_display show_progress(n_trial);

    // loop over trials
    #pragma omp parallel for firstprivate( sample_vec, n_sample, streak_length ) schedule (dynamic)
    for(int j = 0; j < n_trial; j++ ){

        // get sample size
        int sample_size =  sample_vec[j];

        // get vector of probabilities from trial
        auto tmp = tail_prob(sample_size,
                             n_sample,
                             streak_length
                             );

        // convert tmp to arma vec
        std::vector<double> tmp2{ std::make_move_iterator(std::begin(tmp)),
                                 std::make_move_iterator(std::end(tmp)) };

        arma::vec prob_vec =  arma::conv_to< arma::vec >::from(tmp2);

        // get mean and sd of probabilities
        double mean;
        double sd;

        if( prob_vec.size() > 0 ){

            mean = arma::mean(prob_vec);
            sd = arma::stddev(prob_vec);

        } else {
            mean = -1;
            sd = -1;
        }

        // export results
        output(j, 0) = sample_size;
        output(j, 1) = mean;
        output(j, 2) = sd;

        ++show_progress;
    }

    // runtime
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;
    std::cout  << "run time = " << elapsed_seconds.count() << " s" << std::endl;
    std::cout << std::endl;

    // write output to file
    output.save("trial.csv", arma::csv_ascii);

    return 0;

}

