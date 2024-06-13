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
#else
#include <unistd.h>
#endif
using namespace std;
void status(char,int);
void staff_function();
void admin_function();
void display_claim();
void claim_choice();
struct claim{
	string claim_id,user_id,date,departure,destination,total,start_time,end_time,status;
	string expenses,address,days,paper,subject;
};


class count
{
	
	public:
		claim c;
		int countPetrol()
		{
			int i=0;
			
			ifstream file;
			file.open("petrol.txt");
			    if (!file.is_open()) {
			        cerr << "File don't exist !!!";
			    }
			
			    string line;
			    while (getline(file, line)) {
			        istringstream iss(line);
			        getline(iss, c.claim_id, '|');
			        getline(iss, c.user_id, '|');  
			        getline(iss, c.date, '|');
			        getline(iss, c.departure, '|');
			        getline(iss, c.destination, '|');
			        getline(iss, c.total, '|');
			        getline(iss, c.start_time, '|');
			        getline(iss, c.end_time, '|');
			        getline(iss, c.status);
			        
			        
			        if (c.status == "PENDING") {
			            i++;
			            c.status="";
			        }
			        
			    }
		
		    file.close();
		    
		    return i;
		}
		
		int countToll()
		{
			int tollcount=0;
			ifstream file;
			file.open("toll.txt");
			    if (!file.is_open()) {
			        cout<< "File don't exist !!!";
			    }
			
			    string line;
			    while (getline(file, line)) {
			        istringstream iss(line);
			        getline(iss, c.claim_id, '|');
			        getline(iss, c.user_id, '|');
			        getline(iss, c.date, '|');
			        getline(iss, c.departure, '|');
			        getline(iss, c.destination, '|');
			        getline(iss, c.total, '|');
			        getline(iss, c.expenses, '|');
			        getline(iss, c.status);
			        if (c.status == "PENDING") {
			            tollcount++;
			            c.status="";
			        }
			    }
		
		    file.close();
		    return tollcount;
		}
		
		int countOvernight()
		{
			int overnightcount=0;
			ifstream file;
			file.open("overnight.txt");
			    if (!file.is_open()) {
			        cout << "File don't exist !!!";
			    }
			
			    string line;
			    while (getline(file, line)) {
			        istringstream iss(line);
			        getline(iss, c.claim_id, '|');
			        getline(iss, c.user_id, '|');
			        getline(iss, c.date, '|');
			        getline(iss, c.address, '|');
			        getline(iss, c.days, '|');
			        getline(iss, c.expenses, '|');
			        getline(iss, c.status);
			        if (c.status == "PENDING") {
			            overnightcount++;
			            c.status="";
			        }
			    }
		
		    file.close();
		    return overnightcount;
		}
		
		int countInstruction()
		{
			int instructioncount=0;
			ifstream file;
			file.open("givetutorial.txt");
			    if (!file.is_open()) {
			        cout<< "File don't exist !!!";
			    }
			
			    string line;
			    while (getline(file, line)) {
			        istringstream iss(line);
			        getline(iss, c.claim_id, '|');
			        getline(iss, c.user_id, '|');
			        getline(iss, c.date, '|');
			        getline(iss, c.address, '|');
			        getline(iss, c.start_time, '|');
			        getline(iss, c.end_time, '|');
			        getline(iss, c.total, '|');
			        getline(iss, c.status);
			        if (c.status == "PENDING") {
			            instructioncount++;
			            c.status="";
			        }
			    }
		
		    file.close();
		    return instructioncount;
		}
		
		int countPapermarketing()
		{
			int papermarkingcount=0;
			ifstream file;
			file.open("papermark.txt");
			    if (!file.is_open()) {
			        cout<< "File don't exist !!!";
			    }
			
			    string line;
			    while (getline(file, line)) {
			        istringstream iss(line);
		            getline(iss, c.claim_id, '|');
			        getline(iss, c.user_id, '|');
			        getline(iss, c.subject, '|');
			        getline(iss, c.total, '|');
			        getline(iss, c.status);
			        if (c.status == "PENDING") {
			            papermarkingcount++;
			            c.status="";
			        }
			    }
		
		    file.close();
		    return papermarkingcount;
		}
};


class Request {
	private:
		claim c;
		float km,rm;
		char choice;
		
	public:
		friend class change_status;
		
	    char viewPetrolClaim() {
	    	
			    ifstream petrol("petrol.txt");
			
			    if (!petrol.is_open()) {
			        cout<< "File don't exist !!!";
			    }
			
			    string pt;
			    while (getline(petrol, pt)) {
			        istringstream iss(pt);
					
			        getline(iss, c.claim_id, '|');
			        getline(iss, c.user_id, '|');  
			        getline(iss, c.date, '|');
			        getline(iss, c.departure, '|');
			        getline(iss, c.destination, '|');
			        getline(iss, c.total, '|');
			        stringstream ss(c.total);
			        ss>>km;
			        rm=km*0.60;
			        getline(iss, c.start_time, '|');
			        getline(iss, c.end_time, '|');
			        getline(iss, c.status);
			       
			        if (c.status == "PENDING") {
			        	cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" << "Claim ID    : " << c.claim_id << "\n";
				        cout << "User ID     : " << c.user_id << "\n";
				        cout << "Date        : " << c.date << "\n";
				        cout << "Departure   : " << c.departure << "\n";
				        cout << "Destination : " << c.destination << "\n";
				        cout << "Total       : " << c.total << "\n";
				        cout << "Start Time  : " << c.start_time << "\n";
				        cout << "End Time    : " << c.end_time << "\n\n";
				        cout << "Total claim (1KM x RM 0.60 )RM:"<<rm<<"\n";
				        cout << "Status      : " << c.status << endl;
				        cout <<"-----------------------------------------------"<<endl;
			        }
			        
			    }
			cout<<"Please enter the claim id that you want to make changes :";
			cin>>choice;
		    petrol.close();
		    return choice;
		}

	
	    char viewTollClaim() {
	        ifstream file("toll.txt");
	
	        if (!file.is_open()) {
	            cerr << "File don't exist !!!";
	        }
	
	        string line;
	        while (getline(file, line)) {
	            istringstream iss(line);
	            getline(iss, c.claim_id, '|');
		        getline(iss, c.user_id, '|');
		        getline(iss, c.date, '|');
		        getline(iss, c.departure, '|');
		        getline(iss, c.destination, '|');
		        getline(iss, c.total, '|');
		        stringstream ss(c.total);
			    ss>>km;
			    rm=km*0.30;
		        getline(iss, c.expenses, '|');
		        getline(iss, c.status);
		        if (c.status == "PENDING") {
		        		cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" << "Claim ID          : " << c.claim_id << "\n";
			            cout << "User ID           : " << c.user_id << "\n";
				        cout << "Date              : " << c.date << "\n";
				        cout << "Departure         : " << c.departure << "\n";
				        cout << "Destination       : " << c.destination << "\n";
				        cout << "Total Distance(KM): " << c.total << "\n";
				        cout << "Expenses (RM)     : " << c.expenses << "\n\n";
				        cout << "Total claim ("<<km<<"1KM x RM 0.30 )RM:"<<rm<<"\n";
				        cout << "Status            : " << c.status << endl;
				        cout <<"-----------------------------------------------"<<endl;
			        }
	        }
			cout<<"Please enter the claim id that you want to make changes :";
			cin>>choice;
		    file.close();
		    return choice;
	        
	    }
	    
