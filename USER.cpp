//tey soon hong

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <cctype>

#include <cstdlib>
#include <ctime>



using namespace std;
void index(string);
void check_claiming_history(string );
void apply_claiming();
void ex();

void trim(string &str) 
{
    str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
    str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
}

struct userlogin
{
	string username;
	string password;
	string userID;
};

struct claims
{
	string claimID,userID,start_time,end_time,total,departure,destination,expenses,date,address,days,paper,subject,status;
	
};


class User
{
	private:
		userlogin ul;
		string userID, name, ic, gender, contactNumber, email, caddress, paddress, state, city, poscode, username, password, cpassword;
		char choice;
		int uID;
	public:
		User()
		{
			uID=1;
		}
		void user_profile()
		{
			ifstream u_profile("User_Profile.txt");
		    ofstream user_profile;
		    user_profile.open("User_Profile.txt", ios::app);
		
		    if(user_profile.is_open())
			{
		        string line;
		        while(getline(u_profile,line))
		        {
		        	uID++;
				}
		    }
		    system("cls");
		    cout << "*****************************" << endl;
		    cout << "\tREGISTERATION" << endl;
		    cout << "*****************************" << endl;
		    cout << "Name                 : ";
		    cin.ignore();
		    getline(cin, name);
		    cout << "IC Number            : ";
		    getline(cin, ic);
		    cout << "Gender (Male/Female) : ";
		    getline(cin, gender);
		    cout << "Contact Number       : ";
		    getline(cin, contactNumber);
		    cout << "Email                : ";
		    getline(cin, email);
		    cout << "Current Address      : ";
		    getline(cin, caddress);
		    cout << "Permanent Address    : ";
		    getline(cin, paddress);
		    cout << "State                : ";
		    getline(cin, state);
		    cout << "City                 : ";
		    getline(cin, city);
		    cout << "Postcode             : ";
		    getline(cin, poscode);
		
		    if(user_profile.is_open())
		    {
		    	user_profile<<setw(5)<<setfill('0')<<uID<<"|"<<name<<"|"<<ic<<"|"<<gender<<"|"<<contactNumber<<"|"<<email<<"|"<<caddress<<"|"<<paddress<<"|"<<state<<"|"<<city<<"|"<<poscode<<"|"<<endl;
			}
			user_profile.close();
			index(userID);
		}//end of user_profile
		
		void promtprofile(string id)
		{
			system("cls");
			ifstream inputFile;
			ifstream loginfile;
			loginfile.open("user_login.txt");
			inputFile.open("User_Profile.txt");
			string line;
			
			while(getline(inputFile,line))
			{
				istringstream iss(line);
		        getline(iss, userID, '|');
		        getline(iss, name, '|');
		        getline(iss, ic, '|');
		        getline(iss, gender, '|');
		        getline(iss, contactNumber, '|');
		        getline(iss, email, '|');
		        getline(iss, caddress, '|');
		        getline(iss, paddress, '|');
		        getline(iss, state, '|');
		        getline(iss, city, '|');
		        getline(iss, poscode, '|');
		        
		      
				if(userID==id)
				{
					cout<<"+------------------------------------------------+"<<endl;
					cout<<"Name              : "<<name<<endl;
					cout<<"IC                : "<<ic<<endl;
					cout<<"Gender            : "<<gender<<endl;
					cout<<"Contact Number    : "<<contactNumber<<endl;
					cout<<"Email             : "<<email<<endl;
					cout<<"Current Address   : "<<caddress<<endl;
					cout<<"Permenant Address : "<<paddress<<endl;
					cout<<"State             : "<<state<<endl;
					cout<<"City              : "<<city<<endl;
					cout<<"Poscode           : "<<poscode<<endl;
					cout<<"+------------------------------------------------+"<<endl;
					
				}
				
			}
			inputFile.close();
			
			do
			{
				cout<<"Press E Continue To Main : ";
				cin>>choice;
				if(choice == 'E' || choice == 'e')
				{
					index(userID);
				}
				else
				{
					cout<<"Sorry You Had Enter Wrong Code"<<endl<<endl;
					cout<<"Press E Continue To Main : ";
					cin>>choice;
				}
			}while(choice == 'E' || choice == 'e');
		}//end of promptprofile
		
