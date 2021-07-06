//File: hothand.h
#ifndef HOTHAND_H
#define HOTHAND_H

#include <numeric>
#include <random>
#include <vector>
#include <list>


std::list<double> hot_hand ( int sample_size,
                             int n_samples,
                             int streak_length )
{

    // probability results
    std::list<double> prob_vec;

    // loop over samples
    for(int it = 0; it < n_samples; it++){

        // generate binary sample
        std::random_device r;
        std::default_random_engine generator{r()};
        std::uniform_int_distribution<int> distribution(0,1);
        std::vector<int> x(sample_size);

        for(int i = 0; i < sample_size; i++) {
            x[i] = distribution(generator);
        }


        // look for streaks
        int streak_counter = 0;
        std::list<int> end_value;

        for(int i = 0; i < x.size(); i++){


            if( x[i] == 0 ){

                // test if streak equal to desired streak_length
                // if so, record value of x
                if( streak_counter >= streak_length ){
                    end_value.push_back( x[i]);
                }

                // streak continues
                streak_counter++;


            } else{

                // test if streak equal to desired streak_length
                // if so, record value of x
                if( streak_counter >= streak_length ){
                    end_value.push_back( x[i] );
                }

                // streak ends
                streak_counter = 0;

            }
        }


        // analyze streak end
        // if not null, pushback to prob vec
        if(end_value.size() > 0 ){

            double sum = std::accumulate(end_value.begin(), end_value.end(), 0.0);
            double mean = ((double) sum) / end_value.size();

            prob_vec.push_back(mean);

        }

    }


return prob_vec;

}

#endif