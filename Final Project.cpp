#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

class Dictionary {
private:
    map<string, string> words;
    unordered_map<string, int> freq;
    vector<string> history;
    string fname;

    void clear() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

public:
    Dictionary(const string& f = "dictionary_data.txt") : fname(f) {
        load();
    }

    ~Dictionary() {
        save();
    }

    bool add(const string& w, const string& def) {
        string word = w;
        for (int i = 0; i < word.length(); i++) {
            word[i] = tolower(word[i]);
        }

        if (words.find(word) != words.end()) {
            cout << "\nWord already exists!\n";
            return false;
        }

        words[word] = def;
        freq[word] = 0;

        cout << "\nWord added successfully!\n";
        return true;
    }

    bool search(const string& w) {
        string word = w;
        for (int i = 0; i < word.length(); i++) {
            word[i] = tolower(word[i]);
        }

        history.push_back(word);

        auto it = words.find(word);
        if (it != words.end()) {
            freq[word]++;

            cout << "\n=============================================================\n";
            cout << "  WORD FOUND!\n";
            cout << "=============================================================\n\n";
            cout << "  Word: " << it->first << "\n\n";
            cout << "  Definition:\n";
            cout << "  " << it->second << "\n\n";
            cout << "  Times searched: " << freq[word] << "\n\n";
            cout << "=============================================================\n";
            return true;
        }

        cout << "\nWord not found.\n";

        vector<string> suggestions;
        for (const auto& p : words) {
            if (word.length() >= 2 && p.first.length() >= 2) {
                if (word[0] == p.first[0] && word[1] == p.first[1]) {
                    suggestions.push_back(p.first);
                }
            }
        }

        if (suggestions.size() > 0) {
            cout << "\nDid you mean:\n";
            for (int i = 0; i < suggestions.size() && i < 5; i++) {
                cout << "   - " << suggestions[i] << "\n";
            }
        }

        return false;
    }

    bool remove(const string& w) {
        string word = w;
        for (int i = 0; i < word.length(); i++) {
            word[i] = tolower(word[i]);
        }

        auto it = words.find(word);
        if (it != words.end()) {
            words.erase(it);
            freq.erase(word);
            cout << "\nWord deleted!\n";
            return true;
        }

        cout << "\nWord not found.\n";
        return false;
    }

    void autocomplete(const string& p) {
        string prefix = p;
        for (int i = 0; i < prefix.length(); i++) {
            prefix[i] = tolower(prefix[i]);
        }

        vector<string> results;

        for (const auto& pair : words) {
            bool match = true;
            if (pair.first.length() < prefix.length()) {
                match = false;
            }
            else {
                for (int i = 0; i < prefix.length(); i++) {
                    if (pair.first[i] != prefix[i]) {
                        match = false;
                        break;
                    }
                }
            }

            if (match) {
                results.push_back(pair.first);
            }
        }

        if (results.size() == 0) {
            cout << "\nNo suggestions found.\n";
            return;
        }

        cout << "\n=============================================================\n";
        cout << "  SUGGESTIONS\n";
        cout << "=============================================================\n";
        cout << "  Prefix: " << p << "\n";
        cout << "-------------------------------------------------------------\n\n";

        for (int i = 0; i < results.size() && i < 10; i++) {
            cout << "  " << (i + 1) << ". " << results[i] << "\n";
        }

        cout << "\n=============================================================\n";
    }

    void showAll() {
        if (words.empty()) {
            cout << "\nDictionary is empty!\n";
            return;
        }

        cout << "\n=============================================================\n";
        cout << "  ALL WORDS\n";
        cout << "=============================================================\n";
        cout << "  Total: " << words.size() << " words\n";
        cout << "=============================================================\n\n";

        int cnt = 1;
        for (const auto& p : words) {
            cout << "  " << cnt++ << ". " << p.first << "\n";
            cout << "     -> " << p.second << "\n\n";
        }
    }

