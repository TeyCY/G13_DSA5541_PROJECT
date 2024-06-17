#include<iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <cctype>
using namespace std;
void function_choice(int);
#include"queue.cpp"
#include "admin_detail.cpp"

#include "claim_approved.cpp"
#include "admin_function.cpp"
#include"display.cpp"



int admin_login(){
	admin_queue q;
	string username,password;
	cout<<"Username :";
	cin.ignore();
	getline(cin,username);
	
	cout<<"Password :";
	getline(cin,password);
	checkadminlogin(q);
	if(q.displayList(username,password)){
		system("cls");
		
		cout<<"Login Successful";
		
		system("cls");
		return 1;
	}else{
		system("cls");
		cout<<"Login Failed,Wrong entered username or password";
		Sleep(2000);
		system("cls");
		return 0;
	}
}

void function_choice(int choice){
	int select;
	switch(choice){
		case 1:
			
			select=case1choice();
			select=case1function(select);		
			break;
		case 2:
			
			do{
				system("cls");
				title();
				provided_claim();
				select=case2choice();
				select=case2function(select);
			}while(select!=6);

			break;
		case 3:
			system("cls");
			select=case3choice();
			select=case3function(select);
			break;
		case 4:
			system("cls");
			select=case4choice();
			select=case4function(select);
			break;
	}

}

void admin_function(){
	int choice;
	do{
		do{
			system("cls");
			admin_menu();
			cout<<"Enter Your Choice :";
			cin>>choice;
			if(choice<1||choice>5){
				system("cls");
				cout<<"Invalid Choice !! Please choose again";
				Sleep(1500);
				system("cls");
			}
		}
		while(choice<1||choice>5);
	
		function_choice(choice);
	}while(choice!=5);	
}



int main1(){
	int check;
	
	do{
		display_admin_login();
		check=admin_login();
 	}while(check==0);
 	admin_function();
}

//ADTqueue q;
    //writeDataToFile();
    //readDataFromFile(q);
    //q.displayList();

    //return 0;