		void registration()
		{
			char yeayah[2];
			system("cls");
			
			cout << "************************************************" << endl;
			cout << "\t\tJoin Us Today!" << endl;
			cout << "************************************************" << "\n\n";
			
			cout << "Do you want to register? [Enter Y to continue] : ";
			cin >> yeayah;
			
			if(strlen(yeayah) > 1)
			{
				return;
			}
			
			else if(yeayah[0] == 'Y' || yeayah[0] == 'y')
			{
				AddNewUser();
				system("pause");
			}
			
			else
			{
				return;
			}
		}
		
		void AddNewUser()
		{
			string unm;
			string psswd;
			string psswd2;
			char save[2];
			
			ifstream u_login("user_login.txt");
		    ofstream user_login;
		    user_login.open("user_login.txt", ios::app);
			string line;
		    while(getline(u_login,line))
		    {
		        uID++;
			}
			
			cout<<"User ID: "<<setw(5)<<setfill('0')<<uID<<endl;
			
			fflush(stdin);
			cout <<"Username (at most 8 characters) : ";
			getline(cin,unm);
			
			while(unm.length() <= 0 || unm.length() > 8)  
			{
				
					cout << "Only atmost 8 characters! Please try again.\n" << endl;
					fflush(stdin);
					cout << "Username (at most 8 characters) : ";
					getline(cin, unm);	
				
			
			}
		
			fflush(stdin);
			cout << "Password (at most 8 characters) : ";
			getline(cin, psswd);
			
			while(psswd.length()<0 || psswd.length()>8)  
			{
				cout << "Only atmost 8 characters! Please try again.\n" << endl;
				fflush(stdin);
				cout << "Password (at most 8 characters) : ";
				getline(cin, psswd);	
			}
			psswd2="";
			while(psswd2 != psswd)
			{
				fflush(stdin);
				cout << "Confirm your password : ";
				getline(cin, psswd2);
				if(psswd2 != psswd)
				{
					cout << "\n>Both password is not same! Please try again. <\n\n";
				}
			}
			cout <<endl<< "Is all your information correct? [Enter Y to save] :";
			cin >> save;
			
			if(strlen(save) > 1)
			{
			
				return;
			}
			if(save[0] == 'Y' || save[0] == 'y')
			{
				ofstream user_login("user_login.txt", ios::app);
				if(!user_login)
				{
					system("cls");
					cout << "File doesn't exist";
					exit(0);
				}
				user_login<<setw(5)<<setfill('0')<<uID;
				user_login<<"|"<<unm<<"|"<<psswd <<"|"<<endl;
				user_login.close();
				cout << "\n>Your Account is created successfully! Try to login now!" << "\n";
				login();
			}
		}
	

		void login()
		{
			string lgn;
			string passwd;
			string getup;
			char ch,ch1;
			string choice1;
					
			for(int z=0;z<3;z++)
			{
				system("cls");
				cout << "****************************************"<<endl;
				cout << "\tLogin with your account!"<<endl;
				cout << "****************************************";
				cout<<endl;
				cout<<"Exit [Type E]" << "\n\n";
				lgn="";
				passwd="";
				fflush(stdin);
				cout<< "Username : ";
				getline(cin, lgn);
				if(lgn=="E" || lgn=="e")
				{
					return;
				}
				else
				{
					cout<<endl;
					fflush(stdin);
					cout<<"Password : ";
					getline(cin,passwd);
					ifstream inputFile("user_login.txt");
					string line;
					while(getline(inputFile,line))
					{
						istringstream iss(line);
			        	getline(iss, userID, '|');
			        	getline(iss, username, '|');
			        	getline(iss, password, '|');
			        	
			        	if(lgn==username && passwd == password)
						{
						    system("cls");
						    cout << "Login Successfully!"<<endl<<endl;
						    cout<<"Have You Filled In Your Personal Information [Y/N] : ";
						    cin>>ch1;
						    if(ch1=='Y' || ch1=='y')
						    {
			        			index(userID);
			        		}
			        		else if(ch1=='N' || ch1=='n')
			        		{
			        			user_profile();
							}
			        		break;
						}
						
						
						
					}
					
							cout<<endl<<"Invalid Username or Password Entered! \nPlease try again.";
							system("pause");
							return login();	
					inputFile.close();
		}
	}
}


};

class claiming
{
	protected:
	claims c;
	public:
		
		int userID,claimID;
		
		claiming()
		{
			cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
			cout<<"\t  Welcome To TTWC E-Claming System"<<endl;
			cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
		}
		~claiming()
		{
			cout<<"++++++++++++++++++++++++"<<endl;
			cout<<"THANK YOU"<<endl;
			cout<<"++++++++++++++++++++++++"<<endl;
		}
		
