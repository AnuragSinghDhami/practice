#include<bits/stdc++.h>
using namespace std;

class Logger{

private:

    mutex logMutex;
    Logger(){
        cout << "Central Logger Initialized\n";
    }
    ~Logger() = default;

public:

    Logger(const Logger&) = delete;
    Logger& operator = (const Logger&) = delete;

    static Logger& getInstance(){
        static Logger instance;
        return instance;
    }

    void log(const string& level, const string& message){
        lock_guard<mutex> lock(logMutex);
        cout << "[" << level << "]" << message << endl;
    }
};

void networkHandler(){
    for(int i = 1; i <= 3; i++){
        Logger::getInstance().log("INFO", "Network connection " + to_string(i) + "established");
        this_thread::sleep_for(chrono::milliseconds(15));
    }
}

void databaseConnector() {
    Logger::getInstance().log("INFO", "Attempting database connection...");
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    Logger::getInstance().log("ERROR", "Database timeout after 20ms.");
    Logger::getInstance().log("INFO", "Retrying database connection...");
}

void authModule() {
    for (int i = 1; i <= 3; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        Logger::getInstance().log("WARNING", "Failed login attempt for user ID: " + std::to_string(i));
    }
}

int main(){
    cout << "Starting server simulating" << endl;

    thread t1(networkHandler);
    thread t2(databaseConnector);
    thread t3(authModule);

    t1.join();
    t2.join();
    t3.join();

    cout << "completed\n";
    return 0;


}
