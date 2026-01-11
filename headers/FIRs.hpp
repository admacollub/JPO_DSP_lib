#pragma once

#include "filter_type.hpp"

namespace af{
    template <typename T>
    class Lowpass : public FIR<T> {
        private:
            int m_order;
            double m_freq_cutoff;

        public:

        Lowpass() : FIR<T>(44100.0, "Lowpass", {0,1,0}), m_order(2), m_freq_cutoff(2250.0) {}

        Lowpass(double sampling_freq, std::string filter_name, int order, double freq_cutoff) :  FIR<T>(sampling_freq, filter_name, {0,1,0}), m_order(order), m_freq_cutoff(freq_cutoff) {
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

        void upadte_coeffs(int order, double freq_cutoff){
            m_order = order;
            m_freq_cutoff = freq_cutoff;
            this->set_coeff(calc_coeff(order, freq_cutoff));
        }

        /**
         * @brief Method for cloning it's self - used to make cascades
         */
        std::unique_ptr<Base_Filter<T>> clone() const override {
            return std::make_unique<Lowpass<T>>(*this);
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

        Highpass() : FIR<T>(44100.0, "Highpass", {0,1,0}), m_order(2), m_freq_cutoff(0.0) {}

        Highpass(double sampling_freq, std::string filter_name, int order, double freq_cutoff) :  FIR<T>(sampling_freq, filter_name, {0,1,0}), m_order(order), m_freq_cutoff(freq_cutoff)  {
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

        void upadte_coeffs(int order, double freq_cutoff){
            m_order = order;
            m_freq_cutoff = freq_cutoff;
            this->set_coeff(calc_coeff(order, freq_cutoff));
        }

        /**
        * @brief Method for cloning it's self - used to make cascades
        */
        std::unique_ptr<Base_Filter<T>> clone() const override {
            return std::make_unique<Highpass<T>>(*this);
        }

        int get_order() const{
            return m_order;
        }
        
        double get_freq_cutoff() const{
            return m_freq_cutoff;
        }
    };

    template <typename T>
    class Bandpass : public FIR<T> {
        private:
            int m_order;
            double m_freq_cut_low;
            double m_freq_cut_high;

        public:

        Bandpass() : FIR<T>(44100.0, "Bandpass", {0,1,0}),  m_order(2), m_freq_cut_low(0.0), m_freq_cut_high(2250.0) {}

        Bandpass(double sampling_freq, std::string filter_name, int order, double freq_cut_low, double freq_cut_high) :  FIR<T>(sampling_freq, filter_name, {0,1,0}), m_order(order), m_freq_cut_low(freq_cut_low), m_freq_cut_high(freq_cut_high)  {
            this->set_coeff(calc_coeff(order, freq_cut_low, freq_cut_high));
        }

        std::vector<T> calc_coeff( int order, double freq_cut_low, double freq_cut_high){    
            std::vector<T> coeff(order + 1);

            double fs = this->get_sampling_freq();
            double omega_1 = 2.0 * M_PI * (freq_cut_low/fs);
            double omega_2 = 2.0 * M_PI * (freq_cut_high/fs);
            double M = order/2.0;

            for(int i = 0; i <= order; i++){

                double n = static_cast<double>(i) - M;

                if(n==0){
                    coeff[i] = static_cast<T>((omega_2 - omega_1)/M_PI);
                }

                else {
                    coeff[i] = static_cast<T>((std::sin(omega_2 * n) - std::sin(omega_1 * n))/(M_PI * n));
                }
            }

            return coeff;
        }

        void upadte_coeffs(int order, double freq_cut_low, double freq_cut_high){
            m_order = order;
            m_freq_cut_low = freq_cut_low;
            m_freq_cut_high = freq_cut_high;
            this->set_coeff(calc_coeff(order, freq_cut_low, freq_cut_high));
        }

        /**
        * @brief Method for cloning it's self - used to make cascades
        */
        std::unique_ptr<Base_Filter<T>> clone() const override {
            return std::make_unique<Bandpass<T>>(*this);
        }

 
        int get_order() const{
            return m_order;
        }
        
        double get_freq_cut_low() const{
            return m_freq_cut_low;
        }

        double get_freq_cut_high() const{
            return m_freq_cut_high;
        }
    };


    template <typename T>
    class Bandstop : public FIR<T> {
    private:
        int m_order;
        double m_freq_cut_low;
        double m_freq_cut_high;

    public:

        Bandstop() : FIR<T>(44100.0, "Bandstop", {0,1,0}), m_order(2), m_freq_cut_low(0.0), m_freq_cut_high(2250.0) {}


        Bandstop(double sampling_freq, std::string filter_name, int order, double freq_cut_low, double freq_cut_high) 
            : FIR<T>(sampling_freq, filter_name, {0,1,0}), m_order(order), m_freq_cut_low(freq_cut_low), m_freq_cut_high(freq_cut_high)  
        {
            this->set_coeff(calc_coeff(order, freq_cut_low, freq_cut_high));
        }

        std::vector<T> calc_coeff(int order, double freq_cut_low, double freq_cut_high) {    
            std::vector<T> coeff(order + 1);

            double fs = this->get_sampling_freq();
            double omega_1 = 2.0 * M_PI * (freq_cut_low / fs);
            double omega_2 = 2.0 * M_PI * (freq_cut_high / fs);
            double M = order / 2.0;

            for (int i = 0; i <= order; i++) {
                double n = static_cast<double>(i) - M;

                if (n == 0) {
                    coeff[i] = static_cast<T>((M_PI - omega_2 + omega_1) / M_PI);
                }
                else {
                    coeff[i] = static_cast<T>((std::sin(omega_1 * n) - std::sin(omega_2 * n)) / (M_PI * n));
                }
            }

            return coeff;
        }

       void upadte_coeffs(int order, double freq_cut_low, double freq_cut_high){
            m_order = order;
            m_freq_cut_low = freq_cut_low;
            m_freq_cut_high = freq_cut_high;
            this->set_coeff(calc_coeff(order, freq_cut_low, freq_cut_high));
        }

        /**
        * @brief Method for cloning it's self - used to make cascades
        */
        std::unique_ptr<Base_Filter<T>> clone() const override {
            return std::make_unique<Bandstop<T>>(*this);
        }


        int get_order() const {
            return m_order;
        }
        
        double get_freq_cut_low() const {
            return m_freq_cut_low;
        }

        double get_freq_cut_high() const {
            return m_freq_cut_high;
        }
    };
}
