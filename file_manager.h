#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "comlex_number.h"

using namespace std;

// Заголовок WAV
struct WavHeader {
    char riff[4]; // "RIFF"
    int overall_size; // Размер файла - 8 байт + размер данных
    char wave[4]; // "WAVE"
    char fmt[4]; // "fmt "
    int fmt_length; // Длина формата
    int format_type; // Тип формата (1 - PCM)
    int channels; // Количество каналов
    int sample_rate; // Частота дискретизации
    int bytes_per_second; // Байты в секунду
    int block_align; // Размер блока
    int bits_per_sample; // Биты на выборку
    char data[4]; // "data"
    int data_size; // Размер данных
};


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
        string  str{istreambuf_iterator<char>(file), istreambuf_iterator<char>()};
        for (size_t i = 0; i < str.size();i=i+2){
            int w = i + 1;
            signal.push_back(Сomplex(int(str[i]),int(str[w])));
        }

        cout << "Данные успешно прочитаны." << endl;
        file.close();
    }
};

class WavWriter {
public:
    WavWriter(const string& filename, int sampleRate = 32000) : sampleRate(sampleRate) {
        outputFile.open(filename, ios::binary);
        if (!outputFile) {
            throw runtime_error("Ошибка открытия файла для записи");
        }
        writeWavHeader();
    }
    ~WavWriter() {
        writeWavFooter();
        outputFile.close();
    }

    void writeSample(const int& sample) {
        outputFile.write(reinterpret_cast<const char*>(&sample), sizeof(int));
    }
private:
    ofstream outputFile;
    int sampleRate;
    int dataSize = 0;

    void writeWavHeader() {
        // Запись заголовка WAV
        outputFile.write("RIFF", 4);
        int chunkSize = 36; // размер данных (заполнится позже)
        outputFile.write(reinterpret_cast<const char*>(&chunkSize), sizeof(int));
        outputFile.write("WAVE", 4);
        outputFile.write("fmt ", 4);
        
        int subChunk1Size = 16; // размер подчиненного чанка
        outputFile.write(reinterpret_cast<const char*>(&subChunk1Size), sizeof(int));
        
        int audioFormat = 3; // формат: 3 - IEEE Float
        outputFile.write(reinterpret_cast<const char*>(&audioFormat), sizeof(int));
        
        int numChannels = 1; // два канала (действительная и мнимая части)
        outputFile.write(reinterpret_cast<const char*>(&numChannels), sizeof(int));
        
        outputFile.write(reinterpret_cast<const char*>(&sampleRate), sizeof(int));
        
        int byteRate = sampleRate * numChannels * sizeof(float);
        outputFile.write(reinterpret_cast<const char*>(&byteRate), sizeof(int));
        
        int blockAlign = numChannels * sizeof(float);
        outputFile.write(reinterpret_cast<const char*>(&blockAlign), sizeof(int));
        
        int bitsPerSample = 32; // 32 бита на выборку
        outputFile.write(reinterpret_cast<const char*>(&bitsPerSample), sizeof(int));
        
        outputFile.write("data", 4);
        dataSize = 0; // будет обновлено позже
    }

    void writeWavFooter() {

        int chunkSize = dataSize + 36;
        outputFile.seekp(4, ios::beg);
        outputFile.write(reinterpret_cast<const char*>(&chunkSize), sizeof(int));
        
        outputFile.seekp(40, ios::beg);
        outputFile.write(reinterpret_cast<const char*>(&dataSize), sizeof(int));
    }
};