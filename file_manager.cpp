#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "comlex_number.cpp"

using namespace std;

class FileManager {
private:
string path;
public:
    vector <ComlexNumber> data;
    FileManager(const string& path = "") : path(path) {
        ifstream file(path, ios::binary);
        if (!file) {
            cout << "Не удалось открыть файл: " << path << endl;
            return;
        }
        cout << "Удалось открыть файл: " << path << endl;

        vector<char> buffer;
        char byte;
        while (file.get(byte)) {
            buffer.push_back(byte);
        }
        for (size_t i = 0; i < buffer.size(); ++i) {
            data.push_back(ComlexNumber(buffer[i],buffer[++i]));
        }
        cout << "Данные успешно прочитаны." << endl;
    }
};
int main() {
    FileManager binFileManager("sound/file1EuropaPlus.bin"); 
    for (size_t i = 0; i < 200; ++i){
        cout << binFileManager.data[i].Conj() << endl;
    }
}