#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// �ṹ�����ڴ洢ÿ��������Ŀ����ϸ��Ϣ
struct ClaimDetail {
    string categoryID;
    string w;
    string x;
    string y;
    string z;
};

// �ṹ�����ڴ洢�û�����Ķ�������
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

    // �� claim.txt �ļ�
    ifstream inFile("claim.txt");

    if (!inFile) {
        cerr << "�޷����ļ� claim.txt" << endl;
        return 1;
    }

    // ��ȡ�ļ����ݲ�������ʾ������Ŀѡ��
    cout << "�����ǿ���ѡ�" << endl;
    while (getline(inFile, line)) {
        istringstream iss(line);

        string categoryID;
        string claim_name;

        getline(iss, categoryID, '|');  // ��ȡ categoryID
        getline(iss, claim_name, '|');  // ��ȡ claim_name

        // ���������Ŀѡ��
        cout << categoryID << ". " << claim_name << endl;
    }

    // �ر� claim.txt �ļ�
    inFile.close();

    // ��ȡ�ͻ�ѡ���������Ŀ
    cout << "��ѡ��������Ŀ�ı�ţ�";
    getline(cin, categoryID_input);  // ʹ�� getline ��ȡ��������

    // ���� category name
    string selectedCategoryName;
    ifstream categoryFile("claim.txt");
    if (!categoryFile) {
        cerr << "�޷����ļ� claim.txt" << endl;
        return 1;
    }

    while (getline(categoryFile, line)) {
        istringstream iss(line);

        string categoryID;
        string claim_name;

        getline(iss, categoryID, '|');  // ��ȡ categoryID
        getline(iss, claim_name, '|');  // ��ȡ claim_name

        if (categoryID == categoryID_input) {
            selectedCategoryName = claim_name;
            break;
        }
    }

    // �ر� claim.txt �ļ�
    categoryFile.close();

    // �� claim_detail.txt �ļ����ҵ�ƥ���������Ŀ��ϸ��Ϣ
    ifstream detailFile("claim_detail.txt");

    if (!detailFile) {
        cerr << "�޷����ļ� claim_detail.txt" << endl;
        return 1;
    }

    bool found = false;
    ClaimDetail selectedClaim;

    // ��ȡ claim_detail.txt �ļ����ݲ��ҵ�ƥ���������Ŀ��ϸ��Ϣ
    while (getline(detailFile, line)) {
        istringstream iss(line);

        string tempCategoryID;
        string from;
        string to;
        string total_distance;
        string claim_money;

        getline(iss, tempCategoryID, '|');  // ��ȡ categoryID
        getline(iss, from, '|');
        getline(iss, to, '|');
        getline(iss, total_distance, '|');
        getline(iss, claim_money, '|');

        if (tempCategoryID == categoryID_input) {
            // ����ҵ�ƥ��� categoryID���򱣴���ϸ��Ϣ�����Ϊ�ҵ�
            found = true;
            selectedClaim.categoryID = tempCategoryID;
            selectedClaim.w = from;
            selectedClaim.x = to;
            selectedClaim.y = total_distance;
            selectedClaim.z = claim_money;
            break;  // ������ǰ����ѭ������Ϊ�ҵ���ƥ����
        }
    }

    // �ر� claim_detail.txt �ļ�
    detailFile.close();

    // ��ʾ�ͻ���������Ŀ��Ϣ
    cout << "\nCustomer ID: " << customerID << endl;
    cout << "ѡ���������Ŀ: " << categoryID_input << endl;

    // ����ҵ���ƥ���������Ŀ������ʾ��ϸ��Ϣ��������ʾδ�ҵ���Ϣ
    if (found) {
        cout << "\n������Ŀ����ϸ��Ϣ��" << endl;
        InsertData userInsertData;

        cout << selectedClaim.w << ": ";
        getline(cin, userInsertData.w);
        cout << selectedClaim.x << ": ";
        getline(cin, userInsertData.x);
        cout << selectedClaim.y << ": ";
        getline(cin, userInsertData.y);
        cout << selectedClaim.z << ": ";
        getline(cin, userInsertData.z);

        // ����û�����Ķ�����Ϣ
        cout << "\n������Ķ�����Ϣ�ǣ�" << endl;
        cout << selectedClaim.w << ": " << userInsertData.w << endl;
        cout << selectedClaim.x << ": " << userInsertData.x << endl;
        cout << selectedClaim.y << ": " << userInsertData.y << endl;
        cout << selectedClaim.z << ": " << userInsertData.z << endl;

        // ���û����������д�� claim_request.txt �ļ�
        ofstream outFile("claim_request.txt", ios::app);
        if (!outFile) {
            cerr << "�޷����ļ� claim_request.txt" << endl;
            return 1;
        }

        outFile << "\n" << customerID << "|" << selectedCategoryName << "|" << userInsertData.w << "|" << userInsertData.x << "|" << userInsertData.y << "|" << userInsertData.z << "|" << endl;

        // �ر�����ļ�
        outFile.close();

        cout << "\n�����ѳɹ����浽 claim_request.txt �ļ��С�" << endl;
    } else {
        cout << "δ�ҵ���������Ŀ����ϸ��Ϣ��" << endl;
    }

    return 0;
}