		void petrol()
		{
			int cID,uID;
			
		    cout<<"+------------------------------------------+"<<endl;
			cout<<"\t\tPETROL CLAIM"<<endl;
			cout<<"+------------------------------------------+"<<endl;	
			cout<<"DATE                   : ";
			cin.ignore();
			getline(cin,c.date);
			cout<<"DEPARTURE POINT        : ";
			getline(cin,c.departure);
			cout<<"DESTINATION            : ";
			getline(cin,c.destination);
			cout<<"TOTAL DISTANCE (KM)    : ";
			getline(cin,c.total);
			cout<<"DEPARTURE TIME (AM|PM) : ";
			getline(cin,c.start_time);
			cout<<"ARRIVE TIME (AM|PM)    : ";
			getline(cin,c.end_time);
			
			ifstream inFile("petrol.txt");
			ofstream outFile("petrol.txt", ios::app);
			string line;
			while(getline(inFile,line))
		    {
		        cID++;
			}
			
			ifstream ifile("user_login.txt");
			while(getline(ifile,line))
			{
				istringstream iss(line);
				string username,password;
				iss>>uID;
				getline(iss, username, '|');
		        getline(iss, password, '|');
			}
			
			outFile<<cID<<'|'<<setw(5)<<setfill('0')<<uID<<'|'<<c.date<<'|'<<c.departure<<'|'<<c.destination<<'|'<<c.total<<'|'<<c.start_time<<'|'<<c.end_time<<'|'<<"PENDING"<<'\n';
			inFile.close();
			outFile.close();
			ifile.close();
			cout<<"+------------------------------------------+"<<endl;
			cout<<"Request Successfully. You need to wait for 1 to 3 working days for process."<<endl;
			cin.get();
			
			apply_claiming();
		}
		
		void toll()
		{
			int cID,uID;
			cout<<"+-----------------------------------------+"<<endl;
			cout<<"\t\tTOLL CLAIM"<<endl;
			cout<<"+-----------------------------------------+"<<endl;
			cout<<"DATE                      : ";
			cin.ignore();
			getline(cin,c.date);
			cout<<"FIRST TOLL                : ";
			getline(cin,c.departure);
			cout<<"LAST TOLL                 : ";
			getline(cin,c.destination);
			cout<<"TOTAL DISTANCE(COME&BACK) : ";
			getline(cin,c.total);
			cout<<"EXPENSES IN TOLL (RM)     : ";
			getline(cin,c.expenses);
			
			ifstream inFile("toll.txt");
			ofstream outFile("toll.txt", ios::app);
			string line;
			while(getline(inFile,line))
		    {
		        cID++;
			}
			
			ifstream ifile("user_login.txt");
			while(getline(ifile,line))
			{
				istringstream iss(line);
				string username,password;
				iss>>uID;
				getline(iss, username, '|');
		        getline(iss, password, '|');
			}
			outFile<<cID<<'|'<<setw(5)<<setfill('0')<<uID<<'|'<<c.date<<'|'<<c.departure<<'|'<<c.destination<<'|'<<c.total<<'|'<<c.expenses<<'|'<<"PENDING"<<'\n';
			inFile.close();
			outFile.close();
			ifile.close();
			
			cout<<"+-----------------------------------------+"<<endl;
			cout<<"Request Successfully. You need to wait for 1 to 3 working days for process."<<endl;
			cin.get();
			apply_claiming();
		}
		
		void overnight()
		{
			int cID,uID;
			cout<<"+--------------------------------------------------+"<<endl;
			cout<<"\t\tOVERNIGHT STAY CLAIM"<<endl;
			cout<<"+--------------------------------------------------+"<<endl;
			cout<<"DATE (XX TO YY)                 : ";
			cin.ignore();
			getline(cin,c.date);
			cout<<"OVERNIGHT STAYCATION ADDRESS    : ";
			getline(cin,c.address);
			cout<<"NUMBER OF DAYS STAY             : ";
			getline(cin,c.days);
			cout<<"PPRICE|DAY                      : RM ";
			getline(cin,c.expenses); 
			
			ifstream inFile("overnight.txt");
			ofstream outFile("overnight.txt", ios::app);
			string line;
			while(getline(inFile,line))
		    {
		        cID++;
			}
			ifstream ifile("user_login.txt");
			while(getline(ifile,line))
			{
				istringstream iss(line);
				string username,password;
				iss>>uID;
				getline(iss, username, '|');
		        getline(iss, password, '|');
			}
			
			outFile<<cID<<'|'<<setw(5)<<setfill('0')<<uID<<'|'<<c.date<<'|'<<c.address<<'|'<<c.days<<'|'<<c.expenses<<'|'<<"PENDING"<<'\n';
			inFile.close();
			outFile.close();
			ifile.close();
			
			cout<<"+--------------------------------------------------+"<<endl;
			cout<<"Request Successfully. You need to wait for 1 to 3 working days for process."<<endl;
			cin.get();
			apply_claiming();
		}
		
