#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <complex>
#include <stdio.h>
#include "file_manager.h"
#include "demodulators.h"
#include "filter.h"



int main() {
    FileManager<uint32_t> file_manager_dat("sound/am_sound.dat");
    DemodulatorAM demodulator_am;
    demodulator_am.demodulation(file_manager_dat.signal);
    vector<float> signal = normalized(demodulator_am.getDemodulatedSignal());

    WavHeader header;


    strcpy(header.chunkId, "RIFF");
    strcpy(header.format, "WAVE");
    strcpy(header.subchunk1Id, "fmt ");
    strcpy(header.subchunk2Id, "data");    
    header.chunkSize = 36 + 16000 * 26 * 2;
    header.subchunk1Size = 16;
    header.audioFormat = 1;
    header.numChannels = 1;
    header.sampleRate = 16000;
    header.byteRate = 2;        
    header.bitsPerSample = 16;
    header.subchunk2Size = 16000 * 26 * 2;
    
    FILE *file = fopen("signal/am_demodulated_signal.wav","wb");
    fwrite(&header,sizeof(header),1,file);

    for (size_t i = 0; i < signal.size(); ++i){
        fwrite(&signal[i],sizeof(signal[i]),1,file);
    }

    fclose(file);
    // WavRecorder<float> recorder_am("signal/am_demodulated_signal.wav", 32000, 1);
    // DemodulatorAM demodulator_am;
    // demodulator_am.demodulation(file_manager_dat.signal);
    // recorder_am.record(signal);

    // FileManager<int> file_manager_bin("sound/fm_sound.bin");
    // WavRecorder<double> recorder_fm("signal/fm_demodulated_signal.wav", 500000000, 1);
    // DemodulatorFM demodulator_fm;
    // demodulator_fm.demodulation(file_manager_bin.signal);
    // vector<double> filtered_signal = filter((demodulator_fm.getDemodulatedSignal()),5);
    // vector<double> downsampled_signal = downsample(filtered_signal,5);
    // recorder_fm.record(downsampled_signal);
    // return 0;
} 

// #include <iostream>
// #include <fstream>
// #include <cmath>
// #include <vector>

// const int SAMPLE_RATE = 44100; // Частота дискретизации
// const int DURATION = 5;         // Длительность в секундах
// const double FREQUENCY = 440.0; // Частота сигнала (Гц)

// struct WavHeader {
//     char riff[4];        // "RIFF"
//     int overall_size;    // Размер файла
//     char wave[4];       // "WAVE"
//     char fmt[4];        // "fmt "
//     int fmt_length;     // Длина формата
//     short format_type;  // Тип формата (1 - PCM)
//     short channels;      // Количество каналов
//     int sample_rate;    // Частота дискретизации
//     int byte_rate;      // Битрейт
//     short block_align;  // Размер блока
//     short bits_per_sample; // Бит на сэмпл
//     char data[4];       // "data"
//     int data_size;      // Размер данных
// };

// int main() {
//     // Создаем WAV заголовок
//     WavHeader header;
//     memcpy(header.riff, "RIFF", 4);
//     memcpy(header.wave, "WAVE", 4);
//     memcpy(header.fmt, "fmt ", 4);
//     header.fmt_length = 16;
//     header.format_type = 1; // PCM
//     header.channels = 1;     // Моно
//     header.sample_rate = SAMPLE_RATE;
//     header.bits_per_sample = 16;
//     header.byte_rate = SAMPLE_RATE * header.channels * (header.bits_per_sample / 8);
//     header.block_align = header.channels * (header.bits_per_sample / 8);
    
//     memcpy(header.data, "data", 4);
    
//     // Генерация демодулированного AM сигнала
//     int total_samples = SAMPLE_RATE * DURATION;
//     std::vector<short> samples(total_samples);
    
//     for (int i = 0; i < total_samples; ++i) {
//         double time = static_cast<double>(i) / SAMPLE_RATE;
//         samples[i] = static_cast<short>(32767.0 * 0.5 * sin(2.0 * M_PI * FREQUENCY * time)); // Уменьшение амплитуды до 0.5
//     }

//     // Запись в WAV файл
//     std::ofstream file("demodulated_signal.wav", std::ios::binary);
    
//     header.data_size = total_samples * sizeof(short);
//     header.overall_size = sizeof(WavHeader) - 8 + header.data_size;

//     file.write(reinterpret_cast<const char*>(&header), sizeof(WavHeader));
//     file.write(reinterpret_cast<const char*>(samples.data()), samples.size() * sizeof(short));
    
//     file.close();

//     std::cout << "Запись завершена: demodulated_signal.wav" << std::endl;

//     return 0;
// }