	    char viewOvernight_stay_claim()
	    {
	    	ifstream file("overnight.txt");
	
	        if (!file.is_open()) {
	            cerr << "File don't exist !!!";
	        }
	
	        string line;
	        while (getline(file, line)) {
	            istringstream iss(line);
	            getline(iss, c.claim_id, '|');
		        getline(iss, c.user_id, '|');
		        getline(iss, c.date, '|');
		        getline(iss, c.address, '|');
		        getline(iss, c.days, '|');
		        getline(iss, c.expenses, '|');
		        stringstream ss(c.expenses);
			    ss>>km;
			    rm=km*100;
		        getline(iss, c.status);
		        if (c.status == "PENDING") {
		        		cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" ;
						cout << "Claim ID             : " << c.claim_id << "\n";
					    cout << "User ID              : " << c.user_id << "\n";
						cout << "Date                 : " << c.date << "\n";
						cout << "Address              : " << c.address << "\n";
						cout << "Day                  : " << c.days << "\n";
						cout << "Expense(inclucde tax): " << c.expenses << "\n\n";
						cout << "Total claim (1 DAY x RM 100 )RM:"<<rm<<"\n";
						cout << "Status   : " << c.status << endl;
						cout <<"-----------------------------------------------"<<endl;
			        }
	        }
	        cout<<"Please enter the claim id that you want to make changes :";
			cin>>choice;
		    file.close();
		    return choice;
		}
		
		char viewInstuction_claim()
	    {
	    	ifstream file("givetutorial.txt");
	
	        if (!file.is_open()) {
	            cerr << "File don't exist !!!";
	        }
	
	        string line;
	        while (getline(file, line)) {
	            istringstream iss(line);
	            getline(iss, c.claim_id, '|');
		        getline(iss, c.user_id, '|');
		        getline(iss, c.date, '|');
		        getline(iss, c.address, '|');
		        getline(iss, c.start_time, '|');
		        getline(iss, c.end_time, '|');
		        getline(iss, c.total, '|');
		        stringstream ss(c.total);
			    ss>>km;
			    rm=km*50;
		        getline(iss, c.status);
		        if (c.status == "PENDING") {
		        		cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" ;
						cout << "Claim ID    : " << c.claim_id << "\n";
					    cout << "User ID     : " << c.user_id << "\n";
						cout << "Date        : " << c.date << "\n";
						cout << "Address     : " << c.address << "\n";
						cout << "Start Time  : " << c.start_time << "\n";
						cout << "End Time    : " << c.end_time << "\n";
						cout << "Total(Hour) : " << c.total << "\n\n";
						cout << "Total claim (1 HOUR x RM 50 )RM:"<<rm<<"\n";
						cout << "Status      : " << c.status << endl;
						cout <<"-----------------------------------------------"<<endl;
			        }
	        }
	        cout<<"Please enter the claim id that you want to make changes :";
			cin>>choice;
		    file.close();
		    return choice;
		}
		
		char viewPaper_marking_claim()
	    {
	    	ifstream file("papermark.txt");
	
	        if (!file.is_open()) {
	            cerr << "File don't exist !!!";
	        }
	
	        string line;
	        while (getline(file, line)) {
	            istringstream iss(line);
	            getline(iss, c.claim_id, '|');
		        getline(iss, c.user_id, '|');
		        getline(iss, c.subject, '|');
		        getline(iss, c.total, '|');
		        stringstream ss(c.total);
			    ss>>km;
			    rm=km*0.50;
		        getline(iss, c.status);
		        if (c.status == "PENDING") {
		        		cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" << "Claim ID  : " << c.claim_id << "\n";
					    cout << "User ID     : " << c.user_id << "\n";
						cout << "Subject     : " << c.subject << "\n";
						cout << "Total(paper): " << c.total << "\n\n";
						cout << "Total claim (1 PAPER x RM 0.50 )RM:"<<rm<<"\n";
						cout << "Status      : " << c.status << endl;
						cout <<"-----------------------------------------------"<<endl;
			        }
	        }
	        cout<<"Please enter the claim id that you want to make changes :";
			cin>>choice;
		    file.close();
		    return choice;
		}
		
		
		
};




class CheckHistory
{
	private:
		claim c;
		string targetUserId;
		float rm,km; 
	public:
		
