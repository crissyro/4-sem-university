#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

class Message {
private:
    std::string username;
    std::string content;
    long long timestamp;

public:
    Message(const std::string& user, const std::string& msg, long long ts = 0): username(user), content(msg), 
        timestamp(ts ? ts : std::chrono::system_clock::now().time_since_epoch() / std::chrono::seconds(1)) {}

    const std::string getUsername() const { return username; }
    const std::string getContent() const { return content; }
    long long getTimestamp() const { return timestamp; }
    void setTimestamp(long long ts) { timestamp = ts; }
    void updateContent(const std::string& newContent) { content = newContent; }


    inline std::string serialize() const {
        return username + "|" + content + "|" + std::to_string(timestamp) + "\n";
    }

    static Message deserialize(const std::string& line) {
        std::istringstream ss(line);
        std::string parts[3];

        for(int i = 0; i < 3 && getline(ss, parts[i], '|'); i++);

        return Message(parts[0], parts[1], std::stoll(parts[2]));
    }

    inline void display() const {
        std::time_t time = timestamp;
        std::tm tm = *std::localtime(&time);
        std::cout << CYAN << "[" << std::put_time(&tm, "%d-%m-%Y %H:%M") << "] "
                  << GREEN << username << RESET << ": " << BLUE << content << RESET << std::endl;
    }
};

class Chat {
private:
    static const std::string CHAT_FILE_PATH;


};
