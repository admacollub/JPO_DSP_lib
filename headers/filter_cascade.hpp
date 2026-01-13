#pragma once

#include "base_filter.hpp"

namespace af{

    /**
     * @brief Cascade class holding a vector of unique pointers to any filters or cascades.
     * * This class is used to make filtering cascades of filters. Implements filteing, reseting and adding new filters to cascade methods.
     * @tparam Is a numerical type of input samples that will be filtered.
     */
    template <typename T>
    class Cascade : public Base_Filter<T> {
        private:
            std::vector<std::unique_ptr<Base_Filter<T>>> m_cascade;

        public:

            /**
             * @brief Default constructor of cascade objetc. Sets basic values.
             */
            Cascade() : Base_Filter<T>(44100.0, "Cascade") {}

            /**
             * @brief Parametric construcotr of cascade objet. 
             * @param sampling_freq Sampling frequency(double) of filtering system (mus be same for every stage).
             * @param cascade_name String name of cascade.
             */
            Cascade(double sampling_freq, std::string cascade_name) : Base_Filter<T>(sampling_freq, cascade_name) {}


            /**
             * @brief Cloning constructor - enables cloning of it's self.
             * @param other is an pointer to Cascade object.
             */
            Cascade(const Cascade& other) : Base_Filter<T>(other.get_sampling_freq(), other.get_filter_name()) {
                for (const auto& f : other.m_cascade) {
                    m_cascade.push_back(f->clone());
                }
            }

            /**
             * @brief Filtering function overriden from Base Filter. Allows to filter in cascade each sample.
             * @tparam Numerical input is signal sample given to the cascade.
             * @return Returns filtered samle in the same type as input.
             */
            T filter(T input) override{
                T output = input;

                for(auto& f : m_cascade){
                    output = f->filter(output);
                }

                return output;
            }

            /**
             * @brief Resets each filter in cascaden (internal filter memory reset)
             */
            void reset() override {
                for(auto& f : m_cascade){
                    f->reset();
                }
            }
            
            /**
             * @brief Method for adding filter to the cascade. Sampling frequency must be the same for each filter in cascade. Returns true if succesful, false. if negative.
             *  @param filter Any filter or cascade inheriting after Base Filter.
             *  @return Returns true if adding filter succesful. Otherwise retuns false.
             */
            bool add_filter(const Base_Filter<T>& filter) {
                if (filter.get_sampling_freq() == this->get_sampling_freq()) {
                    m_cascade.push_back(filter.clone());
                    return true;
                }

                return false;
            }
            
            /**
             * @brief Method for cloning it's self - cascade can be used to make bigger cascade
             * @return Returns unique pointer for new Cascade object.
             */
            std::unique_ptr<Base_Filter<T>> clone() const override {
               return std::make_unique<Cascade<T>>(*this);
            }
    };
        /**
         * @brief Overloaded operator "+" for case of adding two standalone filters.
         * @return Returns unique pointer at resulting cascade, after adding two filters.
         * * Every method for results of this operation has to be used on pointer (Cascade_bandpass->filter(s);).
         */     
        template<typename T>
        std::unique_ptr<Cascade<T>> operator+(const Base_Filter<T>& first, const Base_Filter<T>& second){
            auto casc = std::make_unique<Cascade<T>>(first.get_sampling_freq(), "Cascade");
            casc->add_filter(first);
            casc->add_filter(second);

            return casc;
        }

        /**
         * @brief Overloaded operator "+" for case of adding Cascade + filter.
         * @return Returns unique pointer at resulting cascade, after adding two filters.
         * * Every method for results of this operation has to be used on pointer (Cascade_bandpass->filter(s);).
         */   
        template<typename T>
        std::unique_ptr<Cascade<T>> operator+(const Cascade<T>& first, const Base_Filter<T>& second){
            first->add_filter(second);

            return first;
        }

        /**
         * @brief Overloaded operator "+" for case of adding two Cascades.
         * @return Returns unique pointer at resulting cascade, after adding two filters.
         * * Every method for results of this operation has to be used on pointer (Cascade_bandpass->filter(s);).
         */      
        template <typename T>
        std::unique_ptr<Cascade<T>> operator+(std::unique_ptr<Cascade<T>> lhs, std::unique_ptr<Cascade<T>> rhs) {
            lhs->add_filter(*rhs); 
            return lhs;
        }

        /**
         * @brief Overloaded operator "+" for case of adding filter + Cascade.
         * @return Returns unique pointer at resulting cascade, after adding two filters.
         * * Every method for results of this operation has to be used on pointer (Cascade_bandpass->filter(s);).
         */   
        template <typename T>
        std::unique_ptr<Cascade<T>> operator+(const Base_Filter<T>& lhs, std::unique_ptr<Cascade<T>> rhs) {
            auto casc = std::make_unique<Cascade<T>>(lhs.get_sampling_freq());
            casc->add_filter(lhs);
            casc->add_filter(*rhs);
            return casc;
        }

}