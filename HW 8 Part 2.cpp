#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Song {
    int id;
    string title;
    string artist;
    float duration;
    Song* prev;
    Song* next;
};

Song* head = nullptr;
Song* tail = nullptr;
Song* current = nullptr;

void loadPlaylist() {
    ifstream in("playlist.txt");
    if (!in) return;

    string line;
    getline(in, line);

    while (getline(in, line)) {
        if (line.empty()) continue;

        Song* node = new Song;
        node->prev = node->next = nullptr;

        int start = 0;
        int pos = line.find(',');

        node->id = stoi(line.substr(start, pos - start));

        start = pos + 1;
        pos = line.find(',', start);
        node->title = line.substr(start, pos - start);

        start = pos + 1;
        pos = line.find(',', start);
        node->artist = line.substr(start, pos - start);

        start = pos + 1;
        node->duration = stof(line.substr(start));

        if (!head) {
            head = tail = current = node;
        }
        else {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
    }
}

void savePlaylist() {
    ofstream out("playlist.txt");
    out << "ID,Title,Artist,Duration\n";

    Song* cur = head;
    while (cur) {
        out << cur->id << ","
            << cur->title << ","
            << cur->artist << ","
            << cur->duration << "\n";
        cur = cur->next;
    }
}

void addSong() {
    Song* node = new Song;
    node->prev = node->next = nullptr;

    cout << "Enter Song ID: ";
    cin >> node->id;
    cin.ignore();

    cout << "Enter Title: ";
    getline(cin, node->title);

    cout << "Enter Artist: ";
    getline(cin, node->artist);

    cout << "Enter Duration (in minutes): ";
    cin >> node->duration;

    if (!head) {
        head = tail = current = node;
    }
    else {
        node->prev = tail;
        tail->next = node;
        tail = node;
    }

    cout << "Song added to playlist!\n";
}

void displayPlaylist() {
    if (!head) {
        cout << "Playlist is empty.\n";
        return;
    }

    cout << "========== CURRENT PLAYLIST ==========\n";
    cout << left << setw(8) << "ID"
        << setw(28) << "Title"
        << setw(22) << "Artist"
        << "Duration\n";
    cout << "----------------------------------------------------\n";

    Song* cur = head;
    while (cur) {
        cout << left << setw(8) << cur->id
            << setw(28) << cur->title
            << setw(22) << cur->artist
            << cur->duration;

        if (cur == current) cout << "  <-- current";
        cout << "\n";

        cur = cur->next;
    }
}

void playNext() {
    if (!current || !current->next) {
        cout << "You are at the last song.\n";
        return;
    }
    current = current->next;
    cout << "Now playing: " << current->title
        << " by " << current->artist
        << " (" << current->duration << " min)\n";
}

void playPrevious() {
    if (!current || !current->prev) {
        cout << "You are at the first song.\n";
        return;
    }
    current = current->prev;
    cout << "Now playing: " << current->title
        << " by " << current->artist
        << " (" << current->duration << " min)\n";
}

void removeSong() {
    if (!head) {
        cout << "Playlist is empty.\n";
        return;
    }

    int target;
    cout << "Enter Song ID to remove: ";
    cin >> target;

    Song* cur = head;
    while (cur && cur->id != target) cur = cur->next;

    if (!cur) {
        cout << "Song not found.\n";
        return;
    }

    if (cur == current) {
        if (cur->next) current = cur->next;
        else current = cur->prev;
    }

    if (cur == head) head = cur->next;
    if (cur == tail) tail = cur->prev;

    if (cur->prev) cur->prev->next = cur->next;
    if (cur->next) cur->next->prev = cur->prev;

    cout << "Song '" << cur->title << "' removed from playlist.\n";
    delete cur;
}

int main() {
    loadPlaylist();
    int choice;

    do {
        cout << "\n****** Welcome to Music Playlist Manager ******\n";
        cout << "1. Add Song to Playlist\n";
        cout << "2. Display Playlist\n";
        cout << "3. Play Next Song\n";
        cout << "4. Play Previous Song\n";
        cout << "5. Remove Song\n";
        cout << "6. Save and Exit\n→ ";
        cin >> choice;

        switch (choice) {
        case 1: addSong(); break;
        case 2: displayPlaylist(); break;
        case 3: playNext(); break;
        case 4: playPrevious(); break;
        case 5: removeSong(); break;
        case 6:
            savePlaylist();
            cout << "Playlist saved. See you next jam!\n";
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
