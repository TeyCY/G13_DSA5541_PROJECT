#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <limits>
#include <windows.h>
#include <cmath>
#ifdef _WIN32
#include"USER.cpp"
#include"admin main.cpp"
#else
#include <unistd.h>
#endif
using namespace std;

int main() {
	int choice;
	
	do{
		do{
			system("cls");
			cout<<"*****************************************************"<<endl;
			cout<<"\t\tVV E-claming System"<<endl;
			cout<<"*****************************************************"<<endl;
			cout<<"\t+-------- Make a Choice --------+"<<endl;
			cout<<"\t|                               |"<<endl;
			cout<<"\t|    [1] User                   |"<<endl;
			cout<<"\t|    [2] Admin                  |"<<endl;
			cout<<"\t|    [3] Exit                   |"<<endl;
			cout<<"\t|                               |"<<endl;
			cout<<"\t+-------------------------------+"<<endl;
			cout<<"\tEnter Your Choice : ";
			cin>>choice;
			if(choice<1||choice>4){
				system("cls");
				cout<<"Invalid Selection,Please enter again";
				Sleep(2000);
			}
		} while(choice<1||choice>4);
		switch(choice){
			case 1 :
				ex();
				break;
				
			case 2:
				system("cls");
				main1();
				break;
			default :
				system("cls");
				cout<<"Program Ended";
				exit(0);
				
				
		}
	}while(choice==4);
    cout<<"Program Ended";
    return 0;
}
