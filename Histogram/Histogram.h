#pragma once

#include <Dataset/Dataset.h>
#include <cmath>
#include <numeric>

class Histogram{
    private:
        std::vector<uint_fast32_t> histFrequencies;
        std::vector<double> histValues;

        // size = número de bins
        uint_fast32_t size;
        double max;

    public:
        virtual ~Histogram() = default;

        void setHistValues(std::vector<double> histValues);
        const std::vector<double> &getHistValues() const;

        const std::vector<uint_fast32_t> &getHistFrequencies() const;

        double getMax() const;
        void setMax(double max);

        double getStandardDeviation() const;

        uint_fast32_t getBucketValue(const uint_fast32_t pos) const;

        void setHistogram(const std::vector<uint_fast32_t> &hist);
        const std::vector<uint_fast32_t> &getHistogram() const;

        uint_fast32_t getSize() const;
};
