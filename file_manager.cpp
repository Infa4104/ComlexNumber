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
    vector <ComlexNumber> signal;
    FileManager(const string& path = "") : path(path) {
        ifstream file(path, ios::binary);
        if (!file) {
            cout << "Не удалось открыть файл: " << path << endl;
            return;
        }
        cout << "Удалось открыть файл: " << path << endl;
        string str{istreambuf_iterator<char>(file), istreambuf_iterator<char>()};
        for (size_t i = 0; i < str.size();i=i+2){
            int w = i + 1;
            signal.push_back(ComlexNumber(str[i],str[w]));
        }
        cout << "Данные успешно прочитаны." << endl;
        file.close();
    }
};
int main() {
    FileManager binFileManager("sound/file1EuropaPlus.bin"); 
}