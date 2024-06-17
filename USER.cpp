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

struct ClaimDetail 
{
    string categoryID;
    string st;
    string type;
    string t;
    string u;
    string v;
    string w;
    string x;
    string y;
    string z;
};

// Struct to store additional user input data
struct InsertData 
{
	string st;
	string type;
	string t;
	string u;
    string v;
	string w;
    string x;
    string y;
    string z;
};

struct Claim 
{
    string id;
    string categoryID;
    string type;
    string date;
    string from;
    string to;
    string total_distance;
    string total_claim;
    string status;
    string start;
    string end;
    string rid;
};

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

class Person 
{
	public:
	    string userID;
	    string username;
	    string password;
	
	    Person(){}
	
	    Person(string userID, string username, string password): userID(userID), username(username), password(password) {}
};

class ADTqueue 
{
	private:
	    Person queue[50];
	    int head, tail;
	
	public:
	    ADTqueue()
		{
	        tail = -1;
	        head = 0;
	    }
	
	    int empty()
		{
	        return head > tail;
	    }
	
	    int full()
		{
	        return tail == 49;
	    }
	
	    void append(Person p)
		{
	        if (!full()) 
			{
	            tail++;
	            queue[tail] = p;
	        } 
			else 
			{
	            cout << "Queue is Full" << endl;
	        }
	    }
	
	    Person serve() 
		{
	        Person p;
	        if (!empty()) 
			{
	            p = queue[head];
	            head++;
	            return p;
	        } 
			else 
			{
	            cout << "Queue is Empty" << endl;
	            return p;
	        }
	    }
	
	    void loadFromFile() 
		{
	        ifstream file("user_login.txt");
	        string line;
	        while (getline(file, line)) 
			{
	            stringstream ss(line);
	            string userID, username, password;
	
	            if (getline(ss, userID, '|') && getline(ss, username, '|') && getline(ss, password, '|')) 
				{
	                Person p(userID, username, password);
	                append(p);
	            }
	        }
	        file.close();
	    }
	
		void saveToFile() 
		{
	        ofstream file("user_login.txt");
	        if (!file.is_open()) 
			{
	            cout << "Error opening file" << endl;
	            return;
	        }
	
	        for (int i = head; i <= tail; ++i) 
			{
	            file << queue[i].userID << "|" << queue[i].username << "|" << queue[i].password << "|" << endl;
	        }
	        file.close();
	    }
	
	    void displayQueue() 
		{
	        for (int i = head; i <= tail; ++i) 
			{
	            cout << "ID: " << queue[i].userID << ", Name: " << queue[i].username << ", Password: " << queue[i].password << endl;
	        }
	    }
	
	    bool login(string lgn, string passwd, string &userID) 
		{
	    	char ch,ch1;
			string choice1;
	        for (int i = head; i <= tail; ++i) 
			{
	            if (queue[i].username == lgn && queue[i].password == passwd) 
				{
	            	userID = queue[i].userID;
	                return true;
	            }
	        }
	        return false;
	    }
	
	    bool registerUser(string username) 
		{
	        // Check if username already exists
	        for (int i = head; i <= tail; ++i) 
			{
	            if (queue[i].username == username) 
				{
	                return false;
	            }
	        }
	        return true;
	    }
};

bool isValidPostcode(const string& postcode)
{
    // Check if postcode is exactly 5 digits
    if (postcode.length() != 5)
    {
        return false;
    }

    // Check if all characters are digits
    for (size_t i = 0; i < postcode.length(); ++i)
	{
	    char ch = postcode[i];
	    if (!isdigit(ch))
	    {
	        return false;
	    }
	}
  	// If passed all checks, postcode is valid
    return true;
}

bool isValidIC(const string& ic)
{
    // Check if ic is exactly 12 digits
    if (ic.length() != 12)
    {
        return false;
    }

    // Check if all characters are digits
    for (size_t i = 0; i <ic.length(); ++i)
	{
	    char ch = ic[i];
	    if (!isdigit(ch))
	    {
	        return false;
	    }
	}
  	// If passed all checks, ic is valid
    return true;
}

bool isValidph(const string& contactNumber)
{
    // Check if phone number is exactly 8/9 digits
    if (contactNumber.length() != 8 || contactNumber.length() !=9)
    {
        return false;
    }

    // Check if all characters are digits
    for (size_t i = 0; i <contactNumber.length(); ++i)
	{
	    char ch = contactNumber[i];
	    if (!isdigit(ch))
	    {
	        return false;
	    }
	}
  	// If passed all checks, phone number is valid
    return true;
}

