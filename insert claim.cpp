#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Struct to store detailed information of each claim item
struct ClaimDetail {
    string categoryID;
    string w;
    string x;
    string y;
    string z;
};

// Struct to store additional user input data
struct InsertData {
    string w;
    string x;
    string y;
    string z;
};

int main() {
    const string customerID = "00001";
    string line;
    string categoryID_input;

    // Open the claim.txt file
    ifstream inFile("claim.txt");

    if (!inFile) {
        cerr << "Unable to open file claim.txt" << endl;
        return 1;
    }

    // Read file content and display claim item options line by line
    cout << "Available options:" << endl;
    while (getline(inFile, line)) {
        istringstream iss(line);

        string categoryID;
        string claim_name;

        getline(iss, categoryID, '|');  // Read categoryID
        getline(iss, claim_name, '|');  // Read claim_name

        // Output claim item options
        cout << categoryID << ". " << claim_name << endl;
    }

    // Close claim.txt file
    inFile.close();

    // Get customer's selected claim item
    cout << "Please select the claim item number: ";
    getline(cin, categoryID_input);  // Use getline to get the entire line input

    // Find the category name
    string selectedCategoryName;
    ifstream categoryFile("claim.txt");
    if (!categoryFile) {
        cerr << "Unable to open file claim.txt" << endl;
        return 1;
    }

    while (getline(categoryFile, line)) {
        istringstream iss(line);

        string categoryID;
        string claim_name;

        getline(iss, categoryID, '|');  // Read categoryID
        getline(iss, claim_name, '|');  // Read claim_name

        if (categoryID == categoryID_input) {
            selectedCategoryName = claim_name;
            break;
        }
    }

    // Close claim.txt file
    categoryFile.close();

    // Open claim_detail.txt file and find the matching claim item details
    ifstream detailFile("claim_detail.txt");

    if (!detailFile) {
        cerr << "Unable to open file claim_detail.txt" << endl;
        return 1;
    }

    bool found = false;
    ClaimDetail selectedClaim;

    // Read claim_detail.txt file content and find the matching claim item details
    while (getline(detailFile, line)) {
        istringstream iss(line);

        string tempCategoryID;
        string from;
        string to;
        string total_distance;
        string claim_money;

        getline(iss, tempCategoryID, '|');  // Read categoryID
        getline(iss, from, '|');
        getline(iss, to, '|');
        getline(iss, total_distance, '|');
        getline(iss, claim_money, '|');

        if (tempCategoryID == categoryID_input) {
            // If a matching categoryID is found, save the details and mark as found
            found = true;
            selectedClaim.categoryID = tempCategoryID;
            selectedClaim.w = from;
            selectedClaim.x = to;
            selectedClaim.y = total_distance;
            selectedClaim.z = claim_money;
            break;  // Can exit the loop early since a match was found
        }
    }

    // Close claim_detail.txt file
    detailFile.close();

    // Display customer and claim item information
    cout << "\nCustomer ID: " << customerID << endl;
    cout << "Selected claim item: " << categoryID_input << endl;

    // If a matching claim item is found, display the details; otherwise, show not found message
    if (found) {
        cout << "\nDetails of the claim item:" << endl;
        InsertData userInsertData;

        cout << selectedClaim.w << ": ";
        getline(cin, userInsertData.w);
        cout << selectedClaim.x << ": ";
        getline(cin, userInsertData.x);
        cout << selectedClaim.y << ": ";
        getline(cin, userInsertData.y);
        cout << selectedClaim.z << ": ";
        getline(cin, userInsertData.z);

        // Output the additional information entered by the user
        cout << "\nThe additional information you entered is:" << endl;
        cout << selectedClaim.w << ": " << userInsertData.w << endl;
        cout << selectedClaim.x << ": " << userInsertData.x << endl;
        cout << selectedClaim.y << ": " << userInsertData.y << endl;
        cout << selectedClaim.z << ": " << userInsertData.z << endl;

        // Write the user input data to claim_request.txt file
        ofstream outFile("claim_request.txt", ios::app);
        if (!outFile) {
            cerr << "Unable to open file claim_request.txt" << endl;
            return 1;
        }

        outFile << "\n" << customerID << "|" << selectedCategoryName << "|" << userInsertData.w << "|" << userInsertData.x << "|" << userInsertData.y << "|" << userInsertData.z << "|";

        // Close the output file
        outFile.close();

        cout << "\nData has been successfully saved to claim_request.txt file." << endl;
    } else {
        cout << "No details found for the selected claim item." << endl;
    }

    return 0;
}

