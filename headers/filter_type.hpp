#pragma once

#include "base_filter.hpp"

namespace af{
    template <typename T>
    class FIR : public Base_Filter<T> {
        private:
            std::vector<T> m_coeff;
            std::vector<T> m_past_sample;
 
        public:

            FIR() : Base_Filter<T>(44100.0, "FIR") {}

            FIR(double sampling_freq, std::string filter_name, const std::vector<T>& coeffitients) : Base_Filter<T>(sampling_freq, filter_name){
                set_coeff(coeffitients);
            }

            virtual ~FIR() = default;

            bool set_coeff(const std::vector<T>& coeff) {
                if(coeff.empty()) {
                    return false;
                }

                else{
                    m_coeff = coeff;
                    m_past_sample = std::vector<T>(m_coeff.size(), static_cast<T>(0)); //anonimo objcetto 
                }

                return true;
            }

            const std::vector<T>& get_coeff() const{
                return m_coeff;
            }

            const std::vector<T>& get_past() const{
                return m_past_sample;
            }

            void reset() override{
                m_past_sample = std::vector<T>(m_coeff.size(), static_cast<T>(0));
            }

            T filter(T input) override{
                for(int i = m_past_sample.size()-1 ; i > 0; i--){
                    m_past_sample[i] = m_past_sample[i-1];
                }

                m_past_sample[0] = input;
                T output = static_cast<T>(0);

                for (size_t i = 0; i< m_coeff.size(); i++){
                    output += m_coeff[i] * m_past_sample[i];
                }

                return output;
            }

    };

    template <typename T>
    class IIR : public Base_Filter<T> {
        private:
            std::vector<T> m_coeff_b;
            std::vector<T> m_coeff_a;
            std::vector<T> m_past_input;
            std::vector<T> m_past_output;
        public:
        
            IIR() : Base_Filter<T>(44100.0, "IIR") {}

            IIR(double sampling_freq, std::string filter_name, const std::vector<T>& coeffitients_b, const std::vector<T>& coeffitients_a ) : Base_Filter<T>(sampling_freq, filter_name){
                set_coeff(coeffitients_b, coeffitients_a);
            }

            virtual ~IIR() = default;

            bool set_coeff(const std::vector<T>& coeff_b, const std::vector<T>& coeff_a) {
                if(coeff_b.empty()||coeff_a.empty()) {
                    return false;
                }

                else{
                    m_coeff_b = coeff_b;
                    m_coeff_a = coeff_a;
                    m_past_input = std::vector<T>(m_coeff_b.size(), static_cast<T>(0)); //anonimo objcetto 
                    m_past_output = std::vector<T>(m_coeff_a.size() + 1, static_cast<T>(0));
                }

                return true;
            }       

            const std::vector<T>& get_coeff_a() const{
                return m_coeff_a;
            }

            const std::vector<T>& get_coeff_b() const{
                return m_coeff_b;
            }

            const std::vector<T>& get_past_input() const{
                return m_past_input;
            }

            const std::vector<T>& get_past_output() const{
                return m_past_output;
            }


            void reset() override{
                m_past_input = std::vector<T>(m_past_input.size(), static_cast<T>(0));
                m_past_output = std::vector<T>(m_past_output.size(), static_cast<T>(0));
            }
            
            T filter(T input) override{
                for(int i = m_past_input.size() - 1 ; i > 0; i--){
                    m_past_input[i] = m_past_input[i-1];
                }                
                m_past_input[0] = input;

            
                for (int i = m_past_output.size() - 1; i > 0; i--) {
                    m_past_output[i] = m_past_output[i - 1];
                }

                T output = static_cast<T>(0);
                for (size_t i = 0; i < m_coeff_b.size(); i++) {
                    output += m_coeff_b[i] * m_past_input[i];
                }

                for (size_t i = 0; i < m_coeff_a.size(); i++) {
                    output -= m_coeff_a[i] * m_past_input[i + 1];
                }

                m_past_output[0] = output;
                return output;
            }



    };
    /*    template <typename T>
    class Other : public Base_Filter<T> {
        private:

        public:
    };
    */

}
