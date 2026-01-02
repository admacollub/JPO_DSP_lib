#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace af
{
    /**
     *@brief Abstract base class for all filters and cascades of filters.
     ** Class holds parameters: sampling freqency and name of the filter/cascade.
     *@tparam  T is the type of data, which the filters will operate on.
     */

    template <typename T>
    class Base_Filter
    {
    private:
        double m_sampling_freq;
        std::string m_filter_name;

    public:
        /**
         * @brief Default constructor of base class.
         * Sets base sampling frequency at 44100 Hz (audio standard).
         */
        Base_Filter() : m_sampling_freq(44100.0), m_filter_name("Filter") {}

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

        bool set_sampling_freq(double sampling_freq)
        {
            if (m_sampling_freq > 0)
            {
                m_sampling_freq = sampling_freq;
                return true;
            }
            else
            {
                reutrn false;
            }
        }

        bool set_filter_name(std::string filter_name)
        {
            if (filter_name != "")
                m_filter_name = filter_name;
            return true;
            else
            {
                return false;
            }
        }

        void get_sampling_freq() const {}

        void get_filter_name() const {}
    }

};