#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

#include "comlex_number.h"

using namespace std;


class FileManager {
private:
string path;
public:
    vector <Сomplex<int>> signal;
    FileManager(const string& path = "") : path(path) {
        ifstream file(path, ios::binary);
        if (!file) {
            cout << "Не удалось открыть файл: " << path << endl;
            return;
        }
        cout << "Удалось открыть файл: " << path << endl;

        Сomplex<int> value;
        while (file.read(reinterpret_cast<char*>(&value), sizeof(int))) {
            signal.push_back(value); 
        }

        cout << "Данные успешно прочитаны." << endl;
        file.close();
    }
};


#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

class WavRecorder {
public:
    WavRecorder(const string& filename, int sampleRate, int numChannels)
        : filename_(filename), sampleRate_(sampleRate), numChannels_(numChannels) {}

    void record(const vector<int>& signal) {
        ofstream outputFile(filename_, ios::binary);
        if (!outputFile) {
            cout << "Ошибка открытия файла для записи!" << endl;
            return;
        }

        vector<int16_t> normalizedSignal = normalize(signal);

        writeWavHeader(outputFile, normalizedSignal.size());

        for (const int& sample : normalizedSignal) {
            int16_t sampleValue = static_cast<int16_t>(sample); 
            outputFile.write(reinterpret_cast<const char*>(&sampleValue), sizeof(sampleValue));
        }

        outputFile.close(); // Закрываем файл

        cout << "Сигнал записан в файл demodulated_signal.wav" << endl;
    }

private:
    std::string filename_;
    int sampleRate_;
    int numChannels_;

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
        }
        return normalizedSignal;
    }

    void writeWavHeader(std::ofstream& outputFile, size_t numSamples) {
        const int bitsPerSample = 16; // 16 бит на сэмпл
        const int byteRate = sampleRate_ * numChannels_ * bitsPerSample / 8;
        const int blockAlign = numChannels_ * bitsPerSample / 8;

        // Заголовок RIFF
        outputFile.write("RIFF", 4);
        uint32_t chunkSize = 36 + numSamples * blockAlign;
        outputFile.write(reinterpret_cast<const char*>(&chunkSize), sizeof(chunkSize));

        // Заголовок WAVE
        outputFile.write("WAVE", 4);

        // Заголовок fmt
        outputFile.write("fmt ", 4);
        uint32_t subChunk1Size = 16; // Размер подзаголовка fmt
        outputFile.write(reinterpret_cast<const char*>(&subChunk1Size), sizeof(subChunk1Size));
        uint16_t audioFormat = 1; // PCM
        outputFile.write(reinterpret_cast<const char*>(&audioFormat), sizeof(audioFormat));
        outputFile.write(reinterpret_cast<const char*>(&numChannels_), sizeof(numChannels_));
        outputFile.write(reinterpret_cast<const char*>(&sampleRate_), sizeof(sampleRate_));
        outputFile.write(reinterpret_cast<const char*>(&byteRate), sizeof(byteRate));
        outputFile.write(reinterpret_cast<const char*>(&blockAlign), sizeof(blockAlign));
        outputFile.write(reinterpret_cast<const char*>(&bitsPerSample), sizeof(bitsPerSample));

        // Заголовок data
        outputFile.write("data", 4);
        uint32_t subChunk2Size = numSamples * blockAlign;
        outputFile.write(reinterpret_cast<const char*>(&subChunk2Size), sizeof(subChunk2Size));
    }
};