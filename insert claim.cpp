#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// 结构体用于存储每个索赔项目的详细信息
struct ClaimDetail {
    string categoryID;
    string w;
    string x;
    string y;
    string z;
};

// 结构体用于存储用户输入的额外数据
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

    // 打开 claim.txt 文件
    ifstream inFile("claim.txt");

    if (!inFile) {
        cerr << "无法打开文件 claim.txt" << endl;
        return 1;
    }

    // 读取文件内容并逐行显示索赔项目选项
    cout << "以下是可用选项：" << endl;
    while (getline(inFile, line)) {
        istringstream iss(line);

        string categoryID;
        string claim_name;

        getline(iss, categoryID, '|');  // 读取 categoryID
        getline(iss, claim_name, '|');  // 读取 claim_name

        // 输出索赔项目选项
        cout << categoryID << ". " << claim_name << endl;
    }

    // 关闭 claim.txt 文件
    inFile.close();

    // 获取客户选择的索赔项目
    cout << "请选择索赔项目的编号：";
    getline(cin, categoryID_input);  // 使用 getline 获取整行输入

    // 查找 category name
    string selectedCategoryName;
    ifstream categoryFile("claim.txt");
    if (!categoryFile) {
        cerr << "无法打开文件 claim.txt" << endl;
        return 1;
    }

    while (getline(categoryFile, line)) {
        istringstream iss(line);

        string categoryID;
        string claim_name;

        getline(iss, categoryID, '|');  // 读取 categoryID
        getline(iss, claim_name, '|');  // 读取 claim_name

        if (categoryID == categoryID_input) {
            selectedCategoryName = claim_name;
            break;
        }
    }

    // 关闭 claim.txt 文件
    categoryFile.close();

    // 打开 claim_detail.txt 文件并找到匹配的索赔项目详细信息
    ifstream detailFile("claim_detail.txt");

    if (!detailFile) {
        cerr << "无法打开文件 claim_detail.txt" << endl;
        return 1;
    }

    bool found = false;
    ClaimDetail selectedClaim;

    // 读取 claim_detail.txt 文件内容并找到匹配的索赔项目详细信息
    while (getline(detailFile, line)) {
        istringstream iss(line);

        string tempCategoryID;
        string from;
        string to;
        string total_distance;
        string claim_money;

        getline(iss, tempCategoryID, '|');  // 读取 categoryID
        getline(iss, from, '|');
        getline(iss, to, '|');
        getline(iss, total_distance, '|');
        getline(iss, claim_money, '|');

        if (tempCategoryID == categoryID_input) {
            // 如果找到匹配的 categoryID，则保存详细信息并标记为找到
            found = true;
            selectedClaim.categoryID = tempCategoryID;
            selectedClaim.w = from;
            selectedClaim.x = to;
            selectedClaim.y = total_distance;
            selectedClaim.z = claim_money;
            break;  // 可以提前结束循环，因为找到了匹配项
        }
    }

    // 关闭 claim_detail.txt 文件
    detailFile.close();

    // 显示客户和索赔项目信息
    cout << "\nCustomer ID: " << customerID << endl;
    cout << "选择的索赔项目: " << categoryID_input << endl;

    // 如果找到了匹配的索赔项目，则显示详细信息；否则显示未找到信息
    if (found) {
        cout << "\n索赔项目的详细信息：" << endl;
        InsertData userInsertData;

        cout << selectedClaim.w << ": ";
        getline(cin, userInsertData.w);
        cout << selectedClaim.x << ": ";
        getline(cin, userInsertData.x);
        cout << selectedClaim.y << ": ";
        getline(cin, userInsertData.y);
        cout << selectedClaim.z << ": ";
        getline(cin, userInsertData.z);

        // 输出用户输入的额外信息
        cout << "\n您输入的额外信息是：" << endl;
        cout << selectedClaim.w << ": " << userInsertData.w << endl;
        cout << selectedClaim.x << ": " << userInsertData.x << endl;
        cout << selectedClaim.y << ": " << userInsertData.y << endl;
        cout << selectedClaim.z << ": " << userInsertData.z << endl;

        // 将用户输入的数据写入 claim_request.txt 文件
        ofstream outFile("claim_request.txt", ios::app);
        if (!outFile) {
            cerr << "无法打开文件 claim_request.txt" << endl;
            return 1;
        }

        outFile << "\n" << customerID << "|" << selectedCategoryName << "|" << userInsertData.w << "|" << userInsertData.x << "|" << userInsertData.y << "|" << userInsertData.z << "|" << endl;

        // 关闭输出文件
        outFile.close();

        cout << "\n数据已成功保存到 claim_request.txt 文件中。" << endl;
    } else {
        cout << "未找到该索赔项目的详细信息。" << endl;
    }

    return 0;
}

