#pragma once

#include "base_filter.hpp"

namespace af{
    template <typename T>
    class FIR : public Base_Filter<T> {
        private:
            std::vector<T> m_coeff;
            std::vector<T> m_past_sample;
 
        public:

            FIR()

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
