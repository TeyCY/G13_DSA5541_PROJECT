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
    string v;
    string w;
    string x;
    string y;
    string z;
};

// Struct to store additional user input data
struct InsertData {
    string v;
	string w;
    string x;
    string y;
    string z;
};

struct Claim {
	string name;
	string categoryID;
    string id;
    string type;
    string from;
    string to;
    string total_distance;
    string claim_money;
    string date;
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

struct claims
{
	string claimID,userID,start_time,end_time,total,departure,destination,expenses,date,address,days,paper,subject,status;
	
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

void readDetailedClaims(Claim*& claims, int& size) 
{
    ifstream detailFile("claim_detail.txt");
    if (!detailFile) {
        cerr << "Unable to open file claim_detail.txt" << endl;
        return;
    }

    string line;
    int index = 0;
    while (getline(detailFile, line)) {
        stringstream ss(line);
        Claim claim;
        getline(ss, claim.id, '|');
        getline(ss, claim.date, '|');
        getline(ss, claim.from, '|');
        getline(ss, claim.to, '|');
        getline(ss, claim.total_distance, '|');
        getline(ss, claim.claim_money, '|');
        
        claims[index++] = claim;
        size++;
    }

    detailFile.close();
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
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(claims, left, mid, sortBy);
        mergeSort(claims, mid + 1, right, sortBy);

        merge(claims, left, mid, right, sortBy);
    }
}

void displayClaims(const Claim* claims, int size) 
{
    for (int i = 0; i < size; ++i) {
        const Claim& claim = claims[i];
        cout << claim.id << "|" << claim.type << "|" << claim.from << "|" << claim.to
             << "|" << claim.total_distance << "|" << claim.claim_money << "|" << endl;
    }
}


int binarySearch(const Claim* claims, int size, const string& searchCategory) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (claims[mid].type == searchCategory) {
            return mid; // Found the category
        } else if (claims[mid].type < searchCategory) {
            left = mid + 1; // Search in the right half
        } else {
            right = mid - 1; // Search in the left half
        }
    }

    return -1; // Category not found
}

class User 
{
	private:
	    string userID, name, ic, gender, contactNumber, email, caddress, paddress, state, city, poscode, username, password;
	    char choice;
	    int uID=1;
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

