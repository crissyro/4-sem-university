#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>

#define CHAT_FILE "chat.txt"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

struct Message {
private:
    std::string username;
    std::string message;
    long long timestamp;

public:
    Message(const std::string& user, const std::string& msg) 
    : username(user), message(msg), timestamp(generateTimestamp()) {}

    Message(const std::string& user, const std::string& msg, long long ts)
    : username(user), message(msg), timestamp(ts) {}

    static long long generateTimestamp() {
        return std::chrono::system_clock::now().time_since_epoch() / std::chrono::seconds(1);
    }

    std::string formatTimestamp() const {
        std::time_t time = timestamp;
        std::tm tm = *std::localtime(&time);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y %H:%M"); 
        return oss.str();
    }

    std::string serialize() const {
        return username + "|" + message + "|" + std::to_string(timestamp) + "\n";
    }

    static Message deserialize(const std::string& line) {
        std::istringstream ss(line);
        std::string user, msg, timeStr;
        getline(ss, user, '|');
        getline(ss, msg, '|');
        getline(ss, timeStr, '|');
        return Message(user, msg, std::stoll(timeStr));  
    }

    std::string getUsername() const { return username; }
    std::string getMessage() const { return message; }
    long long getTimestamp() const { return timestamp; }

    void print() const {
        std::cout << CYAN << "[" << formatTimestamp() << "]" << RESET << " " 
                  << GREEN << username << RESET << ": " << BLUE << message << RESET << std::endl;
    }
};

void sendMessage(const std::string& username, const std::string& message) {
    std::ofstream outFile(CHAT_FILE, std::ios::app);

    if (!outFile) {
        std::cerr << RED << "Ошибка открытия файла чата!" << RESET << std::endl;
        return;
    }

    Message msg(username, message);
    outFile << msg.serialize();
    outFile.close();
}

std::vector<Message> readChat() {
    std::vector<Message> messages;
    std::ifstream inFile(CHAT_FILE);

    if (!inFile) {
        std::cerr << RED << "Ошибка открытия файла чата!" << RESET << std::endl;
        return messages;
    }

    std::string line;
    while (getline(inFile, line)) 
        messages.push_back(Message::deserialize(line));
    
    inFile.close();

    return messages;
}

void printMessages(const std::vector<Message>& messages) {
    if (messages.empty()) {
        std::cout << YELLOW << "Чат пуст!" << RESET << std::endl;
        return;
    }

    for (const auto& msg : messages) 
        msg.print();
}

void clearChat() {
    std::ofstream outFile(CHAT_FILE, std::ios::trunc);

    if (!outFile) {
        std::cerr << RED << "Ошибка очистки чата!" << RESET << std::endl;
        return;
    }

    outFile.close();
    std::cout << GREEN << "Чат очищен!" << RESET << std::endl;
}

void menu() {
    int choice;

    while (true) {
        std::cout << "\n" << YELLOW << "=== Файловый чат ===" << RESET << "\n";
        std::cout << GREEN << "1. Отправить сообщение" << RESET << "\n";
        std::cout << GREEN << "2. Прочитать чат" << RESET << "\n";
        std::cout << GREEN << "3. Очистить чат" << RESET << "\n";
        std::cout << GREEN << "4. Выйти" << RESET << "\n";
        std::cout << "Выберите действие: ";

        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::string username, message;
                std::cout << "Введите ваше имя: ";
                getline(std::cin, username);
                std::cout << "Введите сообщение: ";
                getline(std::cin, message);
                sendMessage(username, message);
                break;
            }
            case 2: {
                std::vector<Message> messages = readChat();
                printMessages(messages);
                break;
            }
            case 3: {
                clearChat();
                break;
            }
            case 4: {
                std::cout << GREEN << "Выход из чата...\n" << RESET;
                return; 
            }
            default: {
                std::cout << RED << "Некорректный выбор. Попробуйте снова.\n" << RESET;
                break;
            }
        }
    }
}

int main() {
    menu();
    
    return 0;
}
