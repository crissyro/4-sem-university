#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void readOutputFile(const string& filename) {
    ifstream inputFile(filename, ios::binary);

    if (!inputFile) {
        cerr << "Ошибка открытия выходного файла!" << endl;
        return;
    }
    
    cout << "Числа в выходном файле: \n";

    int number;
    while (inputFile.read(reinterpret_cast<char*>(&number), sizeof(int))) 
        cout << number << endl;
    
    cout << endl;
    inputFile.close();
}

int main() {
    ifstream input("input_a.txt");
    ofstream output("output_a.bin", ios::binary);
    
    if (!input.is_open() || !output.is_open()) {
        cerr << "Ошибка открытия файлов!" << endl;
        return 1;
    }

    string line;
    while (getline(input, line)) {
        istringstream iss(line);
        int number, last_number;
        bool has_numbers = false;
        
        while (iss >> number) {
            last_number = number;
            has_numbers = true;
        }
        
        if (has_numbers) output.write(reinterpret_cast<char*>(&last_number), sizeof(int));
    }

    input.close();
    output.close();

    cout << "Файл успешно обработан!" << endl;
    
    readOutputFile("output.bin");
    
    return 0;
}
