#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Claim {
    string id;
    string type;
    string from;
    string to;
    string total_distance;
    string claim_money;
};

void merge(vector<Claim>& claims, int left, int mid, int right, int sortBy) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Claim> L(n1);
    vector<Claim> R(n2);

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
}

void mergeSort(vector<Claim>& claims, int left, int right, int sortBy) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(claims, left, mid, sortBy);
        mergeSort(claims, mid + 1, right, sortBy);

        merge(claims, left, mid, right, sortBy);
    }
}

void displayClaims(const vector<Claim>& claims) {
    for (size_t i = 0; i < claims.size(); ++i) {
        const Claim& claim = claims[i];
        cout << claim.id << "|" << claim.type << "|" << claim.from << "|" << claim.to
             << "|" << claim.total_distance << "|" << claim.claim_money << "|" << endl;
    }
}

int binarySearch(const vector<Claim>& claims, const string& searchCategory) {
    int left = 0;
    int right = claims.size() - 1;

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

int main() {
    ifstream infile("claim_request.txt");
    if (!infile.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    vector<Claim> claims;
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        Claim claim;
        getline(ss, claim.id, '|');
        getline(ss, claim.type, '|');
        getline(ss, claim.from, '|');
        getline(ss, claim.to, '|');
        getline(ss, claim.total_distance, '|');
        getline(ss, claim.claim_money, '|');
        
        // Only add entries with id "00001"
        if (claim.id == "00001") {
            claims.push_back(claim);
        }
    }
    infile.close();

    if (claims.empty()) {
        cout << "No claims found with ID 00001." << endl;
        return 0;
    }

    char sortOption;
    cout << "Do you want to sort the data by category? (y/n): ";
    cin >> sortOption;

    int sortBy = 1; // Default: sort by ID
    if (sortOption == 'y' || sortOption == 'Y') {
        sortBy = 2; // Sort by category
    }

    mergeSort(claims, 0, claims.size() - 1, sortBy);

    if (sortBy == 2) {
        cout << "Sorted claims by category for ID 00001:\n" << endl;
    } else {
        cout << "Original claims data sorted by ID for ID 00001:\n" << endl;
    }
    
    displayClaims(claims);

    // Ask user for category to search
    cout << "\nType of Claim" << endl;
    cout << "1. Toll claim" << endl;
    cout << "2. Petrol claim" << endl;
    int choice;
    cout << "Enter the category you want to search for: " ;
    cin >> choice;

    string searchCategory;
    if (choice == 1) {
        searchCategory = "toll claim";
    } else if (choice == 2) {
        searchCategory = "petrol claim";
    } else {
        cout << "Invalid choice. Exiting program." << endl;
        return 0;
    }

    // Perform binary search on sorted claims
    int foundIndex = binarySearch(claims, searchCategory);

    if (foundIndex != -1) {
        cout << "\nFound matching claim:" << endl;
        const Claim& foundClaim = claims[foundIndex];
        cout << foundClaim.id << "|" << foundClaim.type << "|" << foundClaim.from << "|" << foundClaim.to
             << "|" << foundClaim.total_distance << "|" << foundClaim.claim_money << "|" << endl;
    } else {
        cout << "No matching claim found for category '" << searchCategory << "'." << endl;
    }

    return 0;
}

