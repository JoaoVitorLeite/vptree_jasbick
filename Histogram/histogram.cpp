#include <Histogram/Histogram.h>

double Histogram::getStandardDeviation() const{

    const double mean = std::accumulate(histFrequencies.begin(), histFrequencies.end(), 0.0)/size;

    double standardDeviation = 0.0;
    for (uint_fast32_t i = 0; i < size; i++)
        standardDeviation += pow(getBucketValue(i) - mean, 2);

    return std::sqrt(standardDeviation/size);
}

void Histogram::setHistValues(std::vector<double> histValues){
    this->histValues = histValues;
}
const std::vector<double> &Histogram::getHistValues() const{
    return histValues;
}

const std::vector<uint_fast32_t> &Histogram::getHistFrequencies() const{
    return histFrequencies;
}

double Histogram::getMax() const{ return max; }

void Histogram::setMax(double max){
    this->max = max;
}

void Histogram::setHistogram(const std::vector<uint_fast32_t> &hist){
    histFrequencies = hist;
    size = histFrequencies.size();
}
const std::vector<uint_fast32_t> &Histogram::getHistogram() const{ return histFrequencies; }

uint_fast32_t Histogram::getBucketValue(const uint_fast32_t pos) const{ return histFrequencies[pos]; }

// size = número de bins
uint_fast32_t Histogram::getSize() const{ return size; }