		void givetutorial()
		{
			int cID,uID;
			cout<<"+-----------------------------------------------+"<<endl;
			cout<<"\t\tINSTURCTOR CLAIM"<<endl;
			cout<<"+-----------------------------------------------+"<<endl;
			cout<<"DATE                       : ";
			cin.ignore();
			getline(cin,c.date);
			cout<<"INSTRUCTOR LOCATION        : ";
			getline(cin,c.address);
			cout<<"START TIME                 : ";
			getline(cin,c.start_time);
			cout<<"END TIME                   : ";
			getline(cin,c.end_time);
			cout<<"TOTAL TIME                 : ";
			getline(cin,c.total);
			
			ifstream inFile("givetutorial.txt");
			ofstream outFile("givetutorial.txt", ios::app);
			string line;
			
			while(getline(inFile,line))
		    {
		        cID++;
			}
			
			ifstream ifile("user_login.txt");
			while(getline(ifile,line))
			{
				istringstream iss(line);
				string username,password;
				iss>>uID;
				getline(iss, username, '|');
		        getline(iss, password, '|');
			}
			outFile<<cID<<'|'<<setw(5)<<setfill('0')<<uID<<'|'<<c.date<<'|'<<c.address<<'|'<<c.start_time<<'|'<<c.end_time<<'|'<<c.total<<'|'<<"PENDING"<<'\n';
			inFile.close();
			outFile.close();
			ifile.close();
			
			cout<<"+-----------------------------------------------+"<<endl;
			cout<<"Request Successfully. You need to wait for 1 to 3 working days for process."<<endl;
			cin.get();
			apply_claiming();
		}
		
		void papermarking()
		{
			int cID,uID;
			cout<<"+----------------------------------------------------------------+"<<endl;
			cout<<"\t\tPAPER MARKING CLAIM"<<endl;
			cout<<"+----------------------------------------------------------------+"<<endl;
			cout<<"SUBJECT                        : ";
			cin.ignore();
			getline(cin,c.subject);
			cout<<"TOTAL NUMBER OF PAPER MARKING  : ";
			getline(cin,c.total);
			
			ifstream inFile("papermark.txt");
			ofstream outFile("papermark.txt", ios::app);
			string line;
			
			while(getline(inFile,line))
		    {
		        cID++;
			}
			
			ifstream ifile("user_login.txt");
			while(getline(ifile,line))
			{
				istringstream iss(line);
				string username,password;
				iss>>uID;
				getline(iss, username, '|');
		        getline(iss, password, '|');
			}
			
			outFile<<cID<<'|'<<setw(5)<<setfill('0')<<uID<<'|'<<c.subject<<'|'<<c.total<<'|'<<"PENDING"<<'\n';
			inFile.close();
			outFile.close();
			ifile.close();
			
			cout<<"+---------------------------------+"<<endl;
			cout<<"Request Successfully. You need to wait for 1 to 3 working days for process."<<endl;
			cin.get();
			apply_claiming();
			
		} 
		friend class check;
};

class check:public claiming
{
	claims c;
	public:
		int uID;
		
		char choice;
		