    void stats() {
        cout << "\n=============================================================\n";
        cout << "  STATISTICS\n";
        cout << "=============================================================\n\n";

        cout << "  Total words: " << words.size() << "\n";
        cout << "  Total searches: " << history.size() << "\n";

        if (freq.size() > 0) {
            string mostSearched = "";
            int maxCount = 0;

            for (auto& p : freq) {
                if (p.second > maxCount) {
                    maxCount = p.second;
                    mostSearched = p.first;
                }
            }

            if (maxCount > 0) {
                cout << "  Most searched: " << mostSearched << " (" << maxCount << "x)\n";
            }
        }

        if (history.size() > 0) {
            cout << "\n-------------------------------------------------------------\n";
            cout << "  RECENT SEARCHES\n";
            cout << "-------------------------------------------------------------\n\n";

            int start = 0;
            if (history.size() > 5) {
                start = history.size() - 5;
            }

            for (int i = start; i < history.size(); i++) {
                cout << "  - " << history[i] << "\n";
            }
        }

        cout << "\n=============================================================\n";
    }

    void save() {
        ofstream f(fname);
        if (!f.is_open()) {
            cerr << "Error saving!\n";
            return;
        }

        for (const auto& p : words) {
            f << p.first << "|" << p.second << "|" << freq[p.first] << "\n";
        }
        f.close();
    }

    void load() {
        ifstream f(fname);
        if (!f.is_open()) {
            return;
        }

        string line;
        while (getline(f, line)) {
            int pos1 = -1;
            int pos2 = -1;

            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '|') {
                    if (pos1 == -1) {
                        pos1 = i;
                    }
                    else {
                        pos2 = i;
                    }
                }
            }

            if (pos1 != -1 && pos2 != -1) {
                string w = line.substr(0, pos1);
                string d = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string freqStr = line.substr(pos2 + 1);
                int fr = 0;

                for (int i = 0; i < freqStr.length(); i++) {
                    fr = fr * 10 + (freqStr[i] - '0');
                }

                words[w] = d;
                freq[w] = fr;
            }
        }
        f.close();
    }
};

void menu() {
    cout << "\n=============================================================\n";
    cout << "  MENU\n";
    cout << "=============================================================\n\n";

    cout << "  1. Search Word\n";
    cout << "  2. Add Word\n";
    cout << "  3. Delete Word\n";
    cout << "  4. Autocomplete\n";
    cout << "  5. Show All Words\n";
    cout << "  6. Statistics\n";
    cout << "  7. Exit\n\n";

    cout << "=============================================================\n";
    cout << "\nChoice: ";
}

void wait() {
    cout << "\nPress ENTER...";
    cin.ignore();
    cin.get();
}

int main() {
    Dictionary dict;
    int choice;
    string word, def, prefix;

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << "\n\n";
    cout << "=============================================================\n";
    cout << "       Smart Dictionary System\n";
    cout << "=============================================================\n";

    cout << "\nLoading";
    for (int i = 0; i < 3; i++) {
        cout << ".";
#ifdef _WIN32
        system("timeout /t 1 >nul");
#else
        system("sleep 0.5");
#endif
    }
    cout << " Done!\n";

    wait();

    while (true) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        cout << "\n=============================================================\n";
        cout << "        SMART DICTIONARY\n";
        cout << "=============================================================\n";

        menu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "\nEnter word: ";
            getline(cin, word);
            dict.search(word);
            wait();
        }
        else if (choice == 2) {
            cout << "\nEnter word: ";
            getline(cin, word);
            cout << "Enter definition: ";
            getline(cin, def);
            dict.add(word, def);
            wait();
        }
        else if (choice == 3) {
            cout << "\nEnter word: ";
            getline(cin, word);
            dict.remove(word);
            wait();
        }
        else if (choice == 4) {
            cout << "\nEnter prefix: ";
            getline(cin, prefix);
            dict.autocomplete(prefix);
            wait();
        }
        else if (choice == 5) {
            dict.showAll();
            wait();
        }
        else if (choice == 6) {
            dict.stats();
            wait();
        }
        else if (choice == 7) {
            cout << "\nSaving...";
            dict.save();
            cout << " Done!\n\n";
            cout << "=============================================================\n";
            cout << "          Thanks for using our dictionary!\n";
            cout << "=============================================================\n\n";
            return 0;
        }
        else {
            cout << "\nInvalid choice!\n";
            wait();
        }
    }

    return 0;
}