#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<double> filter(const vector<double>& signal, int window_size) {
    if (window_size <= 0) {
        throw invalid_argument("Размер окна должно быть положительным числом");
    }
    if (window_size > signal.size()) {
        throw invalid_argument("Размер окна должно быть меньше размера сигнала");
    }
    vector<double> filtered_signal;

    for (size_t i = 0; i <= signal.size() - window_size; ++i) {
        double sum = 0.0;
        for (int j = 0; j < window_size; ++j) {
            sum += signal[i + j];
        }
        filtered_signal.push_back(sum / window_size);
    }

    return filtered_signal;
}

vector<int> downsample(const vector<int>& signal, int factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Фактор должно быть положительным числом");
    }

    vector<int> downsampledSignal;

    for (size_t i = 0; i < signal.size(); i += factor) {
        downsampledSignal.push_back(signal[i]);
    }

    return downsampledSignal;
}

vector<double> downsample(const vector<double>& signal, int factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Фактор должно быть положительным числом");
    }

    vector<double> downsampledSignal;

    for (size_t i = 0; i < signal.size(); i += factor) {
        downsampledSignal.push_back(signal[i]);
    }

    return downsampledSignal;
}