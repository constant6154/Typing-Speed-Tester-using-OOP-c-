#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <algorithm> // For transform

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
            cerr << "Error: Unable to save leaderboard data.\n";
        }
    }

    void loadLeaderboard() {
        leaderboard.clear();
        ifstream file(leaderboardFile);
        if (file.is_open()) {
            LeaderboardEntry entry;
            while (file >> entry.name >> entry.wpm >> entry.accuracy) {
                leaderboard.push_back(entry);
            }
            file.close();
        } else {
            cerr << "Error: Unable to load leaderboard data.\n";
        }
    }

public:
    TypingTester() {
        loadLeaderboard();
    }

    void startTest(const string& sentence, const string& userName) {
        cout << "\nType the following sentence:\n";
        cout << "\"" << sentence << "\"\n";

        // Start timing
        auto start = chrono::high_resolution_clock::now();

        // Get user input
        string userInput;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        getline(cin, userInput);

        // End timing
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        // Calculate WPM
        int wordCount = countWords(sentence);
        double timeInMinutes = elapsed.count() / 60.0;
        double wpm = wordCount / timeInMinutes;

        // Calculate Accuracy
        double accuracy = calculateAccuracy(sentence, userInput);

        // Update Leaderboard
        updateLeaderboard(userName, wpm, accuracy);

        // Show Results
        cout << fixed << setprecision(2);
        cout << "\nTyping Speed: " << wpm << " WPM\n";
        cout << "Accuracy: " << accuracy << "%\n";
    }

    void displayLeaderboard() {
        cout << "\n--- Leaderboard ---\n";
        cout << setw(15) << "Name"
             << setw(10) << "WPM"
             << setw(12) << "Accuracy\n";
        cout << "--------------------------------------\n";
        for (const auto& entry : leaderboard) {
            cout << setw(15) << entry.name
                 << setw(10) << entry.wpm
                 << setw(10) << entry.accuracy << "%\n";
        }
    }

private:
    int countWords(const string& sentence) {
        if (sentence.empty()) return 0;
        int count = 1;
        for (char ch : sentence) {
            if (ch == ' ') count++;
        }
        return count;
    }

    double calculateAccuracy(const string& original, const string& typed) {
        string originalLower = original, typedLower = typed;
        transform(originalLower.begin(), originalLower.end(), originalLower.begin(), ::tolower);
        transform(typedLower.begin(), typedLower.end(), typedLower.begin(), ::tolower);

        int correct = 0;
        int total = originalLower.size();
        for (size_t i = 0; i < originalLower.size() && i < typedLower.size(); ++i) {
            if (originalLower[i] == typedLower[i]) correct++;
        }
        return (double(correct) / total) * 100;
    }

    void updateLeaderboard(const string& name, double wpm, double accuracy) {
        for (auto& entry : leaderboard) {
            if (entry.name == name) {
                if (wpm > entry.wpm) entry.wpm = wpm;
                if (accuracy > entry.accuracy) entry.accuracy = accuracy;
                saveLeaderboard();
                return;
            }
        }
        leaderboard.push_back({name, wpm, accuracy});
        saveLeaderboard();
    }
};

int main() {
    SentenceGenerator generator;
    TypingTester tester;

    int choice;
    string userName;

    cout << "Enter your name: ";
    cin >> userName;

    do {
        cout << "\n--- Typing Speed Tester ---\n";
        cout << "1. Start Test (Easy)\n";
        cout << "2. Start Test (Medium)\n";
        cout << "3. Start Test (Hard)\n";
        cout << "4. View Leaderboard\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid input! Please enter a number between 1 and 5.\n";
            continue;
        }

        if (choice >= 1 && choice <= 3) {
            string sentence = generator.getSentence(choice);
            tester.startTest(sentence, userName);
        } else if (choice == 4) {
            tester.displayLeaderboard();
        } else if (choice != 5) {
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    cout << "Thank you for using the Typing Speed Tester!\n";
    return 0;
}
