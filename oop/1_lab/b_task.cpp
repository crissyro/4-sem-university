#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void processFile(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile, ios::binary);
    if (!inFile) {
        cerr << "Ошибка открытия входного файла! Попробуйте создать input.bin" << endl;
        return;
    }

    ofstream outFile(outputFile, ios::binary);
    if (!outFile) {
        cerr << "Ошибка открытия выходного файла!" << endl;
        return;
    }

    vector<int> sequence;
    int number;
    bool hasData = false;

    while (inFile.read(reinterpret_cast<char*>(&number), sizeof(int))) {
        hasData = true;
        if (number == 0) {

            int firstNeg = -1, secondNeg = -1;

            for (size_t i = 0; i < sequence.size(); ++i) {
                if (sequence[i] < 0) {
                    if (firstNeg == -1) firstNeg = i;

                    else {
                        secondNeg = i;
                        break;
                    }
                }
            }

            if (firstNeg != -1 && secondNeg != -1) {
                for (size_t i = 0; i <= firstNeg; ++i) 
                    outFile.write(reinterpret_cast<char*>(&sequence[i]), sizeof(int));
                
                for (size_t i = secondNeg; i < sequence.size(); ++i) 
                    outFile.write(reinterpret_cast<char*>(&sequence[i]), sizeof(int));
                
                int delimiter = 0;
                outFile.write(reinterpret_cast<char*>(&delimiter), sizeof(int));
            }
            sequence.clear();
        } else sequence.push_back(number);  
    }

    if (!sequence.empty()) {
        int firstNeg = -1, secondNeg = -1;

        for (size_t i = 0; i < sequence.size(); ++i) {
            if (sequence[i] < 0) {
                if (firstNeg == -1) firstNeg = i;

                else {
                    secondNeg = i;
                    break;
                }
            }
        }

        if (firstNeg != -1 && secondNeg != -1) {
            for (size_t i = 0; i <= firstNeg; ++i) 
                outFile.write(reinterpret_cast<char*>(&sequence[i]), sizeof(int));
            
            for (size_t i = secondNeg; i < sequence.size(); ++i) 
                outFile.write(reinterpret_cast<char*>(&sequence[i]), sizeof(int));
            
            int delimiter = 0;
            outFile.write(reinterpret_cast<char*>(&delimiter), sizeof(int));
        }
    }

    inFile.close();
    outFile.close();

    if (!hasData) cerr << "Файл пуст или повреждён!" << endl;
}

void readOutputFile(const string& filename) {
    ifstream inputFile(filename, ios::binary);
    if (!inputFile) {
        cerr << "Ошибка открытия выходного файла!" << endl;
        return;
    }

    cout << "Числа в выходном файле: \n";
    int number;
    while (inputFile.read(reinterpret_cast<char*>(&number), sizeof(int))) {
        if (number == 0) cout << endl;

        else cout << number << ' ';
    }
    
    cout << endl;

    inputFile.close();
}

void createTestFile(const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Ошибка создания тестового файла!" << endl;
        return;
    }

    int testData[] = {3, 5, -2, 8, 7, -6, 4, 0,
                      1, 2, 3, 4, 5, 0,
                      -1, 10, 20, -3, 30, 0,
                      6, -5, 7, -8, 9, 0};

    outFile.write(reinterpret_cast<char*>(testData), sizeof(testData));
    outFile.close();

    cout << "Тестовый файл создан: " << filename << endl;
}

int main() {
    string inputFile = "input.bin";
    string outputFile = "output.bin";

    createTestFile(inputFile);  
    processFile(inputFile, outputFile);

    cout << "Файл успешно обработан!" << endl;

    readOutputFile(outputFile);

    return 0;
}
