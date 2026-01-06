#include "headers/base_filter.hpp"
#include "headers/filter_type.hpp"
#include <iostream>

int main()
{
    af::FIR<double> MovingAvergae(44100.0, "Fisrt Filter", {0,2,0,0,10,0,0,0});
    std::vector<double> samples {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
    std::vector<double> outputs;

    for(double s : samples) {

        double result = MovingAvergae.filter(s);
        outputs.push_back(result);

        std::cout << "In: " << s << " \t-> Out: " << result << std::endl;
    }

    return 0;
}