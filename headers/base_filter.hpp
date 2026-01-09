#define _USE_MATH_DEFINES

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

namespace af{

    /**
     *@brief Abstract base class for all filters and cascades of filters.
     ** Class holds parameters: sampling freqency (double) and name of the filter/cascade (string).
     *@tparam  T is the type of data, which the filters will operate on.
     */
    template <typename T>
    class Base_Filter {
    private:
        double m_sampling_freq;
        std::string m_filter_name;

    public:
        /**
         * @brief Virtual method for filtering/processing samples.
         * @tparam T is the type of datam that will be filtered
         */
        virtual T filter(T input) = 0;

        /**
         * @brief Virtual method for reseting the state of filter.
         */
        virtual void reset() = 0;

        /**
         * @brief Parametric constructor of base class.
         * @param sampling_freq Sampling Frequency of the provided data. Cannot be 0 or less.
         * @param filter_name Name of filter or cascade of filters. Cannot be "".
         */
        Base_Filter(double sampling_freq, std::string filter_name)
        {
            set_sampling_freq(sampling_freq);
            set_filter_name(filter_name);
        }

        /**
         * @brief Overloaded constructor with default parameters.
         */
        Base_Filter() : Base_Filter(44100.0, "Filter") {}

        /**
         * @brief Virtual destructor of base filter class
         */
        virtual ~Base_Filter() = default;

        /**
         * @brief Overloaded parametric constructor - only sampling frequency will suffice.
         * @param sampling_frequency Double sampling frequeny input.
         */
        Base_Filter(double sampling_freq) : Base_Filter(sampling_freq, "Filter") {}

        /**
         * @brief Setter of samplig frequency parameter in base filter class. Returns true if setting suuccesful, otherwise false.
         * @param sampling_freq Double sampling frequency of filter or cascade of filters.
         */
        bool set_sampling_freq(double sampling_freq)
        {
            if (sampling_freq > 0)
            {
                m_sampling_freq = sampling_freq;
                return true;
            }
            
            return false;
        }

        /**
         * @brief Setter of filter or cascade name. Returns true if succesful, otherwise false.
         * @param filter_name String input of filter name.
         */
        bool set_filter_name(std::string filter_name)
        {
            if (filter_name != "")
            {
                m_filter_name = filter_name;
                return true;
            }
            else
            {
                return false;
            }
        }

        /**
         * @brief Getter of sampling frequency of base structure. Returns double.
         */
        double get_sampling_freq() const
        {
            return m_sampling_freq;
        }

        /**
         * @brief Getter of base class filter name. Returns string.
         */
        std::string get_filter_name() const
        {
            return m_filter_name;
        }
    };

};