		void viewPetrolClaim() {
			    ifstream file("petrol.txt");
				
			    if (!file.is_open()) {
			        cerr << "File don't exist !!!";
			    }
			
			    string line;
			    while (getline(file, line)) {
			        istringstream iss(line);
			        getline(iss, c.claim_id, '|');
			        getline(iss, c.user_id, '|');  
			        getline(iss, c.date, '|');
			        getline(iss, c.departure, '|');
			        getline(iss, c.destination, '|');
			        getline(iss, c.total, '|');
			        stringstream ss(c.total);
			        ss>>km;
			        rm=km*0.60;
			        getline(iss, c.start_time, '|');
			        getline(iss, c.end_time, '|');
			        getline(iss, c.status);

			        	cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" << "Claim ID    : " << c.claim_id << "\n";
				        cout << "User ID     : " << c.user_id << "\n";
				        cout << "Date        : " << c.date << "\n";
				        cout << "Departure   : " << c.departure << "\n";
				        cout << "Destination : " << c.destination << "\n";
				        cout << "Total       : " << c.total << "\n";
				        cout << "Start Time  : " << c.start_time << "\n";
				        cout << "End Time    : " << c.end_time << "\n\n";
				        cout << "Total claim (1KM x RM 0.60 )RM:"<<rm<<"\n";
				        cout << "Status      : " << c.status << endl;
				        cout <<"-----------------------------------------------"<<endl;
			        
			    }
		
		    file.close();
		}

	
	    void viewTollClaim() {
	        ifstream file("toll.txt");
	
	        if (!file.is_open()) {
	            cerr << "File don't exist !!!";
	        }
	
	        string line;
	        while (getline(file, line)) {
	            istringstream iss(line);
	            getline(iss, c.claim_id, '|');
		        getline(iss, c.user_id, '|');
		        getline(iss, c.date, '|');
		        getline(iss, c.departure, '|');
		        getline(iss, c.destination, '|');
		        getline(iss, c.total, '|');
		        stringstream ss(c.total);
			    ss>>km;
			    rm=km*0.30;
		        getline(iss, c.expenses, '|');
		        getline(iss, c.status);
		        
		        		cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" << "Claim ID          : " << c.claim_id << "\n";
			            cout << "User ID           : " << c.user_id << "\n";
				        cout << "Date              : " << c.date << "\n";
				        cout << "Departure         : " << c.departure << "\n";
				        cout << "Destination       : " << c.destination << "\n";
				        cout << "Total Distance(KM): " << c.total << "\n";
				        cout << "Expenses (RM)     : " << c.expenses << "\n\n";
				        cout << "Total claim (1KM x RM 0.30 )RM:"<<rm<<"\n";
				        cout << "Status            : " << c.status << endl;
				        cout <<"-----------------------------------------------"<<endl;
			       
	        }
	
	        file.close();
	    }
	    
	    void viewOvernight_stay_claim()
	    {
	    	ifstream file("overnight.txt");
	
	        if (!file.is_open()) {
	            cerr << "File don't exist !!!";
	        }
	
	        string line;
	        while (getline(file, line)) {
	            istringstream iss(line);
	            getline(iss, c.claim_id, '|');
		        getline(iss, c.user_id, '|');
		        getline(iss, c.date, '|');
		        getline(iss, c.address, '|');
		        getline(iss, c.days, '|');
		        getline(iss, c.expenses, '|');
		        stringstream ss(c.expenses);
			    ss>>km;
			    rm=km*100;
		        getline(iss, c.status);
		        
		        		cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" ;
						cout << "Claim ID             : " << c.claim_id << "\n";
					    cout << "User ID              : " << c.user_id << "\n";
						cout << "Date                 : " << c.date << "\n";
						cout << "Address              : " << c.address << "\n";
						cout << "Day                  : " << c.days << "\n";
						cout << "Expense(inclucde tax): " << c.expenses << "\n\n";
						cout << "Total claim (1 DAY x RM 100 )RM:"<<rm<<"\n";
						cout << "Status   : " << c.status << endl;
						cout <<"-----------------------------------------------"<<endl;
			        
	        }
	        
	        file.close();
		}
		
		void viewInstuction_claim()
	    {
	    	ifstream file("givetutorial.txt");
	
	        if (!file.is_open()) {
	            cerr << "File don't exist !!!";
	        }
	
	        string line;
	        while (getline(file, line)) {
	            istringstream iss(line);
	            getline(iss, c.claim_id, '|');
		        getline(iss, c.user_id, '|');
		        getline(iss, c.date, '|');
		        getline(iss, c.address, '|');
		        getline(iss, c.start_time, '|');
		        getline(iss, c.end_time, '|');
		        getline(iss, c.total, '|');
		        stringstream ss(c.total);
			    ss>>km;
			    rm=km*50;
		        getline(iss, c.status);
		        
		        		cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" ;
						cout << "Claim ID    : " << c.claim_id << "\n";
					    cout << "User ID     : " << c.user_id << "\n";
						cout << "Date        : " << c.date << "\n";
						cout << "Address     : " << c.address << "\n";
						cout << "Start Time  : " << c.start_time << "\n";
						cout << "End Time    : " << c.end_time << "\n";
						cout << "Total(Hour) : " << c.total << "\n\n";
						cout << "Total claim (1 HOUR x RM 50 )RM:"<<rm<<"\n";
						cout << "Status      : " << c.status << endl;
						cout <<"-----------------------------------------------"<<endl;
			        
	        }
	        
	        file.close();
	    }
		
		void viewPaper_marking_claim()
	    {
	    	ifstream file("papermark.txt");
	
	        if (!file.is_open()) {
	            cerr << "File don't exist !!!";
	        }
	
	        string line;
	        while (getline(file, line)) {
	            istringstream iss(line);
	            getline(iss, c.claim_id, '|');
		        getline(iss, c.user_id, '|');
		        getline(iss, c.subject, '|');
		        getline(iss, c.total, '|');
		        stringstream ss(c.total);
			    ss>>km;
			    rm=km*0.50;
		        getline(iss, c.status);
		        
		        		cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" << "Claim ID    : " << c.claim_id << "\n";
					    cout << "User ID     : " << c.user_id << "\n";
						cout << "Subject     : " << c.subject << "\n";
						cout << "Total(paper): " << c.total << "\n\n";
						cout << "Total claim (1 PAPER x RM 0.50 )RM:"<<rm<<"\n";
						cout << "Status      : " << c.status << endl;
						cout <<"-----------------------------------------------"<<endl;
			        
	        }
	        
	        file.close();
	    }
}; 

class CheckUser
{
	string user_id,username,user_ic,gender,contactNumber,email,caddress,paddress,state,city,poscode;
	string searchIC;
	
