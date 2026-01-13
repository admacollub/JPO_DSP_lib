#pragma once

#include "filter_type.hpp"

namespace af{  

    /**
     * @brief ChebyshevLowpass filter class is used to calculate chebyschev 1 type Lowpass coeffitiens for biquad filter and set them. 
     * * Class hold order(not used) of the filter, cutoff frequencies, passband ripple and methods for calucating coeffitients and updateing filter runing.
     * @tparam T is sample input type numeric data.
     */
    template <typename T>
    class ChebyshevLowpass : public IIR<T> {
        private:
            int m_order;
            double m_freq_cutoff;
            double m_pass_ripple;

        public:

        /**
        * @brief Deafault constructor of ChebyshevLowpass object. 
        * * Sets basic values for allpass filter.
        */
        ChebyshevLowpass() : IIR<T>(44100.0, "Chebychev Lowpass", {0,1,0}, {0,0}), m_order(2), m_freq_cutoff(2250.0) {}
        
        /**
         * @brief Parametric construcotr of ChebyshevLowpass filter object.
         * @param sampling_freq Double type Sampling frequency if signal input.
         * @param filter_name String type Name of filter.
         * @param order Integer type order of filter.
         * @param freq_cutoff Double type lower cutoff frequency.
         * @param ripple Double type passband ripple of filter. 
         */
        ChebyshevLowpass(double sampling_freq, std::string filter_name, int order, double freq_cutoff, double ripple) :  IIR<T>(sampling_freq, filter_name, {0,1,0}, {0,0}), m_order(order), m_freq_cutoff(freq_cutoff), m_pass_ripple(ripple){
            auto [b, a] = calc_coeff_biq(freq_cutoff, ripple);
            this->set_coeff(b, a);
        }

        /**
         * @brief Method for calculating biquad filter coeffitients.
         * * Method takes in parameters and only calculate coeffitnients of filter, does not set them to a object.
         * @param freq_cutoff Double type lower cutoff frequency.
         * @param ripple Double type passband ripple of filter.
         * @return Returns pair of coeffitients vectors in type of setting in object constructor.
         */
        std::pair<std::vector<T>, std::vector<T>> calc_coeff_biq(double freq_cutoff, double ripple){    

            double fs = this->get_sampling_freq();
            double epsilon = std::sqrt(std::pow(10.0, ripple / 10.0) - 1.0);
            double v = (1.0 / 2.0) * std::asinh(1.0 / epsilon);
            double k = std::tan(M_PI * freq_cutoff / fs);
            double k2 = k * k;

            double s_re = -std::sinh(v) * std::sin(M_PI / 4.0);
            double s_im = std::cosh(v) * std::cos(M_PI / 4.0);
            double a_sq = s_re * s_re + s_im * s_im;
            double a0 = k2 - 2.0 * s_re * k + a_sq;

            std::vector<T> b= {static_cast<T>(k2/a0), static_cast<T>(2.0*k2/a0), static_cast<T>(k2 / a0)};
            std::vector<T> a = {static_cast<T>(2.0 * (k2 - a_sq) / a0), static_cast<T>((k2 + 2.0 * s_re * k + a_sq) / a0)};

            double gain_fix = 1.0 / std::sqrt(1.0 + epsilon * epsilon);
            for(auto& val : b){
                val *= static_cast<T>(gain_fix);
            } 

            return {b, a};
        }

        /**
         * @brief Method (setter) used to calculate and set filter coeffitients.
         * @param order Integer type order of filter.
         * @param freq_cutoff Double type cutoff frequency.
         * @return Returns true if succesful. False otherwise.
         */
        void upadate_coeffs(int order, double freq_cutoff, double ripple){
            m_order = order;
            m_freq_cutoff = freq_cutoff;
            m_pass_ripple = ripple;
            auto [b, a] = calc_coeff_biq(freq_cutoff, ripple);
            this->set_coeff(b, a);
        }

        /**
        * @brief Method for cloning it's self - used to make cascades
        */
        std::unique_ptr<Base_Filter<T>> clone() const override {
            return std::make_unique<ChebyshevLowpass<T>>(*this);
        }

        /**
         * @brief Getter of the object order.
         * @return Returns integer type order of the filter.
         */
        int get_order() const{
            return m_order;
        }
        
        /**
         * @brief Getter of the object cutoff frequency.
         * @return Returns Double type cutoff frequency.
         */
        double get_freq_cutoff() const{
            return m_freq_cutoff;
        }

    };