            if (u_profile.is_open()) {
                string line;
                while (getline(u_profile, line)) {
                    uID++;
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
            while (!isValidIC(ic)) {
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
                user_profile << setw(5) << setfill('0') << uID << "|" << name << "|" << ic << "|" << gender << "|" << contactNumber << "|" << email << "|" << caddress << "|" << paddress << "|" << state << "|" << city << "|" << poscode << "|" << endl;
                user_profile.close();
            }
            // Assuming index() function is defined elsewhere
            // index(userID);
        }

        void promtprofile(string id) {
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

                if (userID == id) {
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

            cout << "User ID: " << setw(5) << setfill('0') << uID << endl;

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
                user_login << setw(5) << setfill('0') << uID;
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
	        while (getline(inputFile, line)) {
	            istringstream iss(line);
	            getline(iss, userID, '|');
	            if (userID == ID) {
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

class claiming : public User {
public:
    string categoryID_input;

    void processClaim(string userID) {
        ifstream inFiles("claim.txt");
        if (!inFiles) {
            cerr << "Unable to open file claim.txt" << endl;
            return;
        }

        string line;
        while (getline(inFiles, line)) {
            istringstream iss(line);
            string categoryID, claim_name;

            getline(iss, categoryID, '|');
            getline(iss, claim_name, '|');

            cout << "[" << categoryID << "] " << claim_name << endl;
        }

        inFiles.close();

        cout << "Enter Your Choice: ";
        getline(cin >> ws, categoryID_input);

        // Find the category name
        string selectedCategoryName;
        ifstream categoryFile("claim.txt");
        if (!categoryFile) {
            cerr << "Unable to open file claim.txt" << endl;
            return;
        }

        while (getline(categoryFile, line)) {
            istringstream iss(line);
            string categoryID, claim_name;

            getline(iss, categoryID, '|');
            getline(iss, claim_name, '|');

            if (categoryID == categoryID_input) {
                selectedCategoryName = claim_name;
                break;
            }
        }

        categoryFile.close();

        // Open claim_detail.txt file and find the matching claim item details
        ifstream detailFile("claim_detail.txt");
        if (!detailFile) {
            cerr << "Unable to open file claim_detail.txt" << endl;
            return;
        }

        bool found = false;
        ClaimDetail selectedClaim;

        while (getline(detailFile, line)) {
            istringstream iss(line);
            string tempCategoryID, date, from, to, total_distance, claim_money;

            getline(iss, tempCategoryID, '|');
            getline(iss, date, '|');
            getline(iss, from, '|');
            getline(iss, to, '|');
            getline(iss, total_distance, '|');
            getline(iss, claim_money, '|');

            if (tempCategoryID == categoryID_input) {
                found = true;
                selectedClaim.categoryID = tempCategoryID;
                selectedClaim.v = date;
                selectedClaim.w = from;
                selectedClaim.x = to;
                selectedClaim.y = total_distance;
                selectedClaim.z = claim_money;
                break;
            }
        }

        detailFile.close();

        if (found) {
            system("cls");
            InsertData userInsertData;

            cout << selectedClaim.v << ": ";
            getline(cin >> ws, userInsertData.v);
            cout << selectedClaim.w << ": ";
            getline(cin, userInsertData.w);
            cout << selectedClaim.x << ": ";
            getline(cin, userInsertData.x);
            cout << selectedClaim.y << ": ";
            getline(cin, userInsertData.y);
            cout << selectedClaim.z << ": ";
            getline(cin, userInsertData.z);

            cout << "\nInformation:" << endl;
            cout << selectedClaim.v << ": " << userInsertData.v << endl;
            cout << selectedClaim.w << ": " << userInsertData.w << endl;
            cout << selectedClaim.x << ": " << userInsertData.x << endl;
            cout << selectedClaim.y << ": " << userInsertData.y << endl;
            cout << selectedClaim.z << ": " << userInsertData.z << endl;

            ofstream outFile("claim_request.txt", ios::app);
            if (!outFile) {
                cerr << "Unable to open file claim_request.txt" << endl;
                return;
            }

            outFile << "\n" << userID << "|" << selectedCategoryName << "|" << userInsertData.v << "|" << userInsertData.w << "|" << userInsertData.x << "|" << userInsertData.y << "|" << userInsertData.z << "|" << "PENDING" << "|";
            outFile.close();

            cout << "\nData has been successfully saved!!!" << endl;
        } else {
            cout << "No details found for the selected claim item." << endl;
        }
    }

    friend class check;
};

class check {
public:
    void processCheck(string userID)
	{
        // File operations
        ifstream inFile("claim.txt");
        if (!inFile) {
            cerr << "Failed to open file claim.txt." << endl;
            return;
        }

        string line;
        cout << "\t+-------Type of Claim-------+" << endl;
        cout << " " << endl;
        while (getline(inFile, line)) 
		{
            istringstream iss(line);
            Claim claim;
            getline(iss, claim.categoryID, '|');
            getline(iss, claim.name, '|');
            cout << "\t    [" << claim.categoryID << "] " << claim.name << " " << endl;
        }
        inFile.close();
        cout << " " << endl;
        cout << "\t+---------------------------+" << endl;

        // User input
        string choice;
        cout << "Enter the category you want to search for: ";
        cin >> choice;

        // Search category
        string searchCategory;
        ifstream categoryFile("claim.txt");
        if (!categoryFile) 
		{
            cerr << "Unable to open file claim.txt" << endl;
            return;
        }

        while (getline(categoryFile, line)) 
		{
            istringstream iss(line);
            string categoryID, claim_name;
            getline(iss, categoryID, '|');
            getline(iss, claim_name, '|');
            if (categoryID == choice) {
                searchCategory = claim_name;
                break;
            }
        }
        categoryFile.close();

        // Sort option
        char sortOption;
        cout << "Do you want to sort the data by category? (y/n): ";
        cin >> sortOption;

        int sortBy = (sortOption == 'y' || sortOption == 'Y') ? 2 : 1;

        // Read and process claims
        ifstream infile("claim_request.txt");
        if (!infile.is_open()) {
            cerr << "Failed to open file claim_request.txt." << endl;
            return;
        }

        Claim* claims = NULL;
        int size = 0;

        while (getline(infile, line)) {
            stringstream ss(line);
            Claim claim;
            getline(ss, claim.id, '|');
            getline(ss, claim.categoryID, '|');
            getline(ss, claim.from, '|');
            getline(ss, claim.to, '|');
            getline(ss, claim.total_distance, '|');
            getline(ss, claim.claim_money, '|');

            if (claim.id == "00001") {
                // Allocate memory for claims dynamically
                Claim* temp = new Claim[size + 1];
                for (int i = 0; i < size; ++i) {
                    temp[i] = claims[i];
                }
                delete[] claims;
                claims = temp;
                claims[size++] = claim;
            }
        }
        infile.close();

        if (size == 0) {
            cout << "No claims found with ID 00001." << endl;
            return;
        }

        mergeSort(claims, 0, size - 1, sortBy);

        if (sortBy == 2) {
            cout << "Sorted claims by category for ID 00001:\n" << endl;
        } else {
            cout << "Original claims data sorted by ID for ID 00001:\n" << endl;
        }

        displayClaims(claims, size);

        int foundIndex = binarySearch(claims, size, searchCategory);

        if (foundIndex != -1) {
            cout << "\nFound matching claim:" << endl;
            const Claim& foundClaim = claims[foundIndex];
            cout << foundClaim.id << "|" << foundClaim.categoryID << "|" << foundClaim.from << "|" << foundClaim.to
                 << "|" << foundClaim.total_distance << "|" << foundClaim.claim_money << "|" << endl;
        } else {
            cout << "No matching claim found for category '" << searchCategory << "'." << endl;
        }

        delete[] claims; // Clean up allocated memory
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
