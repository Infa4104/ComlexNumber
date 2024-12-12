#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <complex>
#include <algorithm>


using namespace std;


vector<float> normalized(vector<uint32_t> signal){
    vector<float> normalizedSignal;
    uint32_t max = 0;

    for (size_t i = 0; i != signal.size(); i++){
        long value = static_cast<long>(signal[i]);
        if (abs(value) > max){
            max = abs(value);
        };
    }

    for (const uint32_t& sample : signal)
        normalizedSignal.push_back(static_cast<float>( sample )/max);
    cout << "Сигнал успешно нормализированный." << endl;
    return normalizedSignal;
}


template <typename T>
class Demodulator {
public:
    virtual ~Demodulator() = default;
    virtual void demodulation(vector<complex<uint32_t>>& signal) = 0;
    virtual vector<T> getDemodulatedSignal() const = 0;
};

class DemodulatorAM : public Demodulator<uint32_t> {
private:
    vector<uint32_t> demodulatedSignal;

public:
    void demodulation(vector<complex<uint32_t>>& signal) override {
        demodulatedSignal.clear();
        for (const complex<uint32_t>& sample : signal) {
            demodulatedSignal.push_back(sqrt(sample.real()*sample.real()+sample.imag()*sample.imag()));
        }
        cout << "Сигнал AM успешно получен." << endl;
    }
    vector<uint32_t> getDemodulatedSignal() const override {
        return demodulatedSignal;
    }
};

class DemodulatorFM : public Demodulator<double> {
private:
    vector<double> demodulatedSignal;

public:
    void demodulation(vector<complex<uint32_t>>& signal) override {
        demodulatedSignal.clear();
        for (size_t i = 1; i < signal.size(); ++i) {
            double phaseDifference = arg(signal[i]); - arg(signal[i - 1]);
            demodulatedSignal.push_back(phaseDifference);
        }
        cout << "Сигнал FM успешно получен." << endl;
    }
    vector<double> getDemodulatedSignal() const override {
        return demodulatedSignal;
    }
};