#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Task {
private:
    int id;
    string description;
    bool done;

public:
    Task() {
        id = 0;
        description = "";
        done = false;
    }

    Task(int taskID, string taskDesc) {
        id = taskID;
        description = taskDesc;
        done = false;
    }

    int getID() {
        return id;
    }

    void setID(int taskID) {
        id = taskID;
    }

    string getDescription() {
        return description;
    }

    void setDescription(string taskDesc) {
        description = taskDesc;
    }

    bool isDone() {
        return done;
    }

    void setDone(bool status) {
        done = status;
    }

    void toggle() {
        done = !done;
    }

    void display() const {
        cout << "ID: " << id << " | \"" << description << "\" | Status: ";
        if (done) {
            cout << "Completed" << endl;
        }
        else {
            cout << "Pending" << endl;
        }
    }
};

Task tasks[50];
int taskCount = 0;
int nextID = 1001;

void addTask() {
    if (taskCount >= 50) {
        cout << "Task list is full!" << endl;
        return;
    }

    string desc;
    cout << "Enter description: ";
    getline(cin, desc);

    tasks[taskCount] = Task(nextID, desc);
    cout << "Task added! ID: " << nextID << endl;

    nextID++;
    taskCount++;
}

void toggleTask() {
    int searchID;
    cout << "Enter Task ID: ";
    cin >> searchID;

    int index = -1;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].getID() == searchID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Task not found." << endl;
    }
    else {
        tasks[index].toggle();
        cout << "Toggled task " << searchID << "." << endl;
    }
}

void listPendingTasks() {
    int pendingCount = 0;

    for (int i = 0; i < taskCount; i++) {
        if (!tasks[i].isDone()) {
            tasks[i].display();
            pendingCount++;
        }
    }

    if (pendingCount == 0) {
        cout << "No pending tasks." << endl;
    }
}

void displayMenu() {
    cout << "\n*********** Welcome to To-Do Manager ***********" << endl;
    cout << "1 - Add task" << endl;
    cout << "2 - Toggle task (by ID)" << endl;
    cout << "3 - List pending tasks" << endl;
    cout << "0 - Exit" << endl;
    cout << "Choice: ";
}

int main() {
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        if (choice == 0) {
            cout << "Goodbye!" << endl;
            break;
        }

        switch (choice) {
        case 1:
            addTask();
            break;
        case 2:
            toggleTask();
            break;
        case 3:
            listPendingTasks();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}