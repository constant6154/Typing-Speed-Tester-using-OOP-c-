#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <conio.h> // For non-blocking input (Windows only)

using namespace std;

struct LeaderboardEntry {
    string name;
    double wpm;
    double accuracy;
};

class SentenceGenerator {
private:
    vector<string> easySentences = {
        "The cat sits on the mat.",
        "I like to eat apples.",
        "C++ is fun to learn."
    };
    vector<string> mediumSentences = {
        "Programming requires logical thinking and practice.",
        "The quick brown fox jumps over the lazy dog.",
        "Typing fast improves productivity."
    };#include <iostream>
    #include <vector>
    #include <string>
    #include <fstream>
    #include <chrono>
    #include <cstdlib>
    #include <limits>
    #include <iomanip>
    #include <algorithm>
    #include <ctime>
    #include <sstream>
    #include <conio.h> // For non-blocking input (Windows only)
    
    using namespace std;
    
    struct LeaderboardEntry {
        string name;
        double wpm;
        double accuracy;
    };
    
    class SentenceGenerator {
    private:
        vector<string> easySentences = {
            "The cat sits on the mat.",
            "I like to eat apples.",
            "C++ is fun to learn."
        };
        vector<string> mediumSentences = {
            "Programming requires logical thinking and practice.",
            "The quick brown fox jumps over the lazy dog.",
            "Typing fast improves productivity."
        };
        vector<string> hardSentences = {
            "C++ templates provide a powerful mechanism for generic programming.",
            "Encapsulation and inheritance are key OOP principles.",
            "Multithreading in C++ can improve performance significantly."
        };
    public:
        string getSentence(int difficulty) {
            int index;
            switch (difficulty) {
                case 1:
                    index = rand() % easySentences.size();
                    return easySentences[index];
                case 2:
                    index = rand() % mediumSentences.size();
                    return mediumSentences[index];
                case 3:
                    index = rand() % hardSentences.size();
                    return hardSentences[index];
                default:
                    return "Invalid difficulty level!";
            }
        }
    };
    
    class TypingTester {
    private:
        vector<LeaderboardEntry> leaderboard;
        const string leaderboardFile = "leaderboard.txt";
    
        void saveLeaderboard() {
            ofstream file(leaderboardFile, ios::trunc);
            if (file.is_open()) {
                for (const auto& entry : leaderboard) {
                    file << entry.name << " " << entry.wpm << " " << entry.accuracy << "\n";
                }
                file.close();
            } else {
                cout << "Error: Unable to save leaderboard!" << endl;
            }
        }
    
        void loadLeaderboard() {
            leaderboard.clear();
            ifstream file(leaderboardFile);
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    stringstream ss(line);
                    LeaderboardEntry entry;
                    ss >> entry.name >> entry.wpm >> entry.accuracy;
                    leaderboard.push_back(entry);
                }
                file.close();
            } else {
                cout << "No previous leaderboard found, starting fresh.\n";
            }
        }
    
    public:
        TypingTester() {
            loadLeaderboard();
        }
    
        void displayLeaderboard() {
            cout << "\n===== Leaderboard =====\n";
            if (leaderboard.empty()) {
                cout << "No entries yet! Try completing a test.\n";
                return;
            }
            for (const auto& entry : leaderboard) {
                cout << "Name: " << entry.name << " | WPM: " << entry.wpm << " | Accuracy: " << entry.accuracy << "%\n";
            }
        }
    
        void updateLeaderboard(const string& name, double wpm, double accuracy) {
            for (auto& entry : leaderboard) {
                if (entry.name == name) {
                    entry.wpm = max(entry.wpm, wpm);
                    entry.accuracy = max(entry.accuracy, accuracy);
                    saveLeaderboard();
                    return;
                }
            }
            LeaderboardEntry newEntry = {name, wpm, accuracy};
            leaderboard.push_back(newEntry);
            saveLeaderboard();
        }
    
        void startTest(const string& sentence, const string& userName, bool isTimed = false, int timeLimit = 0) {
            cout << "\nType the following:\n\"" << sentence << "\"\n";
            auto start = chrono::high_resolution_clock::now();
            cin.ignore();
            string userInput;
            if (isTimed) {
                cout << "You have " << timeLimit << " seconds. Start typing:\n";
                auto endTime = start + chrono::seconds(timeLimit);
                while (chrono::high_resolution_clock::now() < endTime) {
                    if (_kbhit()) {
                        char ch = _getch();
                        if (ch == '\r') break;
                        userInput += ch;
                        cout << ch;
                    }
                }
                cout << "\nTime's up!\n";
            } else {
                getline(cin, userInput);
            }
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;
            double timeInMinutes = elapsed.count() / 60.0;
            double wpm = count(sentence.begin(), sentence.end(), ' ') / timeInMinutes;
    
            int correct = 0;
            for (size_t i = 0; i < min(sentence.size(), userInput.size()); ++i) {
                if (sentence[i] == userInput[i]) correct++;
            }
            double accuracy = (double(correct) / sentence.size()) * 100;
    
            updateLeaderboard(userName, wpm, accuracy);
            cout << fixed << setprecision(2) << "\nWPM: " << wpm << "\nAccuracy: " << accuracy << "%\n";
        }
    };
    
    int main() {
        srand(time(0));
        SentenceGenerator generator;
        TypingTester tester;
        string userName;
        int choice, difficulty, timeLimit;
    
        cout << "Enter your name: ";
        cin >> userName;
        do {
            cout << "\n1. Typing Test (Easy, Medium, Hard)\n2. Typing Test (Timed - Custom Time)\n3. View Leaderboard\n4. Exit\nEnter choice: ";
            cin >> choice;
            if (choice == 1) {
                cout << "Choose difficulty (1 - Easy, 2 - Medium, 3 - Hard): ";
                cin >> difficulty;
                tester.startTest(generator.getSentence(difficulty), userName);
            } else if (choice == 2) {
                cout << "Enter time limit in seconds: ";
                cin >> timeLimit;
                tester.startTest(generator.getSentence(2), userName, true, timeLimit);
            } else if (choice == 3) {
                tester.displayLeaderboard();
            }
        } while (choice != 4);
        return 0;
    }
    
            case 3:
                index = rand() % hardSentences.size();
                return hardSentences[index];
            default:
                return "Invalid difficulty level!";
        }
    }
};