		void check_petrol(claiming& cl,string id)
		{
			float km=0,rm=0,total=0,expected=0;
		bool found = false;
			system("cls");
			ifstream check("petrol.txt");
			ifstream ulo("user_login.txt");
			ofstream wid("petrol.txt",ios::app);
			if(!check)
		    {
		        cout<<"File does not exist"<<endl;
		       
		    }
			string line,status;
	    	while (getline(check, line))
			{
		        istringstream iss(line);
		        getline(iss, c.claimID, '|');
		        getline(iss, c.userID, '|');
		        getline(iss, c.date, '|');
		        getline(iss, c.departure, '|');
		        getline(iss, c.destination, '|');
		        getline(iss, c.total, '|');
		        stringstream ss(c.total);
			    ss>>km;
		        getline(iss, c.start_time, '|');
		        getline(iss, c.end_time, '|');
		        getline(iss, c.status, '|');
		        if (c.status.empty())
				{
				    c.status = "PENDING";
				}
		        
		       	if(c.userID==id){
		       		found=true;
		       			cout<<"+------------------------------------------+"<<endl;
					    cout<<"\t\tPETROL CLAIM"<<endl;
					    cout<<"+------------------------------------------+"<<endl;
						cout<<"DATE                   : "<<c.date<<endl;
						cout<<"DEPARTURE POINT        : "<<c.departure<<endl;
						cout<<"DESTINATION            : "<<c.destination<<endl;
						cout<<"TOTAL DISTANCE (KM)    : "<<c.total<<endl;
						cout<<"DEPARTURE TIME (AM|PM) : "<<c.start_time<<endl;
						cout<<"ARRIVE TIME (AM|PM)    : "<<c.end_time<<endl;
						cout<<"STATUS                 : "<<c.status<<endl;
						cout<<"+------------------------------------------+"<<endl;
						if (c.status=="PENDING")
						{
							rm=km*0.60;
							cout<<"Claim (Expected) : RM"<<rm<<endl;
							expected+=rm;
						}
						if(c.status=="APPROVED")
						{
							rm=km*0.60;
							cout<<"Claim            : RM"<<rm<<endl;
							total+=rm;
						}
						else if(c.status=="REJECTED")
						{
							rm=0.00;
							cout<<"Claim            : RM"<<rm<<endl;
						}
						
				   }
		       	
				
		       	}
			    if(!found){
					cout<<"No history found"<<endl;
				}else{
					cout<<"\n+-----------------------------------------------+"<<endl;
						cout<<"Total Claim (Expected) : RM"<<expected<<endl;
						cout<<"Total Claim Approved   : RM"<<total<<endl;
						cout<<"+-----------------------------------------------+"<<endl;
				}
				
				cout<<"Press E To Back To Check Claiming Page : "<<endl;
				cin>>choice;
				if(choice== 'E' || choice == 'e')
				{
					check_claiming_history(id);
				}
			//end while
			check.close();	
		}
		
		void check_toll(string id)
		{
			float km=0,rm=0,total=0,expected=0;
		bool found = false;
			system("cls");
			int compare,claimID;
			ifstream check("toll.txt");
			ifstream ulo("user_login.txt");
			ofstream wid("toll.txt",ios::app);
			if(!check)
		    {
		        cout<<"File does not exist"<<endl;
		        
		    }
			string line,status;
	    	while (getline(check, line))
			{
		        istringstream iss(line);
		        getline(iss, c.claimID, '|');
		        getline(iss, c.userID, '|');
		        getline(iss, c.date, '|');
		        getline(iss, c.departure, '|');
		        getline(iss, c.destination, '|');
		        getline(iss, c.total, '|');
		        stringstream ss(c.total);
			    ss>>km;
		        getline(iss, c.expenses, '|');
		        getline(iss, c.status, '|');
		        
		       
		       	if(c.userID==id){
		       		found=true;
		    	cout<<"+----------------------------------------+"<<endl;
			    cout<<"\t\tTOLL CLAIM"<<endl;
			    cout<<"+----------------------------------------+"<<endl;
			    cout<<"DATE                      : "<<c.date<<endl;
				cout<<"FIRST TOLL                : "<<c.departure<<endl;
				cout<<"LAST TOLL                 : "<<c.destination<<endl;
				cout<<"TOTAL DISTANCE(COME&BACK) : "<<c.total<<endl;
				cout<<"EXPENSES IN TOLL (RM)     : "<<c.expenses<<endl;
				cout<<"STATUS                    : "<<c.status<<endl;
				cout<<"+----------------------------------------+"<<endl;
				if (c.status=="PENDING")
				{
					rm=km*0.60;
					cout<<"Claim (Expected) : RM"<<rm<<endl;
					expected+=rm;
				}
				if(c.status=="APPROVED")
				{
					rm=km*0.60;
					cout<<"Claim            : RM"<<rm<<endl;
					total+=rm;
				}
				else if(c.status=="REJECTED")
				{
					rm=0.00;
					cout<<"Claim            : RM"<<rm<<endl;
				}
				   }
		       	
		    }
		    if(!found){
					cout<<"No history found"<<endl;
				}else{
					cout<<"\n+-----------------------------------------------+"<<endl;
				cout<<"Total Claim (Expected) : RM"<<expected<<endl;
				cout<<"Total Claim Approved   : RM"<<total<<endl;
				cout<<"+-----------------------------------------------+"<<endl;
				}
		    
		    cout<<"Press E To Back To Check Claiming Page : "<<endl;
				cin>>choice;
				if(choice== 'E' || choice == 'e')
				{
					check_claiming_history(id);
				}
		    check.close();
		}
		
