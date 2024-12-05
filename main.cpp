#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <complex>

#include "file_manager.h"
#include "demodulators.h"
#include "filter.h"


vector<int16_t> normalize(const vector<int>& signal) {
    // Находим максимальное абсолютное значение
    int maxAbsValue = 0;
    for (const int& sample : signal) {
        maxAbsValue = max(maxAbsValue, abs(sample));
    }

    // Нормализуем значения
    vector<int16_t> normalizedSignal;
    for (const int& sample : signal) {
        if (maxAbsValue == 0) {
            normalizedSignal.push_back(0); // Если maxAbsValue равен 0, добавляем 0
        } else {
            // Нормализуем и приводим к 16-битному значению
            int16_t normalizedValue = static_cast<int16_t>((sample * 32767) / maxAbsValue);
            normalizedSignal.push_back(normalizedValue);
        }
    };
    return normalizedSignal;
};

int main() {
    WavHeader header;
    DemodulatorAM demodulator_am;

    FileManager<int> file_manager_dat("sound/am_sound.dat");

    strcpy(header.chunkId, "RIFF");
    strcpy(header.format, "WAVE");
    strcpy(header.subchunk1Id, "fmt ");
    strcpy(header.subchunk2Id, "data");    
    header.chunkSize = 36 + 32000 * 15 * 2;
    header.subchunk1Size = 16;
    header.audioFormat = 1;
    header.numChannels = 1;
    header.sampleRate = 32000;
    header.byteRate = 2;        
    header.bitsPerSample = 16;
    header.subchunk2Size = 32000 * 15 * 2;
    
    FILE *file = fopen("signal/am_demodulated_signal.wav","wb");
    


    demodulator_am.demodulation(file_manager_dat.signal);

    vector<int16_t> signal = normalize(demodulator_am.getDemodulatedSignal());

    for (size_t i = 0; i < signal.size(); ++i) 
        fwrite(&signal[i],sizeof(signal[i]),1,file);


    fwrite(&header,sizeof(header),1,file);


    fclose(file);
    // FileManager<int> file_manager_dat("sound/am_sound.dat");
    // WavRecorder<int> recorder_am("signal/am_demodulated_signal.wav", 32000, 1);
    // DemodulatorAM demodulator_am;
    // demodulator_am.demodulation(file_manager_dat.signal);
    // recorder_am.record(demodulator_am.getDemodulatedSignal());

    // FileManager<int> file_manager_bin("sound/fm_sound.bin");
    // WavRecorder<double> recorder_fm("signal/fm_demodulated_signal.wav", 500000000, 1);
    // DemodulatorFM demodulator_fm;
    // demodulator_fm.demodulation(file_manager_bin.signal);
    // vector<double> filtered_signal = filter((demodulator_fm.getDemodulatedSignal()),5);
    // vector<double> downsampled_signal = downsample(filtered_signal,5);
    // recorder_fm.record(downsampled_signal);
    // return 0;
} 