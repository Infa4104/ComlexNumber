// #include <iostream>

// #include "comlex_number.cpp"

// int main() {

//   // double phase = 3.141;

//   // ICreatorComplexNumber* creator = new CreatorComplexNumberFromPhaseRadians();

//   // ComlexNumber* cn1 = creator->createComplexNumber(phase);

//   // cout << cn1->Conj() << endl;
  
//   // creator = new CreatorComplexNumberFromPhaseDegree();

//   // ComlexNumber* cn2 = creator->createComplexNumber(phase);

//   // cout << cn2->Conj() << endl;

//   // exit(0);
//   return 0;
// }


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
class FileManager {
public:
    FileManager(const std::string& filename) : filename(filename) {}
    void readBinFile() {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Не удалось открыть файл: " << filename << std::endl;
            return;
        }
        std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::cout << "Содержимое бинарного файла " << filename << ": " << std::endl;
        for (const char& byte : buffer) {
            std::cout << static_cast<int>(byte) << " ";
        }
        std::cout << std::endl;
    }
    void readDatFile() {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Не удалось открыть файл: " << filename << std::endl;
            return;
        }
        std::string line;
        std::cout << "Содержимое текстового файла " << filename << ": " << std::endl;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
    }
private:
    std::string filename;
};
int main() {
    // FileManager binFileManager(".bin"); // Укажите имя вашего бинарного файла
    // binFileManager.readBinFile();
    FileManager datFileManager("am_sound.dat"); // Укажите имя вашего текстового файла
    datFileManager.readDatFile();
    return 0;
}