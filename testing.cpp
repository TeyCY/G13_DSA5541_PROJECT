#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Person {
public:
    string userID;
    string username;
    string password;

    Person() {}

    Person(string userID, string username, string password)
        : userID(userID), username(username), password(password) {}

    bool checkPassword(string pw) {
        return password == pw;
    }
};

class ADTqueue {
private:
    Person queue[50];
    int head, tail;

public:
    ADTqueue() {
        tail = -1;
        head = 0;
    }

    int empty() {
        return head > tail;
    }

    int full() {
        return tail == 49;
    }

    void append(Person p) {
        if (!full()) {
            tail++;
            queue[tail] = p;
        } else {
            cout << "Queue is Full" << endl;
        }
    }

    Person serve() {
        Person p;
        if (!empty()) {
            p = queue[head];
            head++;
            return p;
        } else {
            cout << "Queue is Empty" << endl;
            return p;
        }
    }

    void loadFromFile() {
        ifstream file("user_login.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string userID, username, password;

            if (getline(ss, userID, '|') && getline(ss, username, '|') && getline(ss, password, '|')) {
                Person p(userID, username, password);
                append(p);
            }
        }
        file.close();
    }

    void saveToFile() {
        ofstream file("user_login.txt");
        if (!file.is_open()) {
            cout << "Error opening file" << endl;
            return;
        }

        for (int i = head; i <= tail; ++i) {
            file << queue[i].userID << "|" << queue[i].username << "|" << queue[i].password << "|" << endl;
        }
        file.close();
    }

    void displayQueue() {
        for (int i = head; i <= tail; ++i) {
            cout << "ID: " << queue[i].userID << ", Name: " << queue[i].username << ", Password: " << queue[i].password << endl;
        }
    }

    bool login(string username, string password) {
        for (int i = head; i <= tail; ++i) {
            if (queue[i].username == username && queue[i].checkPassword(password)) {
                cout << "Login successful" << endl;
                return true;
            }
        }
        cout << "Login failed" << endl;
        return false;
    }

    bool registerUser(string username, string password) {
        // Check if username already exists
        for (int i = head; i <= tail; ++i) {
            if (queue[i].username == username) {
                cout << "Username already exists. Please choose another one." << endl;
                return false;
            }
        }
        cout << "Registration successful" << endl;
        return true;
    }
};

int main() {
    ADTqueue q;
    q.loadFromFile();

    string choice;
    while (true) {
        cout << "Welcome!" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;

        if (choice == "1") {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            q.login(username, password);
            break; // Exit loop after login attempt
        } else if (choice == "2") {
            string username, password;
            cout << "Enter new username: ";
            cin >> username;
            cout << "Enter new password: ";
            cin >> password;
            q.registerUser(username, password);
            break; // Exit loop after registration attempt
        } else {
            cout << "Invalid choice. Please enter 1 or 2." << endl;
        }
    }

    return 0;
}

