#include <iostream>
#include <vector>
#include <memory>
#include <queue>

using namespace std;

#include "file_manager.cpp"

vector<double> downsample(const vector<double>& signal, int factor) {
    if (factor <= 0) {
        throw invalid_argument("Factor must be greater than 0");
    }
    vector<double> downsampledSignal;
    for (size_t i = 0; i < signal.size(); i += factor) {
        downsampledSignal.push_back(signal[i]);
    }
    return downsampledSignal;
}


class Demodulator {
public:
    virtual ~Demodulator() = default;
    virtual void receiveSignal(const std::vector<double>& signal) = 0;
    virtual vector<double> getDemodulatedSignal() const = 0;
};

class DemodulatorFM : public Demodulator {
private:
    vector<double> demodulatedSignal;

public:
    void receiveSignal(const vector<double>& signal) override {
        demodulatedSignal.clear();
        for (size_t i = 1; i < signal.size(); ++i) {
            double demodulatedValue = signal[i] - signal[i - 1];
            demodulatedSignal.push_back(demodulatedValue);
        }
    }

    vector<double> getDemodulatedSignal() const override {
        return demodulatedSignal;
    }
};

class DemodulatorAM : public Demodulator {
private:
    vector<double> demodulatedSignal;

public:
    void receiveSignal(const vector<double>& signal) override {
        demodulatedSignal.clear();
        for (const auto& value : signal) {
            demodulatedSignal.push_back(value);
        }
    }
    vector<double> getDemodulatedSignal() const override {
        return demodulatedSignal;
    }
};


enum class FilterType {
    Recursive,
    NonRecursive
};

class Filter {
public:
    Filter(FilterType type, size_t windowSize)
        : type(type), windowSize(windowSize), sum(0.0), count(0) {
        if (type == FilterType::Recursive) {
            // Для рекурсивного фильтра
            prevValue = 0.0; // Начальное значение для рекурсивного фильтра
        }
    }

    double apply(double input) {
        if (type == FilterType::NonRecursive) {
            return nonRecursiveFilter(input);
        } else {
            return recursiveFilter(input);
        }
    }

private:
    FilterType type;
    size_t windowSize;
    double sum;
    size_t count;
    std::queue<double> values; // Для хранения значений в нерекурсивном фильтре
    double prevValue; // Для хранения предыдущего значения в рекурсивном фильтре

    double nonRecursiveFilter(double input) {
        // Добавляем новое значение в очередь
        values.push(input);
        sum += input;
        count++;

        // Если количество значений превышает размер окна, удаляем старое значение
        if (count > windowSize) {
            sum -= values.front();
            values.pop();
            count--;
        }

        // Возвращаем среднее значение
        return sum / count;
    }

    double recursiveFilter(double input) {
        // Рекурсивный фильтр: y[n] = (1/N) * x[n] + (N-1)/N * y[n-1]
        double output = (input / windowSize) + ((windowSize - 1) / static_cast<double>(windowSize)) * prevValue;
        prevValue = output; // Обновляем предыдущее значение
        return output;
    }
};


class WavWriter {
public:
    WavWriter(const std::string& filename, int sampleRate)
        : sampleRate(sampleRate), numChannels(1) {
        file.open(filename, std::ios::binary);
        writeHeader();
    }

    ~WavWriter() {
        writeDataSize();
        file.close();
    }

    void writeSample(double sample) {
        int16_t intSample = static_cast<int16_t>(sample * 32767); // Преобразование в 16-битный формат
        file.write(reinterpret_cast<const char*>(&intSample), sizeof(int16_t));
    }

private:
    std::ofstream file;
    int sampleRate;
    int numChannels;
    long dataSize = 0;

    void writeHeader() {
        file.write("RIFF", 4);
        file.write(reinterpret_cast<const char*>(&dataSize), sizeof(long)); // Placeholder for data size
        file.write("WAVE", 4);
        file.write("fmt ", 4);
        
        uint32_t fmtChunkSize = 16; // Размер fmt блока
        uint16_t audioFormat = 1; // PCM
        uint16_t bitsPerSample = 16; // 16 бит на выборку
        uint16_t blockAlign = numChannels * bitsPerSample / 8; // Выравнивание блока

        file.write(reinterpret_cast<const char*>(&fmtChunkSize), sizeof(fmtChunkSize));
        file.write(reinterpret_cast<const char*>(&audioFormat), sizeof(audioFormat));
        file.write(reinterpret_cast<const char*>(&numChannels), sizeof(numChannels));
        file.write(reinterpret_cast<const char*>(&sampleRate), sizeof(sampleRate));
        file.write(reinterpret_cast<const char*>(&blockAlign), sizeof(blockAlign));
        file.write(reinterpret_cast<const char*>(&bitsPerSample), sizeof(bitsPerSample));
        
        file.write("data", 4);
        dataSize = 0; // Изначально размер данных равен 0
        file.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize)); // Placeholder для размера данных
    }

    void writeDataSize() {
        long currentPos = file.tellp();
        file.seekp(4, std::ios::beg);
        long fileSize = currentPos - 8; // Общий размер файла - 8 байт для RIFF заголовка
        file.write(reinterpret_cast<const char*>(&fileSize), sizeof(fileSize));

        file.seekp(40, std::ios::beg);
        dataSize = currentPos - 44; // Размер данных - текущая позиция - 44 байта заголовка
        file.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));
    }
};
