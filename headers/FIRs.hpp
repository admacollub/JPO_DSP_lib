#pragma once

#include "filter_type.hpp"

namespace af{
    template <typename T>
    class Lowpass : public FIR<T> {
        private:
            int m_order;
            double m_freq_cutoff;

        public:

        Lowpass() : FIR<T>(44100.0, "Lowpass", {0,1,0}) {}

        Lowpass(double sampling_freq, std::string filter_name, int order, double freq_cutoff) :  FIR<T>(sampling_freq, filter_name, {0,1,0}) {
            this->set_coeff(calc_coeff(order, freq_cutoff));
        }

        std::vector<T> calc_coeff( int order, double freq_cutoff){    
            std::vector<T> coeff(order + 1);

            double fs = this->get_sampling_freq();
            double omega = 2.0 * M_PI * (freq_cutoff/fs);
            double M = order/2.0;

            for(int i = 0; i <= order; i++){

                double n = static_cast<double>(i) - M;

                if(n==0){
                    coeff[i] = static_cast<T>(omega/M_PI);
                }

                else {
                    coeff[i] = static_cast<T>(std::sin(omega * n)/(M_PI * n));
                }
            }

            double sum = 0;
            for(T val : coeff) {
                sum += static_cast<double>(val);
            }
            if(sum != 0){
                for (T &val : coeff) {
                    val /= static_cast<T>(sum);
                }
            }

            return coeff;
        }

        int get_order() const{
            return m_order;
        }
        
        double get_freq_cutoff() const{
            return m_freq_cutoff;
        }

    };


    template <typename T>
    class Highpass : public FIR<T> {
        private:
            int m_order;
            double m_freq_cutoff;

        public:

        Highpass() : FIR<T>(44100.0, "Highpass", {0,1,0}) {}

        Highpass(double sampling_freq, std::string filter_name, int order, double freq_cutoff) :  FIR<T>(sampling_freq, filter_name, {0,1,0}) {
            this->set_coeff(calc_coeff(order, freq_cutoff));
        }

        std::vector<T> calc_coeff( int order, double freq_cutoff){    
            std::vector<T> coeff(order + 1);

            double fs = this->get_sampling_freq();
            double omega = 2.0 * M_PI * (freq_cutoff/fs);
            double M = order/2.0;

            for(int i = 0; i <= order; i++){

                double n = static_cast<double>(i) - M;

                if(n==0){
                    coeff[i] = static_cast<T>((M_PI - omega)/M_PI);
                }

                else {
                    coeff[i] = static_cast<T>(-1*std::sin(omega * n)/(M_PI * n));
                }
            }

            return coeff;
        }

        int get_order() const{
            return m_order;
        }
        
        double get_freq_cutoff() const{
            return m_freq_cutoff;
        }
    };
}
