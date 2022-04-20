#include <MathFunctions/Math.h>

double MathFunctions::medianDistance(std::vector<double> distances){

    size_t size = distances.size();

    if ((size % 2) == 0){

        std::nth_element(distances.begin(), distances.begin()+(size/2)-1, distances.end());
        double firstValue = distances.operator []((size/2)-1);

        std::nth_element(distances.begin(), distances.begin()+(size/2), distances.end());
        double secondValue = distances.operator []((size/2));

        return (firstValue + secondValue)/2;

    } else {

        std::nth_element(distances.begin(), distances.begin()+(size/2), distances.end());
        return distances[size/2];
    }
}
