#include<iostream>
#include <stdlib.h>
#include <windows.h>

#include"queue.cpp"
using namespace std;
void display_admin_login(){
	cout<<"+++++++++++++++++++++++++++++++"<<endl;
	cout<<"|                             |"<<endl;
	cout<<"|         Admin Login         |"<<endl;
	cout<<"|                             |"<<endl;
	cout<<"+++++++++++++++++++++++++++++++"<<endl;
}

int admin_login(){
	admin_queue q;
	string username,password;
	cout<<"Username :";
	getline(cin,username);
	cout<<"Password :";
	getline(cin,password);
	checkadminlogin(q);
	if(q.displayList(username,password)){
		system("cls");
		
		cout<<"Login Successful";
		Sleep(2000);
		return 1;
	}else{
		system("cls");
		cout<<"Login Failed,Wrong entered username or password";
		Sleep(2000);
		system("cls");
		return 0;
	}
}

int main(){
	int check;
	
	do{
		display_admin_login();
		check=admin_login();
	}while(check==0);
}

//ADTqueue q;
    //writeDataToFile();
    //readDataFromFile(q);
    //q.displayList();

    //return 0;
