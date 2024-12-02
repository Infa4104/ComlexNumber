#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <complex>

using namespace std;


template <typename T>
class Demodulator {
public:
    virtual ~Demodulator() = default;
    virtual void demodulation(vector<complex<int>>& signal) = 0;
    virtual vector<T> getDemodulatedSignal() const = 0;
};

class DemodulatorAM : public Demodulator<int> {
private:
    vector<int> demodulatedSignal;

public:
    void demodulation(vector<complex<int>>& signal) override {
        demodulatedSignal.clear();
        for (const complex<int>& sample : signal) {
            demodulatedSignal.push_back(abs(sample));
        }
        cout << "Сигнал AM успешно получен." << endl;
    }
    vector<int> getDemodulatedSignal() const override {
        return demodulatedSignal;
    }
};

class DemodulatorFM : public Demodulator<double> {
private:
    vector<double> demodulatedSignal;

public:
    void demodulation(vector<complex<int>>& signal) override {
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
