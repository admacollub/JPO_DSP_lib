#pragma once

#include "base_filter.hpp"

namespace af{
    template <typename T>
    class FIR : public Base_Filter<T> {
        private:
            std::vector<T> m_coeff;
            std::vector<T> m_past_sample;
 
        public:

            FIR() : Base_Filter<T>(44100.0, "Filter") {}

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

        public:
    };

    template <typename T>
    class Other : public Base_Filter<T> {
        private:

        public:
    };
}
