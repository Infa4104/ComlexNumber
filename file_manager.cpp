// #pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdint>

#include <complex>

using namespace std;

template <typename T>
class FileManager {
private:
string path;
public:
    vector <complex<T>> signal;
    FileManager(const string& path = "") : path(path) {
        ifstream file(path, ios::binary);
        if (!file) {
            cout << "Не удалось открыть файл: " << path << endl;
            return;
        }
        cout << "Удалось открыть файл: " << path << endl;

        complex<T> value;
        while (file.read(reinterpret_cast<char*>(&value), sizeof(complex<T>))) {
            signal.push_back(value); 
        }

        cout << "Данные успешно прочитаны." << endl;
        file.close();
    }
};


struct WavHeader {
    char chunkId[4];
    uint32_t chunkSize;
    char format[4];
    char subchunk1Id[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char subchunk2Id[4];
    uint32_t subchunk2Size;
};

// template <typename T>
// class WavRecorder {
// public:
//     WavRecorder(const string& filename, int sampleRate, int numChannels)
//         : filename_(filename), sampleRate_(sampleRate), numChannels_(numChannels) {}

//     void record(const vector<T>& signal) {
//         ofstream outputFile(filename_, ios::binary);
//         if (!outputFile) {
//             cout << "Ошибка открытия файла для записи!" << endl;
//             return;
//         }

//         vector<int16_t> normalizedSignal = normalize(signal);

//         writeWavHeader(outputFile, normalizedSignal.size());

//         for (const int& sample : normalizedSignal) {
//             int16_t sampleValue = static_cast<int16_t>(sample); 
//             outputFile.write(reinterpret_cast<const char*>(&sampleValue), sizeof(sampleValue));
//         }

//         outputFile.close(); // Закрываем файл

//         cout << "Сигнал записан в файл: " << filename_ << endl;
//     }

// private:
//     string filename_;
//     int sampleRate_;
//     int numChannels_;

//     vector<int16_t> normalize(const vector<T>& signal) {
//         // Находим максимальное абсолютное значение
//         int maxAbsValue = 0;
//         for (const int& sample : signal) {
//             maxAbsValue = max(maxAbsValue, abs(sample));
//         }

//         // Нормализуем значения
//         vector<int16_t> normalizedSignal;
//         for (const T& sample : signal) {
//             if (maxAbsValue == 0) {
//                 normalizedSignal.push_back(0); // Если maxAbsValue равен 0, добавляем 0
//             } else {
//                 // Нормализуем и приводим к 16-битному значению
//                 int16_t normalizedValue = static_cast<int16_t>((sample * 32767) / maxAbsValue);
//                 normalizedSignal.push_back(normalizedValue);
//             }
//         }
//         return normalizedSignal;
//     }

//     void writeWavHeader(ofstream& outputFile, size_t numSamples) {
//         const int bitsPerSample = 16; // 16 бит на сэмпл
//         const int byteRate = sampleRate_ * numChannels_ * bitsPerSample / 8;
//         const int blockAlign = numChannels_ * bitsPerSample / 8;

//         // Заголовок RIFF
//         outputFile.write("RIFF", 4);
//         uint32_t chunkSize = 36 + numSamples * blockAlign;
//         outputFile.write(reinterpret_cast<const char*>(&chunkSize), sizeof(chunkSize));

//         // Заголовок WAVE
//         outputFile.write("WAVE", 4);

//         // Заголовок fmt
//         outputFile.write("fmt ", 4);
//         uint32_t subChunk1Size = 16; // Размер подзаголовка fmt
//         outputFile.write(reinterpret_cast<const char*>(&subChunk1Size), sizeof(subChunk1Size));
//         uint16_t audioFormat = 1; // PCM
//         outputFile.write(reinterpret_cast<const char*>(&audioFormat), sizeof(audioFormat));
//         outputFile.write(reinterpret_cast<const char*>(&numChannels_), sizeof(numChannels_));
//         outputFile.write(reinterpret_cast<const char*>(&sampleRate_), sizeof(sampleRate_));
//         outputFile.write(reinterpret_cast<const char*>(&byteRate), sizeof(byteRate));
//         outputFile.write(reinterpret_cast<const char*>(&blockAlign), sizeof(blockAlign));
//         outputFile.write(reinterpret_cast<const char*>(&bitsPerSample), sizeof(bitsPerSample));

//         // Заголовок data
//         outputFile.write("data", 4);
//         uint32_t subChunk2Size = numSamples * blockAlign;
//         outputFile.write(reinterpret_cast<const char*>(&subChunk2Size), sizeof(subChunk2Size));
//     }
// };