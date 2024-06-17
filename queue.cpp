#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct staff {
    string id;
    string name;
    string password;
};

struct node {
    string id;
    string name;
    string password;
    node* next;
};



class admin_queue {
    private:
        node *front, *rear;
        

    public:
        admin_queue() {
            front = NULL;
            rear = NULL;
        }

        int empty() {
            return front == NULL;
        }

        void append(const staff& s) {
            if (rear != NULL) {
                rear->next = new node;
                rear = rear->next;
                rear->id = s.id;
                rear->name = s.name;
                rear->password = s.password;
                rear->next = NULL;
            } else {
                front = rear = new node;
                front->id = s.id;
                front->name = s.name;
                front->password = s.password;
                front->next = NULL;
            }
        }

        int serve(string username,string password) {
            staff s;
            if (!empty()) {
                s.id = front->id;
                s.name = front->name;
                s.password = front->password;
                node *temp = front;
                front = front->next;
                delete temp;
				
                if (front == NULL) {
                    rear = NULL;
                }
                if(username==s.name && password==s.password){
                	return 1;
				}
				return 0;
            } else {
                cout << "Queue is Empty" << endl;
                return 0;
            }
            
        }

        int displayList(string username,string password) {
            int s;
            bool check;
            while (!empty()) {
                s = serve(username, password);
               	if(s==1){
               		return 1;
				   }
            }
            return 0;
        }
};



void checkadminlogin(admin_queue& q) {
    ifstream readfile("admin_login.txt");
    if (!readfile) {
        cerr << "Unable to open file for reading" << endl;
        return;
    }

    string line;
    while (getline(readfile, line)) {
        staff s;
        istringstream iss(line);

        getline(iss, s.id, '|');
        getline(iss, s.name, '|');
        getline(iss, s.password, '|');
        q.append(s);
    }
	
    readfile.close();
}

////////////////////////////////////////////////////////