class TypingTester {
private:
    vector<LeaderboardEntry> leaderboard;
    const string leaderboardFile = "leaderboard.txt";

    void saveLeaderboard() {
        ofstream file(leaderboardFile, ios::trunc);
        if (file.is_open()) {
            for (const auto& entry : leaderboard) {
                file << entry.name << " " << entry.wpm << " " << entry.accuracy << "\n";
            }
            file.close();
        } else {
            cout << "Error: Unable to save leaderboard!" << endl;
        }
    }

    void loadLeaderboard() {
        leaderboard.clear();
        ifstream file(leaderboardFile);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                LeaderboardEntry entry;
                ss >> entry.name >> entry.wpm >> entry.accuracy;
                leaderboard.push_back(entry);
            }
            file.close();
        } else {
            cout << "No previous leaderboard found, starting fresh.\n";
        }
    }

public:
    TypingTester() {
        loadLeaderboard();
    }

    void displayLeaderboard() {
        cout << "\n===== Leaderboard =====\n";
        if (leaderboard.empty()) {
            cout << "No entries yet! Try completing a test.\n";
            return;
        }
        for (const auto& entry : leaderboard) {
            cout << "Name: " << entry.name << " | WPM: " << entry.wpm << " | Accuracy: " << entry.accuracy << "%\n";
        }
    }

    void updateLeaderboard(const string& name, double wpm, double accuracy) {
        for (auto& entry : leaderboard) {
            if (entry.name == name) {
                entry.wpm = max(entry.wpm, wpm);
                entry.accuracy = max(entry.accuracy, accuracy);
                saveLeaderboard();
                return;
            }
        }
        LeaderboardEntry newEntry = {name, wpm, accuracy};
        leaderboard.push_back(newEntry);
        saveLeaderboard();
    }

    void startTest(const string& sentence, const string& userName, bool isTimed = false, int timeLimit = 0) {
        cout << "\nType the following:\n\"" << sentence << "\"\n";
        auto start = chrono::high_resolution_clock::now();
        cin.ignore();
        string userInput;
        if (isTimed) {
            cout << "You have " << timeLimit << " seconds. Start typing:\n";
            auto endTime = start + chrono::seconds(timeLimit);
            while (chrono::high_resolution_clock::now() < endTime) {
                if (_kbhit()) {
                    char ch = _getch();
                    if (ch == '\r') break;
                    userInput += ch;
                    cout << ch;
                }
            }
            cout << "\nTime's up!\n";
        } else {
            getline(cin, userInput);
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        double timeInMinutes = elapsed.count() / 60.0;
        double wpm = count(sentence.begin(), sentence.end(), ' ') / timeInMinutes;

        int correct = 0;
        for (size_t i = 0; i < min(sentence.size(), userInput.size()); ++i) {
            if (sentence[i] == userInput[i]) correct++;
        }
        double accuracy = (double(correct) / sentence.size()) * 100;

        updateLeaderboard(userName, wpm, accuracy);
        cout << fixed << setprecision(2) << "\nWPM: " << wpm << "\nAccuracy: " << accuracy << "%\n";
    }
};

int main() {
    srand(time(0));
    SentenceGenerator generator;
    TypingTester tester;
    string userName;
    int choice, difficulty, timeLimit;

    cout << "Enter your name: ";
    cin >> userName;
    do {
        cout << "\n1. Typing Test (Easy, Medium, Hard)\n2. Typing Test (Timed - Custom Time)\n3. View Leaderboard\n4. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Choose difficulty (1 - Easy, 2 - Medium, 3 - Hard): ";
            cin >> difficulty;
            tester.startTest(generator.getSentence(difficulty), userName);
        } else if (choice == 2) {
            cout << "Enter time limit in seconds: ";
            cin >> timeLimit;
            tester.startTest(generator.getSentence(2), userName, true, timeLimit);
        } else if (choice == 3) {
            tester.displayLeaderboard();
        }
    } while (choice != 4);
    return 0;
}
