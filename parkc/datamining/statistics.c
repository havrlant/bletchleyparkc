#include "statitics.h"

double deviation(double* arr1, double* arr2, size_t length) {
    double deviation = 0;
    for (size_t i = 0; i < length; i++) {
        deviation += pow(arr1[i] - arr2[i], 2);
    }
    return deviation;
}
