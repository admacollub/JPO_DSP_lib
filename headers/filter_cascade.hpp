#pragma once

#include "base_filter.hpp"

namespace af{
    template <typename T>
    class Cascade : public Base_Filter<T> {
        private:
            std::vector<std::unique_ptr<Base_Filter<T>>> m_cascade;

        public:

            Cascade() : Base_Filter<T>(44100.0, "Cascade") {}

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
             * @tparam input is signal sample given to the cascade.
             */
            T filter(T input) override{
                T output = input;

                for(auto& f : m_cascade){
                    output = f->filter(output);
                }

                return output;
            }

            /**
             * @brief resets each filter in cascaden (internal filter memory reset)
             */
            void reset() override {
                for(auto& f : m_cascade){
                    f->reset();
                }
            }
            
            /**
             * @brief Method for adding filter to the cascade. Sampling frequency must be the same for each filter in cascade. Returns true if succesful, false. if negative.
             *  @param filter Any filter or cascade inheriting after Base Filter.
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
             */
            std::unique_ptr<Base_Filter<T>> clone() const override {
               return std::make_unique<Cascade<T>>(*this);
            }
    };

        template<typename T>
        std::unique_ptr<Cascade<T>> operator+(const Base_Filter<T>& first, const Base_Filter<T>& second){
            auto casc = std::make_unique<Cascade<T>>(first.get_sampling_freq(), "Cascade");
            casc->add_filter(first);
            casc->add_filter(second);

            return casc;
        }

        template<typename T>
        std::unique_ptr<Cascade<T>> operator+(const Cascade<T>& first, const Base_Filter<T>& second){
            first->add_filter(second);

            return first;
        }

        template <typename T>
        std::unique_ptr<Cascade<T>> operator+(std::unique_ptr<Cascade<T>> lhs, std::unique_ptr<Cascade<T>> rhs) {
            lhs->add_filter(*rhs); 
            return lhs;
        }

        template <typename T>
        std::unique_ptr<Cascade<T>> operator+(const Base_Filter<T>& lhs, std::unique_ptr<Cascade<T>> rhs) {
            auto casc = std::make_unique<Cascade<T>>(lhs.get_sampling_freq());
            casc->add_filter(lhs);
            casc->add_filter(*rhs);
            return casc;
        }

}