    /**
     * @brief ChebyshevHighpass filter class is used to calculate chebyschev 1 type highpass coeffitiens for biquad filter and set them. 
     * * Class hold order(not used) of the filter, cutoff frequencies, passband ripple and methods for calucating coeffitients and updateing filter runing.
     * @tparam T is sample input type numeric data.
     */ 
    template <typename T>
    class ChebyshevHighpass : public IIR<T> {
        private:
            int m_order;
            double m_freq_cutoff;
            double m_pass_ripple;

        public:

        /**
        * @brief Deafault constructor of ChebyshevHighpass object. 
        * * Sets basic values for allpass filter.
        */
        ChebyshevHighpass() : IIR<T>(44100.0, "Chebychev Lowpass", {0,1,0}, {0,0}), m_order(2), m_freq_cutoff(2250.0) {}

        /**
         * @brief Parametric construcotr of ChebyshevHighpass filter object.
         * @param sampling_freq Double type Sampling frequency if signal input.
         * @param filter_name String type Name of filter.
         * @param order Integer type order of filter.
         * @param freq_cutoff Double type lower cutoff frequency.
         * @param ripple Double type passband ripple of filter. 
         */
        ChebyshevHighpass(double sampling_freq, std::string filter_name, int order, double freq_cutoff, double ripple) :  IIR<T>(sampling_freq, filter_name, {0,1,0}, {0,0}), m_order(order), m_freq_cutoff(freq_cutoff), m_pass_ripple(ripple){
            auto [b, a] = calc_coeff_biq(freq_cutoff, ripple);
            this->set_coeff(b, a);
        }

        /**
         * @brief Method for calculating biquad filter coeffitients.
         * * Method takes in parameters and only calculate coeffitnients of filter, does not set them to a object.
         * @param freq_cutoff Double type lower cutoff frequency.
         * @param ripple Double type passband ripple of filter.
         * @return Returns pair of coeffitients vectors in type of setting in object constructor.
         */
        std::pair<std::vector<T>, std::vector<T>> calc_coeff_biq(double freq_cutoff, double ripple){    
        
            double fs = this->get_sampling_freq();

            if (freq_cutoff <= 0){
                freq_cutoff = 1.0;
            } 

            if (freq_cutoff >= fs / 2.0){
                freq_cutoff = fs / 2.0 - 1.0;
            }

            double epsilon = std::sqrt(std::pow(10.0, ripple / 10.0) - 1.0);
            double v = (1.0 / 2.0) * std::asinh(1.0 / epsilon); 
            double k = std::tan(M_PI * freq_cutoff / fs);
            double k2 = k * k;
            
            double s_re = -std::sinh(v) * std::sin(M_PI / 4.0);
            double s_im = std::cosh(v) * std::cos(M_PI / 4.0);
            double a_sq = s_re * s_re + s_im * s_im;
            double a0 = a_sq * k2 - 2.0 * s_re * k + 1.0;

            double b0 = 1.0 / a0;
            double b1 = -2.0 / a0;
            double b2 = 1.0 / a0;

            double gain_fix = 1.0 / std::sqrt(1.0 + epsilon * epsilon);
            b0 *= gain_fix;
            b1 *= gain_fix;
            b2 *= gain_fix;

            std::vector<T> b = {static_cast<T>(b0), static_cast<T>(b1), static_cast<T>(b2) };

            std::vector<T> a = {static_cast<T>(2.0 * (a_sq * k2 - 1.0) / a0), static_cast<T>((a_sq * k2 + 2.0 * s_re * k + 1.0) / a0)};

            return {b, a};

        }
        
        /**
         * @brief Method (setter) used to calculate and set filter coeffitients.
         * @param order Integer type order of filter.
         * @param freq_cutoff Double type cutoff frequency.
         * @return Returns true if succesful. False otherwise.
         */
        void upadate_coeffs(int order, double freq_cutoff, double ripple){
            m_order = order;
            m_freq_cutoff = freq_cutoff;
            m_pass_ripple = ripple;
            auto [b, a] = calc_coeff_biq(freq_cutoff, ripple);
            this->set_coeff(b, a);
        }

        /**
        * @brief Method for cloning it's self - used to make cascades
        */
        std::unique_ptr<Base_Filter<T>> clone() const override {
            return std::make_unique<ChebyshevHighpass<T>>(*this);
        }

        /**
         * @brief Getter of the object order.
         * @return Returns integer type order of the filter.
         */
        int get_order() const{
            return m_order;
        }
        
        /**
         * @brief Getter of the object cutoff frequency.
         * @return Returns Double type cutoff frequency.
         */
        double get_freq_cutoff() const{
            return m_freq_cutoff;
        }
            
    };
    
}