		void check_overnight(string id)
		{
			float km=0,rm=0,total=0,expected=0;
		bool found = false;
			system("cls");
			int compare;
			ifstream check("overnight.txt");
			ifstream ulo("user_login.txt");
			ofstream wid("overnight.txt",ios::app);
			if(!check)
		    {
		        cout<<"File does not exist"<<endl;
		        exit(0);
		    }
			string line,status;
	    	while (getline(check, line))
			{
		        istringstream iss(line);
		        getline(iss, c.claimID, '|');
		        getline(iss, c.userID, '|');
		        getline(iss, c.date, '|');
		        getline(iss, c.address, '|');
		        getline(iss, c.days, '|');
		        stringstream ss(c.days);
			    ss>>km;
		        getline(iss, c.expenses, '|');
		        
		        getline(iss, c.status, '|');
		       	if(c.userID==id){
		       		found=true;
		       		cout<<"+-------------------------------------+"<<endl;
			        cout<<"\tOVERNIGHT STAY CLAIM"<<endl;
			        cout<<"+-------------------------------------+"<<endl;
			        cout<<"DATE (XX TO YY)      : "<<c.date<<endl;
					cout<<"OVERNIGHT STAYCATION : "<<c.address<<endl;
					cout<<"NUMBER OF DAYS STAY  : "<<c.days<<endl;
					cout<<"PRICE (PER DAY)      : RM "<<c.expenses<<endl;
			    	cout<<"STATUS               : "<<c.status<<endl;
			    	cout<<"+-------------------------------------+"<<endl;
			    	
			    	if (c.status=="PENDING")
					{
						rm=km*0.60;
						cout<<"Claim (Expected) : RM"<<rm<<endl;
						expected+=rm;
					}
					if(c.status=="APPROVED")
					{
						rm=km*0.60;
						cout<<"Claim            : RM"<<rm<<endl;
						total+=rm;
					}
					else if(c.status=="REJECTED")
					{
						rm=0.00;
						cout<<"Claim            : RM"<<rm<<endl;
					}
				   }
			}
			if(!found){
					cout<<"No history found"<<endl;
				}else{
					cout<<"\n+-----------------------------------------------+"<<endl;
			cout<<"Total Claim (Expected) : RM"<<expected<<endl;
			cout<<"Total Claim Approved   : RM"<<total<<endl;
			cout<<"+-----------------------------------------------+"<<endl;
				}
			
			
			
			cout<<"Press E To Back To Check Claiming Page : "<<endl;
				cin>>choice;
				if(choice== 'E' || choice == 'e')
				{
					check_claiming_history(id);
				}
		    check.close();
		}
		