	public:
		void searchUserId()
		{
			ifstream file("User_Profile.txt");
			if (!file.is_open()) {
	            cerr << "File don't exist !!!";
	        }
	
	        string line;
	        do {
            cout << "\nPlease enter User IC : ";
            getline(cin >> ws, searchIC);

            bool found = false;

            while (getline(file, line)) {
                istringstream iss(line);
                getline(iss, user_id, '|');
	            getline(iss, username, '|');
		        getline(iss, user_ic, '|');
		        getline(iss, gender, '|');
		        getline(iss, contactNumber, '|');
		        getline(iss, email, '|');
		        getline(iss, caddress, '|');
		        getline(iss, paddress, '|');
				getline(iss, state, '|');
				getline(iss, city, '|');
				getline(iss, poscode, '|');

                if (searchIC == user_ic) {
                    found = true;
                    cout << "User ID           : " << user_id << "\n";
                    cout << "Name              : " << username << "\n";
                    cout << "IC Number         : " << user_ic << "\n";
                    cout << "Gender            : " << gender << "\n";
                    cout << "Contact Number    : " << contactNumber << "\n";
                    cout << "Email             : " << email << "\n";
                    cout << "Current Address   : " << caddress << "\n";
                    cout << "Permanent Address : " << paddress << "\n";
                    cout << "State             : " << state << "\n";
                    cout << "City              : " << city << "\n";
                    cout << "Postcode          : " << poscode << endl;
                    break; 
                }
            }

            if (!found) {
                cout << "User with IC " << searchIC << " not found." << endl;
            }

            cout << "\nDo you want to continue searching? (Y/N): ";
            char choice;
            cin >> choice;

            if (toupper(choice) != 'Y') {
                cout << "Press enter to return to the main page...";
                cin.ignore();
                
                cin.get();
                break;  
            }

            file.clear();
            file.seekg(0, ios::beg);

        } while (true);
	        
	        
	        file.close();
	        
		}
};

class change_status{
	int file_check;
	claim c;
	public :
		void change_petrol_status(char choice,Request &r){
			
			string i(1,choice);
			file_check=1;
			fstream file;
			file.open("petrol.txt");
			    if (!file.is_open()) {
			        cout<< "File don't exist !!!";
			    }
			    string line;
			    while (getline(file, line)) {
			        istringstream iss(line);
			        getline(iss, c.claim_id, '|');
			        getline(iss, c.user_id, '|');  
			        getline(iss, c.date, '|');
			        getline(iss, c.departure, '|');
			        getline(iss, c.destination, '|');
			        getline(iss, c.total, '|');
			        stringstream ss(c.total);
			        ss>>r.km;
			        r.rm=r.km*0.60;
			        getline(iss, c.start_time, '|');
			        getline(iss, c.end_time, '|');
			        getline(iss, c.status);
			        
			    
			        if(c.claim_id==i){
			        	system("cls");
			        	cout<<"Seleted Claim:"<<endl;
				        cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" << "Claim ID    : " << c.claim_id<< "\n";
				        cout << "User ID     : " << c.user_id << "\n";
				        cout << "Date        : " << c.date << "\n";
				        cout << "Departure   : " << c.departure << "\n";
				        cout << "Destination : " << c.destination << "\n";
				        cout << "Total       : " << c.total << "\n";
				        cout << "Start Time  : " << c.start_time << "\n";
				        cout << "End Time    : " << c.end_time << "\n\n";
				        cout << "Total claim (1km x RM 0.60 )RM:"<<r.rm<<"\n";
				        cout << "Status      : " << c.status << endl;
				        cout <<"-----------------------------------------------"<<endl;	
					}
					
			    }
			    file.close();
			    status(choice,file_check);
		    
		}
		void change_toll_status(char choice,Request &r){
			
			string i(1,choice);
			fstream file;
			file_check=2;
			file.open("toll.txt");
			    if (!file.is_open()) {
			        cout<< "File don't exist !!!";
			    }
			    string line;
	        while (getline(file, line)) {
	            istringstream iss(line);
	            getline(iss, c.claim_id, '|');
		        getline(iss, c.user_id, '|');
		        getline(iss, c.date, '|');
		        getline(iss, c.departure, '|');
		        getline(iss, c.destination, '|');
		        getline(iss, c.total, '|');
		        stringstream ss(c.total);
			    ss>>r.km;
			    r.rm=r.km*0.30;
		        getline(iss, c.expenses, '|');
		        getline(iss, c.status);
		        if (c.claim_id== i) {
		        		system("cls");
		        		cout<<"Seleted Claim:"<<endl;
		        		cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" << "Claim ID          : " << c.claim_id << "\n";
			            cout << "User ID           : " << c.user_id << "\n";
				        cout << "Date              : " << c.date << "\n";
				        cout << "Departure         : " << c.departure << "\n";
				        cout << "Destination       : " << c.destination << "\n";
				        cout << "Total Distance(KM): " << c.total << "\n";
				        cout << "Expenses (RM)     : " << c.expenses << "\n\n";
				        cout << "Total claim (1KM x RM 0.30 )RM:"<<r.rm<<"\n";
				        cout << "Status            : " << c.status << endl;
				        cout <<"-----------------------------------------------"<<endl;
			        }
	        }
			    file.close();
			    status(choice,file_check);
		}
		void change_overnight_status(char choice,Request &r){
			
			string i(1,choice);
			file_check=3;
			fstream file;
			file.open("overnight.txt");
			    if (!file.is_open()) {
			        cout<< "File don't exist !!!";
			    }
			    string line;
			    while (getline(file, line)) {
	            istringstream iss(line);
	            getline(iss, c.claim_id, '|');
		        getline(iss, c.user_id, '|');
		        getline(iss, c.date, '|');
		        getline(iss, c.address, '|');
		        getline(iss, c.days, '|');
		        getline(iss, c.expenses, '|');
		        stringstream ss(c.expenses);
			    ss>>r.km;
			    r.rm=r.km*100;
		        getline(iss, c.status);
		        if (c.claim_id == i) {
		        		system("cls");
		        		cout<<"Seleted Claim:"<<endl;
		        		cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" ;
						cout << "Claim ID             : " << c.claim_id << "\n";
					    cout << "User ID              : " << c.user_id << "\n";
						cout << "Date                 : " << c.date << "\n";
						cout << "Address              : " << c.address << "\n";
						cout << "Day                  : " << c.days << "\n";
						cout << "Expense(inclucde tax): " << c.expenses << "\n\n";
						cout << "Total claim (1 DAY x RM 100 )RM:"<<r.rm<<"\n";
						cout << "Status   : " << c.status << endl;
						cout <<"-----------------------------------------------"<<endl;
			        }
	        }
			    file.close();
			    status(choice,file_check);
		}
		void change_instruction_status(char choice,Request &r){
			string i(1,choice);
			file_check=4;
			fstream file;
			file.open("givetutorial.txt");
			    if (!file.is_open()) {
			        cout<< "File don't exist !!!";
			    }
			    string line;
			    while (getline(file, line)) {
	            istringstream iss(line);
	            getline(iss, c.claim_id, '|');
		        getline(iss, c.user_id, '|');
		        getline(iss, c.date, '|');
		        getline(iss, c.address, '|');
		        getline(iss, c.start_time, '|');
		        getline(iss, c.end_time, '|');
		        getline(iss, c.total, '|');
		        stringstream ss(c.total);
			    ss>>r.km;
			    r.rm=r.km*50;
		        getline(iss, c.status);
		        if (c.claim_id == i) {
		        		system("cls");
		        		cout<<"Seleted Claim:"<<endl;
		        		cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" ;
						cout << "Claim ID    : " << c.claim_id << "\n";
					    cout << "User ID     : " << c.user_id << "\n";
						cout << "Date        : " << c.date << "\n";
						cout << "Address     : " << c.address << "\n";
						cout << "Start Time  : " << c.start_time << "\n";
						cout << "End Time    : " << c.end_time << "\n";
						cout << "Total(Hour) : " << c.total << "\n\n";
						cout << "Total claim (1 HOUR x RM 50 )RM:"<<r.rm<<"\n";
						cout << "Status      : " << c.status << endl;
						cout <<"-----------------------------------------------"<<endl;
			        }
	       		}
			    file.close();
			    status(choice,file_check);
		}
		void change_papermark_status(char choice,Request &r){
			string i(1,choice);
			file_check=5;
			fstream file;
			file.open("papermark.txt");
			    if (!file.is_open()) {
			        cout<< "File don't exist !!!";
			    }
			    string line;
			    while (getline(file, line)) {
	            istringstream iss(line);
	            getline(iss, c.claim_id, '|');
		        getline(iss, c.user_id, '|');
		        getline(iss, c.subject, '|');
		        getline(iss, c.total, '|');
		        stringstream ss(c.total);
			    ss>>r.km;
			    r.rm=r.km*0.50;
		        getline(iss, c.status);
		        if (c.claim_id==i) {
		        		system("cls");
		        		cout<<"Seleted Claim:"<<endl;
		        		cout <<"-----------------------------------------------"<<endl;
			            cout << "\n" << "Claim ID  : " << c.claim_id << "\n";
					    cout << "User ID     : " << c.user_id << "\n";
						cout << "Subject     : " << c.subject << "\n";
						cout << "Total(paper): " << c.total << "\n\n";
						cout << "Total claim (1 PAPER x RM 0.50 )RM:"<<r.rm<<"\n";
						cout << "Status      : " << c.status << endl;
						cout <<"-----------------------------------------------"<<endl;
			        }
	        }
			    file.close();
			    status(choice,file_check);
		}
};

