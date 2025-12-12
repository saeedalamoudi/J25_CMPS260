#include <iostream>
#include <string>

using namespace std;

struct TrafficLight {
    int id;
    string roadName;
    string color;
    TrafficLight* next;
};

TrafficLight* head = nullptr;
TrafficLight* current = nullptr;

void addLight() {
    TrafficLight* node = new TrafficLight;
    node->next = nullptr;

    cout << "Enter Road ID: ";
    cin >> node->id;
    cin.ignore();

    cout << "Enter Road Name: ";
    getline(cin, node->roadName);

    cout << "Enter Initial Light Color (Green/Yellow/Red): ";
    getline(cin, node->color);

    if (!head) {
        head = current = node;
        node->next = node;
    }
    else {
        TrafficLight* tail = head;
        while (tail->next != head) tail = tail->next;
        tail->next = node;
        node->next = head;
    }

    cout << "Traffic light added for " << node->roadName << ".\n";
}

void displaySequence() {
    if (!head) {
        cout << "No traffic lights in the system.\n";
        return;
    }

    cout << "========== TRAFFIC LIGHT SEQUENCE ==========\n";
    cout << "ID | Road Name | Light\n";
    cout << "-------------------------------\n";

    TrafficLight* cur = head;
    do {
        cout << cur->id << " | " << cur->roadName << " | " << cur->color;
        if (cur == current) cout << "  <-- current";
        cout << "\n";
        cur = cur->next;
    } while (cur != head);
}

void advanceLight() {
    if (!head || !current) {
        cout << "No traffic lights in the system.\n";
        return;
    }

    TrafficLight* cur = head;
    do {
        cur->color = "Yellow";
        cur = cur->next;
    } while (cur != head);

    current->color = "Red";
    current->next->color = "Green";
    current = current->next;
}

void resetSystem() {
    if (!head) {
        cout << "System reset. All traffic lights cleared.\n";
        return;
    }

    TrafficLight* cur = head->next;
    while (cur != head) {
        TrafficLight* temp = cur;
        cur = cur->next;
        delete temp;
    }
    delete head;
    head = current = nullptr;

    cout << "System reset. All traffic lights cleared.\n";
}

int main() {
    int choice;

    do {
        cout << "\n****** Welcome to Smart Traffic Light Controller ******\n";
        cout << "1. Add Road and Light\n";
        cout << "2. Display Light Sequence\n";
        cout << "3. Advance to Next Light\n";
        cout << "4. Reset System\n";
        cout << "5. Exit\n→ ";
        cin >> choice;

        switch (choice) {
        case 1: addLight(); break;
        case 2: displaySequence(); break;
        case 3: advanceLight(); break;
        case 4: resetSystem(); break;
        case 5:
            cout << "Traffic system saved. Goodbye and drive safe!\n";
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 5);

    resetSystem();
    return 0;
}
