#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

struct Box {
    int id;
    string item;
    float weight;
    string destination;
};

const int MAX_STACK = 50;

bool isEmpty(int top) {
    return top == -1;
}

bool isFull(int top) {
    return top == MAX_STACK - 1;
}

const Box* peekBox(const Box stack[], int top) {
    if (isEmpty(top)) return nullptr;
    return &stack[top];
}

bool pushBox(Box stack[], int& top, const Box& b) {
    if (isFull(top)) return false;
    stack[++top] = b;
    return true;
}

bool popBox(Box stack[], int& top, Box& out) {
    if (isEmpty(top)) return false;
    out = stack[top--];
    return true;
}

void displayMenu() {
    cout << "****** Welcome to Warehouse Inventory Stack Tracker ******\n";
    cout << "Please choose one of the following operations:\n";
    cout << "1. Add Box to Stack\n";
    cout << "2. View Current Stack\n";
    cout << "3. Remove Top Box (Dispatch)\n";
    cout << "4. View Inventory Summary\n";
    cout << "5. Exit\n";
    cout << "Choice: ";
}

void pauseToMenu() {
    cout << "Press any key to return to menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    cout << "\n";
}

void addBoxFlow(Box stack[], int& top) {
    if (isFull(top)) {
        cout << "Stack is full. Cannot add more boxes.\n";
        return;
    }

    Box b;

    cout << "Enter Box ID: ";
    cin >> b.id;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Item Name: ";
    getline(cin, b.item);

    cout << "Enter Weight (kg): ";
    cin >> b.weight;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Destination: ";
    getline(cin, b.destination);

    if (pushBox(stack, top, b)) {
        cout << "Box added to stack!\n";
    }
    else {
        cout << "Stack is full. Cannot add more boxes.\n";
    }
}

void viewStackFlow(const Box stack[], int top) {
    if (isEmpty(top)) {
        cout << "Stack is empty.\n";
        return;
    }

    cout << "========= STACKED BOXES (Top to Bottom) =========\n";
    cout << left << setw(10) << "Box ID"
        << setw(20) << "Item"
        << setw(12) << "Weight(kg)"
        << "Destination\n";
    cout << "-----------------------------------------------\n";

    cout << fixed << setprecision(1);
    for (int i = top; i >= 0; --i) {
        cout << left << setw(10) << stack[i].id
            << setw(20) << stack[i].item.substr(0, 19)
            << setw(12) << stack[i].weight
            << stack[i].destination << "\n";
    }
}

void dispatchTopFlow(Box stack[], int& top) {
    Box removed;
    if (!popBox(stack, top, removed)) {
        cout << "Stack is empty. No boxes to dispatch.\n";
        return;
    }

    cout << "Top box dispatched:\n";
    cout << "ID: " << removed.id
        << ", Item: " << removed.item
        << ", Destination: " << removed.destination << "\n";
}

void summaryFlow(const Box stack[], int top) {
    cout << "========== INVENTORY SUMMARY ==========\n";

    int count = top + 1;
    cout << "Total Boxes in Stack: " << count << "\n";

    float totalWeight = 0.0f;
    for (int i = 0; i <= top; ++i) totalWeight += stack[i].weight;

    cout << fixed << setprecision(1);
    cout << "Total Weight: " << totalWeight << " kg\n";

    const Box* topBox = peekBox(stack, top);
    if (topBox) {
        cout << "Top Box: ID " << topBox->id << " - " << topBox->item << "\n";
    }
    else {
        cout << "Top Box: (none)\n";
    }

    cout << "=======================================\n";
}

void saveToFileTopToBottom(const Box stack[], int top, const string& filename) {
    ofstream out(filename);
    if (!out) return;

    out << "ID,Item,Weight,Destination\n";
    out << fixed << setprecision(1);

    for (int i = top; i >= 0; --i) {
        out << stack[i].id << ","
            << stack[i].item << ","
            << stack[i].weight << ","
            << stack[i].destination << "\n";
    }
}

int main() {
    Box stack[MAX_STACK];
    int top = -1;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Try again.\n";
            pauseToMenu();
            continue;
        }

        switch (choice) {
        case 1:
            addBoxFlow(stack, top);
            pauseToMenu();
            break;
        case 2:
            viewStackFlow(stack, top);
            pauseToMenu();
            break;
        case 3:
            dispatchTopFlow(stack, top);
            pauseToMenu();
            break;
        case 4:
            summaryFlow(stack, top);
            pauseToMenu();
            break;
        case 5:
            saveToFileTopToBottom(stack, top, "inventory.txt");
            cout << "Inventory saved to inventory.txt. Have a productive day!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            pauseToMenu();
        }

    } while (choice != 5);

    return 0;
}
