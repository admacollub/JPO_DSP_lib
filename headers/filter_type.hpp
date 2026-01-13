#pragma once

#include "base_filter.hpp"

namespace af{

    /**
     * @brief FIR class is used to create arbitrary finate impluse response filters
     * * This class hold coeffitients and memory of filter (both needed to filtering). 
     * * Implements methods for filtering in FIR type filters, reseting memory of filters, and cloning (used for cascades).
     * @tparam T is type of numerical data to be used as input samples.
     */
    template <typename T>
    class FIR : public Base_Filter<T> {
        private:
            std::vector<T> m_coeff;
            std::vector<T> m_past_sample;
 
        public:

            /**
             * @brief Deafault constructor of FIR object. 
             * * Sets basic values for sampling frequency(44100Hz) and name(FIR).
             */
            FIR() : Base_Filter<T>(44100.0, "FIR") {}

            /**
             * @brief Parametric constructor for FIR object.
             * @param sampling_freq Double type sampling frequency of samples to be filtered.
             * @param filter_name String type name of FIR.
             * @param coeffitients Vector of coeffitients (numerical type).
             */
            FIR(double sampling_freq, std::string filter_name, const std::vector<T>& coeffitients) : Base_Filter<T>(sampling_freq, filter_name){
                set_coeff(coeffitients);
            }

            /**
             * @brief Virtual destrutor of FIR object.
             */
            virtual ~FIR() = default;

            /**
             * @brief Setter of coeffitients to a FIR filter.
             * @param coeff Vector (numerical type) of coeffitients. 
             * @return Returns true if setting succesful, otherwise false. (vector cannot be empty) 
             */
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

            /**
             * @brief Getter of filters coeffitients.
             * @return Retutrns vector of coeffitiens.
             */
            const std::vector<T>& get_coeff() const{
                return m_coeff;
            }

            /**
             * @brief Getter of filters memory.
             * @return Retutrns vector of samples in memory.
             */
            const std::vector<T>& get_past() const{
                return m_past_sample;
            }

            /**
             * @brief Method for reseting filter memory.
             */
            void reset() override{
                m_past_sample = std::vector<T>(m_coeff.size(), static_cast<T>(0));
            }

            /**
             * @brief Method for filtering a sample of input signal for FIR filters.
             * * Filters one sample at a time for flexibility in using.
             * @tparam Numerical type input sample.
             * @return Filtered numerical type input sample (same as input type).
             */
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

            /**
            * @brief Method for cloning it's self - used to make cascades
            * @return Returns unique pointer for filters clone.
            */
            std::unique_ptr<Base_Filter<T>> clone() const override {
                return std::make_unique<FIR<T>>(*this);
            }


    };


    /**
     * @brief IIR class is used to create arbitrary infinite impluse response filters
     * * This class hold coeffitients and memory of filter (both needed to filtering). 
     * * Implements methods for filtering in FIR type filters, reseting memory of filters, and cloning (used for cascades).
     * @tparam T is type of numerical data to be used as input samples.
     */
    template <typename T>
    class IIR : public Base_Filter<T> {
        private:
            std::vector<T> m_coeff_b;
            std::vector<T> m_coeff_a;
            std::vector<T> m_past_input;
            std::vector<T> m_past_output;
        public:

            /**
             * @brief Deafault constructor of IIR object. 
             * * Sets basic values for sampling frequency(44100Hz) and name(IIR).
             */       
            IIR() : Base_Filter<T>(44100.0, "IIR") {}

            /**
             * @brief Parametric constructor for IIR object.
             * @param sampling_freq Double type sampling frequency of samples to be filtered.
             * @param filter_name String type name of IIR.
             * @param coeffitients_b Vector of coeffitients b (numerical type).
             * @param coeffitients_a Vector of coeffitients a(numerical type).           
             */           
            IIR(double sampling_freq, std::string filter_name, const std::vector<T>& coeffitients_b, const std::vector<T>& coeffitients_a ) : Base_Filter<T>(sampling_freq, filter_name){
                set_coeff(coeffitients_b, coeffitients_a);
            }

            /**
            * @brief Virtual destrutor of IIR object.
            */
            virtual ~IIR() = default;

            /**
             * @brief Setter of coeffitients to a FIR filter.
             * @param coeff_b Vector (numerical type) of coeffitients b. 
             * @param coeff_a Vector (numerical type) of coeffitients a. 
             * @return Returns true if setting succesful, otherwise false. (vectors cannot be empty) 
             */
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

            /**
             * @brief Getter of coefitienst a of IIR filter.
             * @return Returns vector of coeffitiets.
             */
            const std::vector<T>& get_coeff_a() const{
                return m_coeff_a;
            }

            /**
             * @brief Getter of coefitienst b of IIR filter.
             * @return Returns vector of coeffitiets.
             */
            const std::vector<T>& get_coeff_b() const{
                return m_coeff_b;
            }

            /**
             * @brief Getter of filter's input memory.
             * @return Returns vector of input samples in memory.
             */
            const std::vector<T>& get_past_input() const{
                return m_past_input;
            }

            /**
             * @brief Getter of filter's output memory.
             * @return Returns vector of output samples in memory.
             */
            const std::vector<T>& get_past_output() const{
                return m_past_output;
            }

            /**
             * @brief Method for reseting filter's internal memory.
             */
            void reset() override{
                m_past_input = std::vector<T>(m_past_input.size(), static_cast<T>(0));
                m_past_output = std::vector<T>(m_past_output.size(), static_cast<T>(0));
            }
            
            /**
             * @brief Method for filtering a sample of input signal for IIR filters.
             * * Filters one sample at a time for flexibility in using.
             * @tparam Numerical type input sample.
             * @return Filtered numerical type input sample (same as input type).
             */
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
                    output -= m_coeff_a[i] * m_past_output[i + 1];
                }

                m_past_output[0] = output;
                return output;
            }

            /**
             * @brief Method for cloning it's self - used to make cascades
             */
            std::unique_ptr<Base_Filter<T>> clone() const override {
                return std::make_unique<IIR<T>>(*this);
            }
                


    };

}