		void check_instruction(string id)
		{
			float km=0,rm=0,total=0,expected=0;
		bool found = false;
			system("cls");
			int compare;
			ifstream check("givetutorial.txt");
			ifstream ulo("user_login.txt");
			ofstream wid("givetutorial.txt",ios::app);
			if(!check)
		    {
		        cout<<"File does not exist"<<endl;
		        exit(0);
		    }
			string line,status;
	    	while (getline(check, line))
			{
		        istringstream iss(line);
		        getline(iss, c.claimID, '|');
		        getline(iss, c.userID, '|');
		        getline(iss, c.date, '|');
		        getline(iss, c.address, '|');
		        getline(iss, c.start_time, '|');
		        getline(iss, c.end_time, '|');
		        getline(iss, c.total, '|');
		        stringstream ss(c.total);
			    ss>>km;
		        getline(iss, c.status, '|');
		        if(c.userID==id){
		        	found=true;
			        cout<<"+------------------------------+"<<endl;
			        cout<<"\tINSTRUCTOR CLAIM"<<endl;
			        cout<<"+------------------------------+"<<endl;
			        cout<<"DATE               : "<<c.date<<endl;
					cout<<"DESTINATION        : "<<c.address<<endl;
					cout<<"START TIME (AM/PM) : "<<c.start_time<<endl;
					cout<<"END TIME (AM/PM)   : "<<c.end_time<<endl;
					cout<<"TOTAL              : "<<c.total<<endl;
					cout<<"STATUS             : "<<c.status<<endl;
					cout<<"+------------------------------+"<<endl;
					if (c.status=="PENDING")
			{
				rm=km*0.60;
				cout<<"Claim (Expected) : RM"<<rm<<endl;
				expected+=rm;
			}
			if(c.status=="APPROVED")
			{
				rm=km*0.60;
				cout<<"Claim            : RM"<<rm<<endl;
				total+=rm;
			}
			else if(c.status=="REJECTED")
			{
				rm=0.00;
				cout<<"Claim            : RM"<<rm<<endl;
			}
				}

		    }
		    if(!found){
					cout<<"No history found"<<endl;
				}else{
					cout<<"\n+-----------------------------------------------+"<<endl;
			cout<<"Total Claim (Expected) : RM"<<expected<<endl;
			cout<<"Total Claim Approved   : RM"<<total<<endl;
			cout<<"+-----------------------------------------------+"<<endl;
				}
		    
			
			
			cout<<"Press E To Back To Check Claiming Page : "<<endl;
				cin>>choice;
				if(choice== 'E' || choice == 'e')
				{
					check_claiming_history(id);
				}
		
		    check.close();
		}
		
		void check_papermarking(string id)
		{
			float km=0,rm=0,total=0,expected=0;
		bool found = false;
			system("cls");
			ifstream check("papermark.txt");
			ifstream ulo("user_login.txt");
			ofstream wid("papermark.txt",ios::app);
			if(!check)
		    {
		        cout<<"File does not exist"<<endl;
		        exit(0);
		    }
			string line,status;
	    	while (getline(check, line))
			{
		        istringstream iss(line);
		        getline(iss, c.claimID, '|');
		        getline(iss, c.userID, '|');
		        getline(iss, c.subject, '|');
		        getline(iss, c.total, '|');
		        stringstream ss(c.total);
			    ss>>km;
		        getline(iss, c.status, '|');
		        if (c.status.empty())
				{
				    c.status = "PENDING";
				}
		        if(c.userID==id){
		        	found=true;
		        	cout<<"+-------------------------------------------------+"<<endl;
					cout<<"\t\tPAPER MARKING CLAIM"<<endl;
					cout<<"+-------------------------------------------------+"<<endl;
					cout<<"SUBJECT                        : "<<c.subject<<endl;
					cout<<"TOTAL NUMBER OF PAPER MARKING  : "<<c.total<<endl;
					cout<<"STATUS                         : "<<c.status<<endl;
					cout<<"+-------------------------------------------------+"<<endl;
					if (c.status=="PENDING")
			{
				rm=km*0.60;
				cout<<"Claim (Expected) : RM"<<rm<<endl;
				expected+=rm;
			}
			if(c.status=="APPROVED")
			{
				rm=km*0.60;
				cout<<"Claim            : RM"<<rm<<endl;
				total+=rm;
			}
			else if(c.status=="REJECTED")
			{
				rm=0.00;
				cout<<"Claim            : RM"<<rm<<endl;
			}
				}
		       }
		     	
		 	if(!found){
					cout<<"No history found"<<endl;
				}else{
					cout<<"\n+-----------------------------------------------+"<<endl;
			cout<<"Total Claim (Expected) : RM"<<expected<<endl;
			cout<<"Total Claim Approved   : RM"<<total<<endl;
			cout<<"+-----------------------------------------------+"<<endl;
				}
		    
		    
			
			
		    cout<<"Press E To Back To Check Claiming Page : "<<endl;
				cin>>choice;
				if(choice== 'E' || choice == 'e')
				{
					check_claiming_history(id);
				}
		    check.close();
		}
			
};


