#include "headers/base_filter.hpp"
#include "headers/filter_type.hpp"
#include "headers/FIRs.hpp"
#include <iostream>

int main()
{
    double fs = 44100.0;
    double f_square = 500.0; 
    std::vector<double> samples;

    for (int n = 0; n < 1000; n++) {
        double t = n / fs;
        double val = (std::sin(2.0 * M_PI * f_square * t) >= 0) ? 1.0 : -1.0;
        samples.push_back(val);
    }

    std::cout << "Input samples for filters: [";
    for(double s : samples){
        std::cout << s << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << std::endl;
 
    af::Highpass<double> HP_filter(44100.0, "HPF", 60 , 500);
    std::vector<double> coeffs = HP_filter.get_coeff();
    std::cout << "HPF coeffitients: [ ";
    for( double c : coeffs) {
        std::cout << c << " ";
    }
    std::cout << "]" << std::endl;

    std::cout << "Output from HPF [ ";
    for(double s : samples){
        double result = HP_filter.filter(s);
        std::cout << result << " ";
    }
    std::cout << " ]" << std::endl;


    return 0;
}