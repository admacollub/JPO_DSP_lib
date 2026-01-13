#include "headers/base_filter.hpp"
#include "headers/filter_type.hpp"
#include "headers/FIRs.hpp"
#include "headers/IIRs.hpp"
#include "headers/filter_cascade.hpp"
#include <iostream>

int main()
{

    std::cout << "This is demonstration of DSP lib for students project " << std::endl;
    std::cout << "First we will create arbitraty FIR filter by parametric constructor, with some coeffitients " << std::endl;

    af::FIR<double> Fir_filter(4100.0, "First Filter", {0.05,0.1,0.35,0.35,0.1,0.05});

    std::cout << "Now displaying filter parameters by getters: " << std::endl;
    std::cout << "- Filter name: " << Fir_filter.get_filter_name() << std::endl;
    std::cout << "- Sampling frequency: " << Fir_filter.get_sampling_freq() << std::endl;
    std::cout << "- Coeffitients:  [ ";
    std::vector<double> coeffs = Fir_filter.get_coeff();
    for(double c : coeffs){
        std::cout << c << " " ;
    }
    std::cout << "]" << std::endl;
    std::cout << std::endl;
    std::cout << "Now some filtering, this is our sample: [ ";
    double sample[] = {1, -1, 1, 0, 1, -1, 1, 0, 1, -1, 0, 1};
    for(double s : sample){
        std::cout << s << " ";
    }
    std::cout << "]" << std::endl;
    
    std::cout << "And this is filtering result: [";
    for(double s : sample){
        double result = Fir_filter.filter(s);
        std::cout << result << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << std::endl;

    std::cout << "Second Filter will be made by using ChebyshevLowpass class" << std::endl;
    std::cout << "Methods of this object will calculate coeffitients for us" << std::endl;
    af::ChebyshevLowpass<double> Iir_filter(44100.0, "Second filter", 2 , 3000.0 , 5.0);
     std::cout << "Now displaying filter parameters by getters: " << std::endl;
    std::cout << "- Filter name: " << Iir_filter.get_filter_name() << std::endl;
    std::cout << "- Sampling frequency: " << Iir_filter.get_sampling_freq() << std::endl;
    std::cout << "- Cutoff Frequency: " << Iir_filter.get_freq_cutoff() << std::endl;
    std::cout << "- Coeffitients:  b = [ ";

    std::vector<double> coeffs_b = Iir_filter.get_coeff_b();
    std::vector<double> coeffs_a = Iir_filter.get_coeff_a();
    for( double c : coeffs_b) {
        std::cout << c << " ";
    }
    std::cout << "], a = [ ";


    for( double c : coeffs_a) {
        std::cout << c << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << std::endl;


    std::cout << "And this is filtering result, for the same examples as earlier: [";
    for(double s : sample){
        double result = Iir_filter.filter(s);
        std::cout << result << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << std::endl;
    std::cout << "Finally, we will make cascade of this two filters" << std::endl;
    std::cout << "Cascade is created by operation auto cascade = Fir_filter + Iir_filter" << std::endl ;

    auto Cascade = Fir_filter + Iir_filter;

    std::cout << "These are result of filtering in cascade of two filters: [ ";
    for(double s : sample){
        double result = Cascade->filter(s);
        std::cout << result << " ";
    }
    std::cout << " ]" << std::endl;


    return 0;
}