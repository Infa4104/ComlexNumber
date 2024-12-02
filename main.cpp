#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <complex>

#include "file_manager.h"
#include "demodulators.h"
#include "filter.h"

int main() {
    FileManager<int> file_manager_dat("sound/am_sound.dat");
    WavRecorder<int> recorder_am("signal/am_demodulated_signal.wav", 32000, 1);
    DemodulatorAM demodulator_am;
    demodulator_am.demodulation(file_manager_dat.signal);
    recorder_am.record(demodulator_am.getDemodulatedSignal());

    FileManager<int> file_manager_bin("sound/fm_sound.bin");
    WavRecorder<double> recorder_fm("signal/fm_demodulated_signal.wav", 500000000, 1);
    DemodulatorFM demodulator_fm;
    demodulator_fm.demodulation(file_manager_bin.signal);
    vector<double> filtered_signal = filter((demodulator_fm.getDemodulatedSignal()),5);
    vector<double> downsampled_signal = downsample(filtered_signal,5);
    recorder_fm.record(downsampled_signal);
    return 0;
} 