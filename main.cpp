#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "file_manager.h"
#include "demodulators.h"

int main() {
    FileManager binFileManager("sound/am_sound.dat");
    WavRecorder recorder("demodulated_signal.wav", 32000, 1);
    DemodulatorAM demodulator;
    demodulator.receiveSignal(binFileManager.signal);
    recorder.record(demodulator.getDemodulatedSignal());
    return 0;
} 