void status(char choice,int file_check){
	string search,line;
	char select ;
	
	do{
    	cout <<"Approve[1]/Reject[2]:";
    	cin>>select;
    	
    	if(toupper(select)!='1'&&toupper(select)!='2'){
    		cout<<"Invalid Selection";
		}
    	
	}while(toupper(select)!='1'&&toupper(select)!='2');
	
	ifstream inFile;
	if(file_check==1){
		inFile.open("petrol.txt");
	}else if(file_check==2){
		inFile.open("toll.txt");
	}else if(file_check==3){
		inFile.open("overnight.txt");
	}else if(file_check==4){
		inFile.open("givetutorial.txt");
	}else {
		inFile.open("papermark.txt");
	}
    ofstream tempFile("temp_file.txt");
	if(toupper(select)=='1'){
    		search = "APPROVED";
		}
	if(toupper(select)=='2'){
    		search = "REJECTED";
		}
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Error opening the file." << endl;
       exit(0);
    }
   
    bool updated = false;
    while (getline(inFile, line)) {
        if (!updated && line.size() > 0 && line[0] == choice) {
            size_t pos = line.find("PENDING");
            if (pos != string::npos) {
                line.replace(pos, 7, search);
               	 }
                updated = true;
            }
        
        tempFile << line << '\n';
    }
    inFile.close();
    tempFile.close();
	if(file_check==1){
		remove("petrol.txt");
		rename("temp_file.txt", "petrol.txt");
	}else if(file_check==2){
		remove("toll.txt");
		rename("temp_file.txt", "toll.txt");
	}else if(file_check==3){
		remove("overnight.txt");
		rename("temp_file.txt", "overnight.txt");
	}else if(file_check==4){
		remove("givetutorial.txt");
		rename("temp_file.txt", "givetutorial.txt");
	}else {
		remove("papermark.txt");
		rename("temp_file.txt", "papermark.txt");
	}
    
	cout<<"Status updated sucesssfull";
	Sleep(3000);
}

class Staff {
public:
	
	
	
	string 	staffID,staffPassword, staffName, staffIC, staffGender, staffContact,
	              staffEmail, staffCurrentAddress, staffPermanentAddress,
	              staffState, staffCity, staffPostcode;   
    bool login(string enteredStaffName, string enteredStaffPassword) {
        ifstream file;
		file.open("staff_login.txt");
        if (!file.is_open()) {
            cerr << "File don't exist !!!";
            return false;
        }

        string line;
        while (getline(file, line)) 
		{
            istringstream iss(line);
            getline(iss, staffID, '|');
			getline(iss, staffName, '|');
			getline(iss, staffPassword);
            
            if (enteredStaffName == staffName && enteredStaffPassword == staffPassword) {
                file.close();
                return true; // login successful
            }
        }

        file.close();
        return false; // login fail
        
        
    }
    