void index(string id)
{
	User u;
	char choice[2];

	system("cls");
	
	for (int x = 0; x < 10000; x++)
	{
	cout<<"+--------------------------------------------+"<<endl;
	cout<<"    WELCOME TO MMU-TTWC E-CLAIMING SYSTEM    "<<endl;
	cout<<"+--------------------------------------------+"<<endl;
	cout<<"+--------------------------------------------+"<<endl;
	cout<<"|                                            |"<<endl;
	cout<<"|          [P] Personal Information          |"<<endl;
	cout<<"|          [R] Request                       |"<<endl;
	cout<<"|          [S] Status                        |"<<endl;
	cout<<"|          [E] Log Out                       |"<<endl;
	cout<<"|                                            |"<<endl;
	cout<<"+--------------------------------------------+"<<endl;
					
	fflush(stdin);
	cout<<"Enter choice : ";
	cin >> choice;
					    
	int length = strlen(choice);
					    
	if(length > 1)
	{
	  	cout<<"Only one alphabet need to type!" << "\n\n\n\n\n";
		system("pause");
	    continue;
	}
						
	if(choice[0] == 'E' || choice[0] == 'e')
	{
		exit(0);
		
	}
					
	else if (choice[0] == 'P' || choice[0] == 'p')
	{		    
		u.promtprofile(id);
	}
					    
	else if (choice[0] == 'R' || choice[0] == 'r')
	{
	    apply_claiming();
	}
	else if (choice[0] == 'S' || choice[0] == 'e')
	{
		check_claiming_history(id);	    	
	}
}
}

void check_claiming_history(string id)
{
	system("cls");
	User u;
	claiming la;
	system("cls");
	check c;
	int choice;
	string uid="";
	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"\t\t\tCLAIM"<<endl;
	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"1. Petrol Claim history "<<endl;
	cout<<"2. Toll Claim history"<<endl;
	cout<<"3. Overnight Stay Claim history"<<endl;
	cout<<"4. Intruction Claim History"<<endl;
	cout<<"5. Paper Marking Claim History"<<endl;
	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"Enter Your Choice [Press 6 back to main]: ";
	cin>>choice;
	while(choice<1||choice>6)
	{
		cout<<"Wrong Choice are selected! Please enter again your choice:";
		cin>>choice;
	}
	cin.ignore();
	
	switch(choice)
	{
		case 1:
			c.check_petrol(la,id);
			break;
		case 2:
			c.check_toll(id);
			break;
		case 3:
			c.check_overnight(id);
			break;
		case 4:
			c.check_instruction(id);
			break;
		case 5:
			c.check_papermarking(id);
		case 6:
			index(uid);
	}
}
	
void apply_claiming()
{
	system("cls");
	check c;
	int choice,id;
	string uid="";
	cout<<"Please choose your claim"<<endl;
	cout<<"1. Petrol Claim"<<endl;
	cout<<"2. Toll claim"<<endl;
	cout<<"3. Overnight stay claim"<<endl;
	cout<<"4. Intruction claim"<<endl;
	cout<<"5. Paper making claim"<<endl;
	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"Enter Your Choice [Press 6 back to main]: ";
	cin>>choice;
	while(choice<1||choice>6) {
		cout<<"Wrong Choice are selected! Please enter again your choice:";
		cin>>choice;
	}
	system("cls");
	switch(choice){
		case 1:
			c.petrol();
			break;
		case 2:
			c.toll();
			break;
		case 3:
			c.overnight();
			break;
		case 4:
			c.givetutorial();
			break;
		
		case 5:
			c.papermarking();
		case 6:
			index(uid);
	}
}

void ex(){
	User ue;
					for(int g=0;g<10000;g++)
					{
						system("cls");
						int dptc;
						cout<<"*****************************************************"<<endl;
						cout<<"\tWELCOME TO MMU-TTWC E-CLAIMING SYSTEM"<<endl;
						cout<<"*****************************************************"<<endl;
							
						cout<<"\t+-------- Make a Choice --------+"<<endl;
						cout<<"\t|                               |"<<endl;
						cout<<"\t|    [1] Register               |"<<endl;
						cout<<"\t|    [2] Log In                 |"<<endl;
						cout<<"\t|    [3] Exit                   |"<<endl;
						cout<<"\t|                               |"<<endl;
						cout<<"\t+-------------------------------+"<<endl;
						cout<<"\tEnter Your Choice : ";
						cin>>dptc;
					
						
						if(dptc==1)
						{
							ue.registration();
						}
						else if(dptc==2)
						{
							ue.login();
						}
						else if(dptc==3)
						{
							cout<<"\tExiting in progress...";
							exit(0);
						}
						else 
						{
							cout<<"\n\tInvalid choice entered!\n\tPlease try again.  ";
							system("pause");
							
							continue;
					}
					
				}
}