void merge(Claim* claims, int left, int mid, int right, int sortBy) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Claim* L = new Claim[n1];
    Claim* R = new Claim[n2];

    for (int i = 0; i < n1; ++i)
        L[i] = claims[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = claims[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (sortBy == 2) { // Sort by category
            if (L[i].type <= R[j].type) {
                claims[k] = L[i];
                ++i;
            } else {
                claims[k] = R[j];
                ++j;
            }
        } else { // Default: sort by ID
            if (L[i].id <= R[j].id) {
                claims[k] = L[i];
                ++i;
            } else {
                claims[k] = R[j];
                ++j;
            }
        }
        ++k;
    }

    while (i < n1) {
        claims[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        claims[k] = R[j];
        ++j;
        ++k;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(Claim* claims, int left, int right, int sortBy) 
{
    if (left < right) 
	{
        int mid = left + (right - left) / 2;

        mergeSort(claims, left, mid, sortBy);
        mergeSort(claims, mid + 1, right, sortBy);

        merge(claims, left, mid, right, sortBy);
    }
}

void displayClaims(const Claim* claims, int size) 
{
	string line;
	ifstream detailFile("claim_detail.txt");
        if (!detailFile) 
		{
            cerr << "Unable to open file claim_detail.txt" << endl;
            return;
        }

        bool found = false;
        ClaimDetail selectedClaim;

        while (getline(detailFile, line))
		{
		    istringstream iss(line);
		    string categoryID, date, from, to, total_distance, total_claim, status, st, start, end;
		
		    getline(iss, categoryID, '|');
		    getline(iss, date, '|');
		    getline(iss, from, '|');
		    getline(iss, to, '|');
		    getline(iss, start, '|');
		    getline(iss, end, '|');
		    getline(iss, total_distance, '|');
		    getline(iss, total_claim, '|');
		
		    // Assigning values to selectedClaim
		    selectedClaim.categoryID = categoryID;
		    selectedClaim.t = date;
		    selectedClaim.u = from;
		    selectedClaim.v = to;
		    selectedClaim.w = start;
		    selectedClaim.x = end;
		    selectedClaim.y = total_distance;
		    selectedClaim.z = total_claim;
		}

        detailFile.close();
        
	    for (int i = 0; i < size; ++i) 
		{
	    	cout<<endl;
	        const Claim& claim = claims[i];
	        cout << "RID : " << claim.rid<<endl;
			cout << "Claim Type : " << claim.type <<endl;
			cout << "Status     : " <<claim.status <<endl;
			cout << selectedClaim.t << " : " <<claim.date <<endl;
			cout << selectedClaim.u << " : " <<claim.from <<endl; 
			cout << selectedClaim.v << " : " <<claim.to <<endl;
			cout << selectedClaim.w << " : " <<claim.start <<endl;
			cout << selectedClaim.x << " : " <<claim.end <<endl;
			cout << selectedClaim.y << " : " <<claim.total_distance <<endl;
			cout << selectedClaim.z << " : " <<claim.total_claim <<endl; 
		}
}

int binarySearch(Claim claims[], int low, int high, string categoryToSearch) 
{
    while (low <= high) 
	{
        int mid = low + (high - low) / 2;
        
        // Compare categoryToSearch with the category of the claim at mid
        if (claims[mid].rid == categoryToSearch)
            return mid;  // Found the category, return index
        else if (claims[mid].rid < categoryToSearch)
            low = mid + 1;  // Category might be in the upper half
        else
            high = mid - 1; // Category might be in the lower half
    }
    return -1;  // Category not found
}

int rid_auto_increment() 
{
    ifstream readfile("claim_request.txt");
    int max = 0, check;
    if (!readfile) 
	{
        cout << "Unable to open file for reading" << endl;
    }
    string line;
    while (getline(readfile, line)) 
	{
        istringstream iss(line);
        string rid_str;
        getline(iss, rid_str, '|');
        stringstream ss(rid_str);
        ss >> check;
        if (check > max) 
		{
            max = check;
        }
        // Assuming the rest of the line is not relevant for `rid` auto-increment
    }
    max++;
    readfile.close();
    return max;
}

class User 
{
	private:
	    string userID, name, ic, gender, contactNumber, email, caddress, paddress, state, city, poscode, username, password;
	    char choice;
	    int uID;
	    ADTqueue ADT;
	
	public:
	    User() 
		{
	        uID = 1;
	    }
	
	    void user_profile() {
            ifstream u_profile("User_Profile.txt");
            ofstream user_profile;
            user_profile.open("User_Profile.txt", ios::app);

            if (u_profile.is_open()) 
			{
                string line;
                while (getline(u_profile, line)) {
                    uID=uID;
                }
                u_profile.close();
            }

            system("cls");
            cout << "*****************************" << endl;
            cout << "\tREGISTRATION" << endl;
            cout << "*****************************" << endl;
            cout << "Name                 : ";
           
            getline(cin, name);
            cout << "IC Number            : ";
            getline(cin, ic);
            while (!isValidIC(ic)) 
			{
                cout << "Invalid IC format. Please enter a valid 12-digit IC£¡" << endl;
                cout << "IC Number            : ";
                getline(cin, ic);
            }
            cout << "Gender (Male/Female) : ";
            getline(cin, gender);
            cout << "Contact Number       : +601";
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

            while (!isValidPostcode(poscode)) {
                cout << "Invalid Postcode format. Please enter a valid 5-digit postcode£¡" << endl;
                cout << "Postcode             : ";
                getline(cin, poscode);
            }

            if (user_profile.is_open()) {
                user_profile << uID << "|" << name << "|" << ic << "|" << gender << "|" << contactNumber << "|" << email << "|" << caddress << "|" << paddress << "|" << state << "|" << city << "|" << poscode << "|" << endl;
                user_profile.close();
            }
            // Assuming index() function is defined elsewhere
            index(userID);
        }

        void promtprofile(string id) 
		{
            system("cls");
            ifstream inputFile;
            inputFile.open("User_Profile.txt");
            string line;

            while (getline(inputFile, line)) {
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

                if (id == userID) 
				{
                    cout << "+------------------------------------------------+" << endl;
                    cout << "Name              : " << name << endl;
                    cout << "IC                : " << ic << endl;
                    cout << "Gender            : " << gender << endl;
                    cout << "Contact Number    : " << contactNumber << endl;
                    cout << "Email             : " << email << endl;
                    cout << "Current Address   : " << caddress << endl;
                    cout << "Permenant Address : " << paddress << endl;
                    cout << "State             : " << state << endl;
                    cout << "City              : " << city << endl;
                    cout << "Poscode           : " << poscode << endl;
                    cout << "+------------------------------------------------+" << endl;
                }
            }
            inputFile.close();

            do {
                cout << "Press E to Continue to Main : ";
                cin >> choice;
                if (choice == 'E' || choice == 'e') {
                    // Assuming index() function is defined elsewhere
                    // index(userID);
                } else {
                    cout << "Sorry, you entered the wrong code." << endl << endl;
                    cout << "Press E to Continue to Main : ";
                    cin >> choice;
                }
            } while (choice != 'E' && choice != 'e');
            system("cls");
        }

        void registration() {
            char yeayah[2];
            system("cls");

            cout << "************************************************" << endl;
            cout << "\t\tJoin Us Today!" << endl;
            cout << "************************************************" << "\n\n";

            cout << "Do you want to register? [Enter Y to continue] : ";
            cin >> yeayah;

            if (strlen(yeayah) > 1) {
                return;
            } else if (yeayah[0] == 'Y' || yeayah[0] == 'y') {
                AddNewUser();
                system("pause");
            } else {
                return;
            }
        }

        void AddNewUser() {
            string unm;
            string psswd;
            string psswd2;
			char save[2];

            ifstream u_login("user_login.txt");
            ofstream user_login;
            user_login.open("user_login.txt", ios::app);
            string line;
            while (getline(u_login, line)) {
                uID++;
            }

            cout << "User ID: "  << uID << endl;

            fflush(stdin);
            cout << "Username (at most 8 characters) : ";
            getline(cin, unm);

            while (unm.length() <= 0 || unm.length() > 8) {
                cout << "Only at most 8 characters! Please try again.\n" << endl;
                fflush(stdin);
                cout << "Username (at most 8 characters) : ";
                getline(cin, unm);
            }

            fflush(stdin);
            cout << "Password (at most 8 characters) : ";
            getline(cin, psswd);

            while (psswd.length() < 0 || psswd.length() > 8) {
                cout << "Only at most 8 characters! Please try again.\n" << endl;
                fflush(stdin);
                cout << "Password (at most 8 characters) : ";
                getline(cin, psswd);
            }
            psswd2 = "";
            while (psswd2 != psswd) {
                fflush(stdin);
                cout << "Confirm your password : ";
                getline(cin, psswd2);
                if (psswd2 != psswd) {
                    cout << "\n>Both passwords are not the same! Please try again. <\n\n";
                }
            }
            cout << endl << "Is all your information correct? [Enter Y to save] :";
            cin >> save;

            if (strlen(save) > 1) {
                return;
            }
            if (save[0] == 'Y' || save[0] == 'y') {
                ofstream user_login("user_login.txt", ios::app);
                if (!user_login) {
                    system("cls");
                    cout << "File doesn't exist";
                    exit(0);
                }
                user_login << uID;
                user_login << "|" << unm << "|" << psswd << "|" << endl;
                user_login.close();
                cout << "\n>Your account is created successfully! Try to login now!" << "\n";
                // Assuming login() function is defined elsewhere
                // login();
            }
        }
	
	    void login() 
		{
		    string lgn;
		    string passwd;
		    string getup;
		    char ch, ch1;
		    string choice1;
		    ADT.loadFromFile();
		
		    for (int z = 0; z < 3; z++) 
		    {
		        system("cls");
		        cout << "****************************************" << endl;
		        cout << "\tLogin with your account!" << endl;
		        cout << "****************************************";
		        cout << endl;
		        cout << "Exit [Type E]" << "\n\n";
		        lgn = "";
		        passwd = "";
		        fflush(stdin);
		        cout << "Username : ";
		        getline(cin, lgn);
		        if (lgn == "E" || lgn == "e") 
		        {
		            return;
		        } 
		        else
		        {
		            cout << endl;
		            fflush(stdin);
		            cout << "Password : ";
		            getline(cin, passwd);
		            string userID;
		            if (ADT.login(lgn, passwd, userID))
		            {
		                system("cls");
		                cout << "Login Successfully!" << endl << endl;
		                cout << "Debug: UserID after login: " << userID << endl; // Debug statement
		
		                if (isProfileFilled(userID)) 
		                {
		                    index(userID);
		                } 
		                else 
		                {
		                    cout << "You haven't filled in your personal information yet. Please fill in your profile." << endl;
		                    user_profile();
		                }
		                return;
		            }
		            else
		            {
		                cout << endl << "Invalid Username or Password Entered! \nPlease try again.";
		                system("pause");
		                return login();
		            }   
		        }
	    	}
		}
	    
		
	    bool isProfileFilled(string& ID)
		{
	        ifstream inputFile("User_Profile.txt");
	        string line;
	        while (getline(inputFile, line)) 
			{
	            istringstream iss(line);
	            getline(iss, userID, '|');
	            if (userID == ID) 
				{
	                return true;
	            }
	        }
	        return false;
	    }
	
	   bool isValidPostcode(const string &postcode) 
	   {
		    if (postcode.length() != 5) return false;
		    for (size_t i = 0; i < postcode.length(); ++i) 
			{
		        if (!isdigit(postcode[i])) return false;
		    }
		    return true;
		}
		
		bool isValidIC(const string &ic) 
	   	{
		    if (ic.length() != 12) return false;
		    for (size_t i = 0; i < ic.length(); ++i) 
			{
		        if (!isdigit(ic[i])) return false;
		    }
		    return true;
		}
		
		bool isValidph(const string &contactNumber) 
	   	{
		    if (contactNumber.length() != 8 || contactNumber.length() !=9)
		    {
		    	return false;
			}
		    for (size_t i = 0; i < contactNumber.length(); ++i) 
			{
		        if (!isdigit(contactNumber[i])) return false;
		    }
		    return true;
		}    
};

class claiming : public User 
{
	public:
	    string categoryID_input;
	
	    void processClaim(string userID) 
		{
	        system("cls");
	
	        ifstream inFiles("claim.txt");
	        if (!inFiles) 
			{
	            cout << "Unable to open file claim.txt" << endl;
	            return;
	        }
	
	        string line;
	        cout << "\t+-------Type of Claim-------+" << endl;
	        cout << " " << endl;
	        while (getline(inFiles, line)) 
			{
	            istringstream iss(line);
	            string categoryID, claim_name;
	
	            getline(iss, categoryID, '|');
	            getline(iss, claim_name, '|');
	
	            cout << "\t    [" << categoryID << "] " << claim_name << endl;
	        }
	
	        inFiles.close();
	        cout << " " << endl;
	        cout << "\t+---------------------------+" << endl;    
	        cout << "\t    Enter Your Choice: ";
	        getline(cin >> ws, categoryID_input);
	
	        // Debug statement to check input
	        cout << "Category ID Input: " << categoryID_input << endl;
	
	        // Find the category name
	        string selectedCategoryName;
	        ifstream categoryFile("claim.txt");
	        if (!categoryFile) 
			{
	            cout << "Unable to open file claim.txt" << endl;
	            return;
	        }
	
	        bool categoryFound = false;
	        while (getline(categoryFile, line)) 
			{
	            istringstream iss(line);
	            string categoryID, claim_name;
	
	            getline(iss, categoryID, '|');
	            getline(iss, claim_name, '|');
	
	            if (categoryID == categoryID_input) 
				{
	                selectedCategoryName = claim_name;
	                categoryFound = true;
	                break;
	            }
	        }
	
	        categoryFile.close();
	
	        if (!categoryFound) 
			{
	            cout << "Category ID not found in claim.txt" << endl;
	            return;
	        }
	
	        // Open claim_detail.txt file and find the matching claim item details
	    
			ifstream detailFile("claim_detail.txt");
	        if (!detailFile) 
			{
	            cerr << "Unable to open file claim_detail.txt" << endl;
	            return;
	        }
	
	        bool found = false;
	        ClaimDetail selectedClaim;
	
	        while (getline(detailFile, line))
			{
			    istringstream iss(line);
			    string categoryID, date, from, to, total_distance, total_claim, status, st, start, end;
			
			    getline(iss, categoryID, '|');
			    getline(iss, date, '|');
			    getline(iss, from, '|');
			    getline(iss, to, '|');
			    getline(iss, start, '|');
			    getline(iss, end, '|');
			    getline(iss, total_distance, '|');
			    getline(iss, total_claim, '|');
			
			    // Assigning values to selectedClaim
			    selectedClaim.categoryID = categoryID;
			    selectedClaim.t = date;
			    selectedClaim.u = from;
			    selectedClaim.v = to;
			    selectedClaim.w = start;
			    selectedClaim.x = end;
			    selectedClaim.y = total_distance;
			    selectedClaim.z = total_claim;
			}

	        detailFile.close();
			
	        if (!found) 
			{
	            system("cls");
	            InsertData userInsertData;
	            int rid = rid_auto_increment();
	            cout << "\t+---" << selectedCategoryName << "---+" << endl;
	            cout << " " << endl;
	            cout << "\t" << selectedClaim.t << ": ";
	            getline(cin >> ws, userInsertData.t);
	            cout << "\t" << selectedClaim.u << ": ";
	            getline(cin >> ws, userInsertData.u);
	            cout << "\t" << selectedClaim.v << ": ";
	            getline(cin >> ws, userInsertData.v);
	            cout << "\t" << selectedClaim.w << ": ";
	            getline(cin, userInsertData.w);
	            cout << "\t" << selectedClaim.x << ": ";
	            getline(cin, userInsertData.x);
	            cout << "\t" << selectedClaim.y << ": ";
	            getline(cin, userInsertData.y);
	            cout << "\t" << selectedClaim.z << ": ";
	            getline(cin, userInsertData.z);
	            cout << "\t+---------------------------+" << endl;
	
	            cout << "\nInformation:" << endl;
	            cout << selectedClaim.t << ": " << userInsertData.t << endl;
	            cout << selectedClaim.u << ": " << userInsertData.u << endl;
	            cout << selectedClaim.v << ": " << userInsertData.v << endl;
	            cout << selectedClaim.w << ": " << userInsertData.w << endl;
	            cout << selectedClaim.x << ": " << userInsertData.x << endl;
	            cout << selectedClaim.y << ": " << userInsertData.y << endl;
	            cout << selectedClaim.z << ": " << userInsertData.z << endl;
	            
	            ofstream outFile("claim_request.txt", ios::app);
	            if (!outFile) 
				{
	                cerr << "Unable to open file claim_request.txt" << endl;
	                return;
	            }
	
	            outFile << "\n" << rid << "|" << userID << "|" << selectedCategoryName << "|" << "PENDING" << "|" << userInsertData.t << "|" << userInsertData.u << "|" << userInsertData.v << "|" << userInsertData.w << "|" << userInsertData.x << "|" << userInsertData.y << "|" << userInsertData.z << "|";
	            outFile.close();
	
	            cout << "\nData has been successfully saved!!!" << endl;
	            
	        } 
			else 
			{
	            cout << "No details found for the selected claim item." << endl;
	        }
	        cout << "Press Enter" << endl;
	        system("pause"); // Use system("pause") instead of system("cls") to wait for user input
	        system("cls");
	    }
	
	    friend class check;
};

class check : public User
{
	public:
	    void processCheck(string userID) 
		{
	        system("cls"); // Clear screen
	
	        const int MAX_CLAIMS = 100;  // Maximum number of claims to handle
	        Claim claims[MAX_CLAIMS];    // Array to store claims
	        int count = 0;               // Counter for number of claims found
	 
	        // Read claims from file
	        ifstream inFile("claim_request.txt");
			if (!inFile) 
			{
			    cerr << "Failed to open file claim_request.txt." << endl;
			    return;
			}
			
			string line;
			while (getline(inFile, line) && count < MAX_CLAIMS) 
			{
			    stringstream ss(line);
			    string rid;
			    getline(ss, claims[count].rid, '|');
			    getline(ss, claims[count].id, '|');
			    getline(ss, claims[count].type, '|');
			    getline(ss, claims[count].status, '|');
			    getline(ss, claims[count].date, '|');
			    getline(ss, claims[count].from, '|');
			    getline(ss, claims[count].to, '|');
			    getline(ss, claims[count].start, '|');
			    getline(ss, claims[count].end, '|');
			    getline(ss, claims[count].total_distance, '|');
			    getline(ss, claims[count].total_claim, '|');
			
			    if (claims[count].id == userID) 
				{
			        count++;  // Increment count only if the claim belongs to userID
			    }
			}
			inFile.close();
	
	        if (count == 0) 
			{
	            cout << "No claims found for ID " << userID << "." << endl;
	            return;
	        }
	
	        // Ask user for sorting preference
	        char sortOption;
	        cout << "Do you want to sort the data by category? (y/n): ";
	        cin >> sortOption;
	
	        int sortBy = (sortOption == 'y' || sortOption == 'Y') ? 2 : 1;
	
	        // Perform sorting using merge sort
	        mergeSort(claims, 0, count - 1, sortBy);
	
	        // Display sorted claims
	        if (sortBy == 2) 
			{
	            cout << "Sorted claims by category for ID " << userID << ":\n" << endl;
	        } 
			else 
			{
	            cout << "Original claims data sorted by ID for ID " << userID << ":\n" << endl;
	        }
	        displayClaims(claims, count);
			
			
    		// Ask user for category to search
			ifstream file("claim_request.txt");
    if (!file) {
        cout << "Failed to open file claim_request.txt." << endl;
        
    }

    // Read data from file into claims array
    while (getline(file, line) && count < MAX_CLAIMS) {
        stringstream ss(line);
        getline(ss, claims[count].rid, '|');
        getline(ss, claims[count].id, '|');
        getline(ss, claims[count].type, '|');
        getline(ss, claims[count].status, '|');
        getline(ss, claims[count].date, '|');
        getline(ss, claims[count].from, '|');
        getline(ss, claims[count].to, '|');
        getline(ss, claims[count].start, '|');
        getline(ss, claims[count].end, '|');
        getline(ss, claims[count].total_distance, '|');
        getline(ss, claims[count].total_claim, '|');

        // Increment count only if the claim belongs to userID
        if (claims[count].id == userID) {
            count++;
        }
    }
    file.close();  // Close the file after reading

    // Prompt user for category to search
    string categoryToSearch;
    cout << "Enter the category to search (using RID): ";
    cin >> categoryToSearch;

    // Perform binary search on claims array
    int categoryIndex = binarySearch(claims, 0, count - 1, categoryToSearch);

    // Display results based on binary search
    if (categoryIndex != -1) {
        cout << "\nClaims with category " << categoryToSearch << ":\n";
        displayClaims(claims + categoryIndex, 1); // Display only one claim starting from categoryIndex
    } else {
        cout << "\nNo claims found with category " << categoryToSearch << "." << endl;
    }

    // System-specific pause and clear screen commands
    system("pause");  // Pause the console
    system("cls");    // Clear the console screen

	        
	    }
};

void index(string id)
{
	User u;
	char choice[2];
	claiming cl;
	check ck;
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
	    cl.processClaim(id);
	}
	else if (choice[0] == 'S' || choice[0] == 'e')
	{
		ck.processCheck(id);	    	
	}
}
}

void ex()
{
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