    void show_all_staff(){
    	ifstream staffInfoFile;
	    ifstream staffLoginFile;
	    staffInfoFile.open("staff_info.txt");
		staffLoginFile.open("staff_login.txt");
		string 	staffID, staffName, staffIC, staffGender, staffContact,
	              staffEmail, staffCurrentAddress, staffPermanentAddress,
	              staffState, staffCity, staffPostcode;
	    if (staffInfoFile.is_open() && staffLoginFile.is_open()) {
	        cout <<" All Staff information:"<<endl;
	        string lineInfo;
			
	        while (getline(staffInfoFile,lineInfo)) {
	            istringstream iss(lineInfo);
	            getline(iss, staffID , '|');
		        getline(iss, staffName, '|');
		        getline(iss,  staffIC, '|');
		        getline(iss, staffGender, '|');
		        getline(iss, staffContact, '|');
		        getline(iss, staffEmail, '|');
		        getline(iss,staffCurrentAddress, '|');
		        getline(iss, staffPermanentAddress, '|');
		        getline(iss, staffState, '|');
		        getline(iss,staffCity, '|');
		        getline(iss, staffPostcode);
	    		
	    		cout <<"-----------------------------------------------"<<endl;
				cout << "ID               : " << staffID << "\n";
			    cout << "Name             : " << staffName << "\n";
				cout << "IC               : " <<staffIC  << "\n";
				cout << "Gender           : " <<staffGender  << "\n";
				cout << "Contact          : " << staffContact << "\n";
				cout << "Email            : " <<staffEmail  << "\n";
				cout << "CurrentAddress   : " << staffCurrentAddress << "\n";
				cout << "PermanentAddress :"<<staffPermanentAddress<<"\n";
				cout << "State            : " << staffState  << endl;
				cout << "City             : " << staffCity  << endl;
				cout << "Postcode         : " << staffPostcode << endl;
				cout <<"-----------------------------------------------"<<endl;
	          
	        }
	
	        staffInfoFile.close();
	        staffLoginFile.close();
	    } else {
	        cerr << "Error: Unable to open staff_info.txt or staff_login.txt for reading.\n";
	        exit(0);
	    }
	}
	
	void search_staff_by_id(string id){
		ifstream staffInfoFile;
	    ifstream staffLoginFile;
	    staffInfoFile.open("staff_info.txt");
		staffLoginFile.open("staff_login.txt");
		
	    if (staffInfoFile.is_open() && staffLoginFile.is_open()) {
	        
	        string lineInfo;
			bool found =false;
	        while (getline(staffInfoFile,lineInfo)) {
	            istringstream iss(lineInfo);
	            getline(iss, staffID , '|');
		        getline(iss, staffName, '|');
		        getline(iss,  staffIC, '|');
		        getline(iss, staffGender, '|');
		        getline(iss, staffContact, '|');
		        getline(iss, staffEmail, '|');
		        getline(iss,staffCurrentAddress, '|');
		        getline(iss, staffPermanentAddress, '|');
		        getline(iss, staffState, '|');
		        getline(iss,staffCity, '|');
		        getline(iss, staffPostcode);
	    		if(staffID==id){
	    			found = true;
	    			cout <<" Selected Staff information:"<<endl;
	    			cout <<"-----------------------------------------------"<<endl;
					cout << "ID               : " << staffID << "\n";
				    cout << "Name             : " << staffName << "\n";
					cout << "IC               : " <<staffIC  << "\n";
					cout << "Gender           : " <<staffGender  << "\n";
					cout << "Contact          : " << staffContact << "\n";
					cout << "Email            : " <<staffEmail  << "\n";
					cout << "CurrentAddress   : " << staffCurrentAddress << "\n";
					cout << "PermanentAddress :"<<staffPermanentAddress<<"\n";
					cout << "State            : " << staffState  << endl;
					cout << "City             : " << staffCity  << endl;
					cout << "Postcode         : " << staffPostcode << endl;
					cout <<"-----------------------------------------------"<<endl;
				}
	    		
	          
	        }
			if (!found) {
                cout << "Staff ID with " << id << " not found." << endl;
            }
	        staffInfoFile.close();
	        staffLoginFile.close();
	    } else {
	        cerr << "Error: Unable to open staff_info.txt or staff_login.txt for reading.\n";
	        exit(0);
	    }
	}
	
	void delete_staff(string id){
		   // Open the input file
	 	ifstream staffInfoReadFile("staff_info.txt");
	    ifstream staffLoginReadFile("staff_login.txt");


	    ofstream tempStaffInfoFile("temp_staff_info.txt");
	    ofstream tempStaffLoginFile("temp_staff_login.txt");
		bool staffFound = false;
   		
   		string lineInfo, lineLogin;
		while (getline(staffInfoReadFile, lineInfo)){
			istringstream iss(lineInfo);
	        getline(iss, staffID , '|');
	        getline(iss, staffName, '|');
	        getline(iss,  staffIC, '|');
	        getline(iss, staffGender, '|');
	        getline(iss, staffContact, '|');
	        getline(iss, staffEmail, '|');
	        getline(iss,staffCurrentAddress, '|');
	        getline(iss, staffPermanentAddress, '|');
	        getline(iss, staffState, '|');
	        getline(iss,staffCity, '|');
	        getline(iss, staffPostcode);
	        cout<<staffID;
	        if (lineInfo.size() > 0 && staffID == id) {  
				staffFound = true;          
		        continue;
		              
			}	
			tempStaffInfoFile <<lineInfo << '\n';
		}
     
		while(getline(staffLoginReadFile, lineLogin)) { 
			istringstream iss(lineLogin);
		    getline(iss, staffID, '|');
	        getline(iss,staffName, '|');
	        getline(iss, staffIC);
			
			if (lineLogin.size() > 0 && staffID == id) {            
	            continue;
	            
			}
		    tempStaffLoginFile << lineLogin << '\n';
		        
		    }
		
		if(!staffFound){
			cout << "Staff ID with " << id << " not found." << endl;
		}
		staffInfoReadFile.close();
	    staffLoginReadFile.close();
	    tempStaffInfoFile.close();
	    tempStaffLoginFile.close();
	
	    if (staffFound) {
	        
	        remove("staff_info.txt");
	        remove("staff_login.txt");
	
	        // Rename the temporary files to the original names
	        rename("temp_staff_info.txt", "staff_info.txt");
	        rename("temp_staff_login.txt", "staff_login.txt");
	
	        cout << "\nStaff with ID " << id << " has been deleted.\n";
	    }
   
	}

};

class Admin :public Staff{

public:
    


    int login(const string& entered_name, const string& entered_password) const {
    	ifstream a;
    	a.open("admin.txt");
    	string admin_name;
    string admin_password;
    	string line;
    	while(getline(a,line)){
    		istringstream iss(line);
    		getline(iss,admin_name, '|');
    		getline(iss,admin_password, '|');
    		
    		if(entered_name == admin_name && entered_password == admin_password){
    			return 1;
			}else{
				return 2;
			}
		}
        
    }

    void displayMenu() const {
        system("cls");
        cout << "Admin Menu:\n";
        cout << "1. Staff\n";
        cout << "2. Claim\n";
    }
};

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string generateStaffID(int staffCount) {
    ostringstream oss;
    oss << setw(5) << setfill('0') << staffCount + 1;
    return oss.str();
}

