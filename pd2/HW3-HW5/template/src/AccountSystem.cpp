#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include "AccountSystem.h"
#define red(text)    "\033[31m" text "\033[0m"
#define green(text)  "\033[32m" text "\033[0m"
#define yellow(text) "\033[33m" text "\033[0m"
#define blue(text)   "\033[34m" text "\033[0m"
#define magenta(text) "\033[35m" text "\033[0m"
#define cyan(text)   "\033[36m" text "\033[0m"
#define white(text)  "\033[37m" text "\033[0m"

User* AccountSystem::search(std::string name) {
    for(size_t i=0;i<user_list.size();i++) {
    	if (user_list[i].getUsername() == name) return &(user_list[i]);
    	else return NULL;
    }
    return nullptr;
}
void AccountSystem::init(std::string USER_DATA_PATH) {

    AccountSystem::USER_DATA_PATH = USER_DATA_PATH;

    try {

        std::ifstream file(USER_DATA_PATH); // 開啟檔案
        if( !file ) {
            throw std::runtime_error("Error: File does not exist - " + USER_DATA_PATH);
        }

        // TODO: Loading user data from USER_DATA_PATH and call adding_user (from AccountSystem) function to insert data
        // Hints: stringstream

        std::string read_line;
        while( getline(file, read_line) ) {
            std::string username, password;
            int index_found = read_line.find(",");
           	username = read_line.substr(0, index_found);
           	password = read_line.substr(index_found + 1);
            AccountSystem::adding_user(username, password);
        }
        file.close();
		AccountSystem::userdataUpdate();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }
}

void AccountSystem::sign_up() {
	std::cout << "Welcome! Please Enter Your Name: ";
	std::string input;
	std::getline(std::cin, input);
	std::string input1, input2;
	do{
		std::cout << "Please Enter Your Password: ";
		std::getline(std::cin, input1);
		std::cout << "Please Enter Your Password: ";
		std::getline(std::cin, input2);
		if (input1 == input2) break;
		else std::cout << "Two passwords are not the same. Plz try again.\n";
	} while (true);
	adding_user(input/*username*/, input1/*password*/);
	userdataUpdate();
}

std::pair<bool, std::string> AccountSystem::login() {
	std::string input;
	User *user_found;
	std::cout << "User Name(Enter -1 to sign up): ";
	do{
		std::getline(std::cin, input);
		if (input == "-1"){
			sign_up(); return std::pair<bool, std::string>(false, "");
		}
		user_found = search(input);
		if (user_found == NULL) std::cout << "USER DOES NOT EXIST. PLEASE ENTER AGAIN: ";
		else break;
	}while (true);

	std::cout << "Please Enter your password: ";
	short count = 0;
	do{
		std::getline(std::cin, input);
		if (input != user_found->getPassword()){
			std::cout << "PASSWORD WRONG. PLEASE ENTER AGAIN: ";
			count++;
			if (count > 3){
				std::cout << "Too many stupid attempts...\n";
				return login();
			}
		}else break;
	}while (true);
	std::cout << "LOGIN SUCCESSFULLY!!!\n";
	return std::pair<bool, std::string>(true, user_found->getUsername());
}
void AccountSystem::adding_user(std::string username, std::string password) {
    User new_user(username, password);
    user_list.push_back(new_user);
    return;
}

std::string AccountSystem::getuserLogin() {
	return AccountSystem::login_user;
}
void AccountSystem::userdataUpdate() {
    
    try {
        std::ofstream info_out(AccountSystem::USER_DATA_PATH);
        if( !info_out ) {
            throw std::runtime_error("Error: File does not exist - " + USER_DATA_PATH);
        }

        std::ofstream out(USER_DATA_PATH);
        for (User u: user_list){
        	out << u.getUsername() << '\t' << u.getPassword() << std::endl;
        }
        // 把整個 vector 跑過一次，透過 info_out 寫入
        // Hints: 你可能會需要 class User 的 getter 才能取得某些資訊

        info_out.close();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }
}
