#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "file_manager.h"
#include "demodulators.h"

int main() {
    FileManager binFileManager("sound/file1EuropaPlus.bin");
    WavWriter writer("output.wav");
    DemodulatorAM demodulator;
    demodulator.receiveSignal(binFileManager.signal);

    for (const auto& value : demodulator.getDemodulatedSignal()) {
        writer.writeSample(value);
    }
    return 0;
} 