void saveStaffLogin(const string& staffID, const string& username, const string& password) {
    ofstream loginFile("staff_login.txt", ios::app);
    if (loginFile.is_open()) {
        loginFile << staffID << "|" << username << "|" << password << endl;
        loginFile.close();
    } else {
        cerr << "Error: Unable to open staff_login.txt for writing.\n";
    }
}

void saveStaffInfo(const string& staffID, const string& name, const string& ic, const string& gender,
                   const string& contact, const string& email, const string& currentAddress,
                   const string& permanentAddress, const string& state, const string& city,
                   const string& postcode) {
    ofstream infoFile("staff_info.txt", ios::app);
    if (infoFile.is_open()) {
        infoFile << staffID << "|" << name << "|" << ic << "|" << gender << "|" << contact << "|"
                 << email << "|" << currentAddress << "|" << permanentAddress << "|" << state << "|"
                 << city << "|" << postcode << endl;
        infoFile.close();
    } else {
        cerr << "Error: Unable to open staff_info.txt for writing.\n";
    }
}

void display_claim(){
	Request request;
	count count;
	change_status cs;
	int reChoice;
	do {
		int petrolcount=0,tollcount=0,overnightcount=0,instructioncount=0,papermarkingcount=0;
		petrolcount=count.countPetrol();
		tollcount = count.countToll();
		overnightcount = count.countOvernight();
		instructioncount = count.countInstruction();
		papermarkingcount = count.countPapermarketing();
		system("cls");
	    cout << "\n1. Check Petrol Claim         | Pending claim application :" << petrolcount;
	    cout << "\n2. Check Toll Claim           | Pending claim application :" << tollcount;
	    cout << "\n3. Check Overnight Stay Claim | Pending claim application :" << overnightcount;
	    cout << "\n4. Check Instuction Claim     | Pending claim application :" << instructioncount;
	    cout << "\n5. Check Paper marking Claim  | Pending claim application :" << papermarkingcount;
	    cout << "\n6. End Check Claiming\n";
	    cout << "\nPlease select the claim you want to view : ";
	    cin >> reChoice;
		char select;
	    switch (reChoice) {
	        case 1:
	            select=request.viewPetrolClaim();
	            cs.change_petrol_status(select,request);
	            break;
	        case 2:
	            select=request.viewTollClaim();
	            cs.change_toll_status(select,request);
	            break;
	        case 3:
	            select=request.viewOvernight_stay_claim();
	            cs.change_overnight_status(select,request);
	            break;
	        case 4:
	            select=request.viewInstuction_claim();
	            cs.change_instruction_status(select,request);
	            break;
	        case 5:
	            select=request.viewPaper_marking_claim();
	            cs.change_papermark_status(select,request);
	            break;
	        case 6:
	            break;
	        default:
	            cout << "Have not this choise.\n";
	    }
	} while (reChoice != 6);
}


