#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "comlex_number.h"

using namespace std;



class Demodulator {
public:
    virtual ~Demodulator() = default;
    virtual void receiveSignal(vector<Сomplex<int>>& signal) = 0;
    virtual vector<int> getDemodulatedSignal() const = 0;
};

class DemodulatorAM : public Demodulator {
private:
    vector<int> demodulatedSignal;

public:
    void receiveSignal(vector<Сomplex<int>>& signal) override {
        demodulatedSignal.clear();
        for (size_t i = 0; i < signal.size();++i) {
            demodulatedSignal.push_back(signal.at(i).abs());
        }
        cout << "Сигнал успешно получен." << endl;
    }
    vector<int> getDemodulatedSignal() const override {
        return demodulatedSignal;
    }
};

