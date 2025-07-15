#include "UserInfo.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <climits>
#include <algorithm>

UserInfo::UserInfo(std::string name, int id){
    this->name = name;
    this->id = id;
}

bool UserManager::addUser(const UserInfo& user, const std::string& parent, const std::string& type) {
    // 根據家族選擇對應的新增函式
    if (type == "rongguo"){
        return RongGuoMansion::addUser(user, parent);
    } else if (type == "ningguo"){
        return NingGuoMansion::addUser(user, parent);
    }
    return false;
}

bool RongGuoMansion::addUser(const UserInfo& user, const std::string& parent) {
    // 第一筆資料，必須以 root 為父母才能加入
    if (users.size() == 0){
        if (parent == "root"){
            users.push_back(std::pair<UserInfo, UserInfo>(user, UserInfo(parent, -1)));
            return true;
        }
    } else {
        // 後續資料，檢查 parent 是否已存在
        for (auto bond: users){
            if (bond.first.getName() == parent || bond.second.getName() == parent){
                users.push_back(std::pair<UserInfo, UserInfo>(user, UserInfo(parent, -1)));
                return true;
            }
        }
    }
    // 找不到 parent
    return false;
}

bool NingGuoMansion::addUser(const UserInfo& user, const std::string& parent) {
    // 第一筆資料，必須以 root 為父母才能加入
    if (users.size() == 0){
        if (parent == "root"){
            users.push_back(std::pair<UserInfo, UserInfo>(user, UserInfo(parent, -1)));
            return true;
        }
    } else {
        // 後續資料，檢查 parent 是否已存在
        for (auto bond: users){
            if (bond.first.getName() == parent || bond.second.getName() == parent){
                users.push_back(std::pair<UserInfo, UserInfo>(user, UserInfo(parent, -1)));
                return true;
            }
        }
    }
    // 找不到 parent
    return false;
}

bool Mansion::addUser(const UserInfo& user, const std::string& parent){
    return true;
}
int RongGuoMansion::printMagicNumber(int target) {
    static int sum = 0, i = 0, closest = INT_MIN; // sum: 當前組合總和, i: 索引, closest: 最接近 target 的總和
    if (i >= users.size()) { // 遍歷完所有人
        int diff1 = abs(closest - target), diff2 = abs(sum - target); // 計算當前與最佳的誤差
        if (diff2 < diff1) closest = sum; // 更接近則更新
        if (diff1 == diff2 && sum > closest) closest = sum; // 同樣接近則取較大者
        return closest; // 回傳最終結果
    }
    int id = users[i].first.getId(); // 取當前使用者 id
    i++;
    sum += id; // 選擇當前使用者
    RongGuoMansion::printMagicNumber(target);
    sum -= id; // 不選擇當前使用者
    RongGuoMansion::printMagicNumber(target);
    i--;
    return closest; // 返回最接近的和
}
int RongGuoMansion::printMagicNumber() {
    static int sum = 0, i = 0, closest = INT_MIN, target = 2025;
    if (i >= users.size()){
        //std::cout << sum << std::endl;
        int diff1 = abs(closest-target), diff2 = abs(sum-target);
        if (diff2 < diff1) closest = sum;
        if (diff1 == diff2 && sum > closest) closest = sum;
        return closest;
    }
    int id = users[i].first.getId();
    i++;
    sum += id;
    RongGuoMansion::printMagicNumber();
    sum -= id;
    RongGuoMansion::printMagicNumber();
    i--;
    return closest;
}
int NingGuoMansion::printMagicNumber(int target) {
    int cnt = 0; // 紀錄 id <= target 的人數
    for (auto bond : users) {
        if (bond.first.getId() <= target) 
            cnt++; // 符合條件則計數
    }
    return cnt; // 回傳人數
}
int NingGuoMansion::printMagicNumber() {
    int cnt = 0;
    for (auto bond: users){
        if (bond.second.getName() == "root") cnt++;
    }
    return cnt;
}
std::string NingGuoMansion::printLCA(std::string name1, std::string name2) {
    // 若兩人相同則直接回傳
    if (name1 == name2) return name1;

    // 初始化兩個 set，分別紀錄兩個人的祖先鏈
    std::unordered_set<std::string> table1 = {name1}, table2 = {name2};
    while (true) {
        bool check1 = false, check2 = false;
        for (auto bond : users) {
            // 處理第一個人的上升
            if (!check1 && bond.first.getName() == name1) {
                check1 = true;
                std::string parent1 = bond.second.getName();
                // 若發現為第二人的祖先，則為 LCA
                if (table2.count(parent1)) return parent1;
                table1.insert(parent1);
                name1 = std::move(parent1);
            }
            // 處理第二個人的上升
            if (!check2 && bond.first.getName() == name2) {
                check2 = true;
                std::string parent2 = bond.second.getName();
                // 若發現為第一人的祖先，則為 LCA
                if (table1.count(parent2)) return parent2;
                table2.insert(parent2);
                name2 = std::move(parent2);
            }
            // 兩人皆已處理則跳出內層 for，繼續 while
            if (check1 && check2) {
                break;
            }
        }
    }
}

int Mansion::printMagicNumber(int target){
    return 1;
}
int Mansion::printMagicNumber(){
    return 1;
}