int main() {
	int choice;
	
	do{
		do{
			system("cls");
			cout<<"----------------------"<<endl;
			cout<<"VV E-claming System "<<endl;
			cout<<"----------------------"<<endl;
			cout<<"1.User"<<endl;
			cout<<"2.Staff"<<endl;
			cout<<"3.Admin"<<endl;
			cout<<"4.Exit"<<endl;
			cout<<"Enter your choice : ";
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
				staff_function();
				break;
				
			case 3:
				system("cls");
				admin_function();
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

void staff_function(){
	Staff loggedInStaff;
    claim c;
    
    int choice;
    

    while (true) {
        cout << "Enter Username: ";
        cin >> loggedInStaff.staffName;

        cout << "Enter Password: ";
        cin >> loggedInStaff.staffPassword;

        if (loggedInStaff.login(loggedInStaff.staffName, loggedInStaff.staffPassword)) {
        	system("cls");
            cout << "\nLogin Successful\n";
            cout << "\n===========================================" << endl;
            cout << "\tWelcome Back " << loggedInStaff.staffName << endl;
            cout << "===========================================" << endl;

            while (true) {
                claim_choice();
            }

            break; 
        } else {
            cout << "\nLogin Fail. Please check the Username and Password!!!\n" << endl;
        }
    }

}

void claim_choice(){
	int choice;
	CheckHistory history;
    CheckUser User;
    system("cls");
	cout << "\n1. Check Claim\n";
    cout << "2. Check History\n";
    cout << "3. Check User\n";
    cout << "4. Log out\n";
    cout << "\nPlease select the action you need to perform : ";
    cin >> choice;

    switch (choice) {
        case 1:
            display_claim();
            
            break;
        case 2:
        	int hisChoice;
            do {
            	system("cls");
                cout << "\n1. Check Petrol Claim History\n";
                cout << "2. Check Toll Claim History\n";
                cout << "3. Check Overnight Stay Claim History\n";
                cout << "4. Check Instuction Claim History\n";
                cout << "5. Check Paper marking Claim History\n";
                cout << "6. End Check Claim History\n";
                cout << "\nPlease choise the history you want to view : ";
                cin >> hisChoice;

                switch (hisChoice) {
                    case 1:
                        history.viewPetrolClaim();
                        break;
                    case 2:
                        history.viewTollClaim();
                        break;
                    case 3:
                        history.viewOvernight_stay_claim();
                        break;
                    case 4:
                        history.viewInstuction_claim();
                        break;
                    case 5:
                        history.viewPaper_marking_claim();
                        break;
                    case 6:
                        break;
                    default:
                        cout << "Have not this choise\n";
                }
                cout<<"Press any key to continue ....";
				cin.ignore();
				cin.ignore();
                
            } while (hisChoice != 6);
            break;
        case 3:
        	User.searchUserId();
        	break;
        case 4:
            cout << "Log out Successful\n";
            Sleep(2000);
            exit(0);
            break;
        default:
            cout << "Have not this choise\n";
    }

}

void admin_function(){
	Admin admin;
    const int maxLoginAttempts = 3;
    int loginAttempts = 0;

    while (loginAttempts < maxLoginAttempts) {
        string entered_name, entered_password;

        cout << "Enter Admin Name: ";
        getline(cin >> ws, entered_name);

        cout << "Enter Admin Password: ";
        getline(cin >> ws, entered_password);
		system("cls ");
        if (admin.login(entered_name, entered_password)==1) {
            cout << "\nLogin successful!\n";

            entered_name.clear();
            entered_password.clear();
			
            // Introduce a 3-second delay before clearing the console
           	Sleep(3000);

            // Clear the console after 3 seconds
            system("cls ");
            bool backToAdminMenu = false;

			adminMenuLabel:
            while (true) {
                admin.displayMenu();
                bool backToAdminMenu = false;

                int choice;
                cout << "Enter your choice (1 or 2): ";
                cin >> choice;

                switch (choice) {
                    case 1: {
                        // Introduce a 3-second delay before clearing the console
                       

                        // Clear the console after 3 seconds
                        system("cls");

                        while (true) {
                            cout << "Staff Menu:\n";
                            cout << "1. Add Staff\n";
                            cout << "2. Delete Staff\n";
                            cout << "3. Show All Staff Info\n";
                            cout << "4. Search Staff by Staff ID\n";
                            cout << "5. Back to Admin Menu\n";

                            int staffChoice;
                            cout << "Enter your choice : ";
                            cin >> staffChoice;

                            switch (staffChoice) {
                                case 1: {
                                    
                                    system("cls ");

                                    cout << "Adding Staff:\n";
									cin.ignore();
                                    string staffUsername, staffPassword;
                                    cout << "Enter Staff Username: ";
                                    getline(cin,staffUsername);

                                    cout << "Enter Staff Password: ";
                                    getline(cin,staffPassword);

                                    // Generate a staff ID
                                    int staffCount = 0;
                                    ifstream loginFile("staff_login.txt");
                                    if (loginFile.is_open()) {
                                        string line;
                                        while (getline(loginFile, line)) {
                                            staffCount++;
                                        }
                                        loginFile.close();
                                    } else {
                                        cerr << "Error: Unable to open staff_login.txt for reading.\n";
                                    }

                                    string staffID = generateStaffID(staffCount);

                                    // Save login information to staff_login.txt
                                    saveStaffLogin(staffID, staffUsername, staffPassword);

                                    // Get staff details
                                    string staffName, staffIC, staffGender, staffContact, staffEmail,
                                           staffCurrentAddress, staffPermanentAddress, staffState, staffCity,
                                           staffPostcode;

                                    cout << "Enter Staff Name: ";
                                     
                                    getline(cin, staffName);
									
                                    cout << "Enter Staff IC: ";
                                    getline(cin, staffIC);
									
                                    cout << "Enter Staff Gender: ";
                                    getline(cin, staffGender);
									
                                    cout << "Enter Staff Contact: ";
                                    getline(cin, staffContact);

                                    cout << "Enter Staff Email: ";
                                    getline(cin, staffEmail);

                                    cout << "Enter Staff Current Address: ";
                                    getline(cin, staffCurrentAddress);

                                    cout << "Enter Staff Permanent Address: ";
                                    getline(cin, staffPermanentAddress);

                                    cout << "Enter Staff State: ";
                                    getline(cin, staffState);

                                    cout << "Enter Staff City: ";
                                    getline(cin, staffCity);

                                    cout << "Enter Staff Postcode: ";
                                    getline(cin, staffPostcode);

                                    // Save staff information to staff_info.txt
                                    saveStaffInfo(staffID, staffName, staffIC, staffGender, staffContact,
                                                  staffEmail, staffCurrentAddress, staffPermanentAddress,
                                                  staffState, staffCity, staffPostcode);

                                    cout << "\nStaff added successfully!\n";

                                    // Introduce a 3-second delay before clearing the console
                                    Sleep(3000);

                                    // Clear the console after 3 seconds
                                    system("cls || clear");

                                    break;
                                }

                                case 2: {
                                    
                                    system("cls || clear");

                                    cout << "Delete Staff:\n";

                                    // Display a list of all staff members with their IDs and names
                                    
                                    admin.show_all_staff();

                                    // Ask the user to enter the staff ID to delete
                                    string staffIDToDelete;
                                    cin.ignore();
                                    cout << "Enter the Staff ID to delete: ";
                                    getline(cin,staffIDToDelete);

                                    admin.delete_staff(staffIDToDelete);
                                    cout<<"Press any key to continue ....";
									cin.ignore();
									
									break;
                                }
								
								case 3: {
									// Introduce a 3-second delay before clearing the console
								    
								
								    // Clear the console after 3 seconds
								    system("cls");

								    cout << "Search Staff Info:\n";
								
								    
								    admin.show_all_staff();
								    Sleep(3000);
								    cout<<"Press any key to continue ....";
									cin.ignore();
									cin.ignore();
								
								    break;
								}


								case 4:{
									string id;
									system("cls");
									Staff *s =new Staff;
									cin.ignore();
									cout<<"Pleaser Enter the Staff id that you want to search :";
									getline(cin,id);
									s->search_staff_by_id(id);
									cout<<"Press any key to continue ....";
									cin.ignore();
									delete s;
									break;
									
								}
									
									
                                case 5:{
                                	system("cls ");

								    goto adminMenuLabel;
								    
									break;
								}

                                default:
                                    cout << "Invalid choice.\n";
                                    
                                    system("cls ");
                                    continue;
                            }

                            // Introduce a 3-second delay before clearing the console
                           

                            // Clear the console after 3 seconds
                            system("cls ");

                            if (backToAdminMenu) {
                                // Exit the Staff Menu loop
                                break;
                            }
                        }
                        break;
                    }

                    case 2:
                    	system("cls");
                        claim_choice();
                        break;

                    default:
                        cout << "Invalid choice. Please enter 1 or 2.\n";
                        
                        system("cls ");
                        continue;
                }

                // Introduce a 3-second delay before clearing the console
               

                // Clear the console after 3 seconds
                system("cls ");
                 // Exit the Admin Menu loop
            }

            loginAttempts = 0;
        } else {
            loginAttempts++;

            entered_name.clear();
            entered_password.clear();

            cout << "\nAdmin name or password is incorrect. ";
            cout << "Attempts left: " << (maxLoginAttempts - loginAttempts) << endl;

            if (loginAttempts == maxLoginAttempts) {
                cout << "Maximum login attempts reached. Program terminated.\n";
                break;
            }

            // Introduce a 3-second delay before clearing the console
            Sleep(3000);

            // Clear the console after 3 seconds
            system("cls ");
        }
    }

}
