#include <iostream>
#include "MainPage.h"
#define red(text)    "\033[31m" text "\033[0m"
#define green(text)  "\033[32m" text "\033[0m"
#define yellow(text) "\033[33m" text "\033[0m"
#define blue(text)   "\033[34m" text "\033[0m"
#define magenta(text) "\033[35m" text "\033[0m"
#define cyan(text)   "\033[36m" text "\033[0m"
#define white(text)  "\033[37m" text "\033[0m"

void MainPage::mainpagePrint() {
    std::cout << "+";
    for (int i = 0; i < 45; ++i) {
        std::cout << "-";
    }
    std::cout << "+\n";
    std::cout << yellow("Please choose an operation:") << "\n";
    std::cout << "+";
    for (int i = 0; i < 45; ++i) {
        std::cout << "-";
    }
    std::cout << "+\n";

    std::cout << green("(1) Who am I") << "\n";
    std::cout << green("(2) Query judge version") << "\n";
    std::cout << green("(3) List all problem") << "\n";
    std::cout << green("(4) Random some problem") << "\n";
    std::cout << green("(5) Submit code") << "\n";
    std::cout << red("(6) Add a new problem (admin only)") << "\n";
    std::cout << yellow("(7) Exit the process") << "\n";
    
    std::cout << "+";
    for (int i = 0; i < 45; ++i) {
        std::cout << "-";
    }
    std::cout << "+\n";

    return;
}
int MainPage::operationCheck() {
    std::string input;
    int judge;
    do{
        std::getline(std::cin, input);
        if (input.size() > 1){std::cout << "Invalid Input. Plz enter again\n"; continue;}
        judge = static_cast<int>(input[0]) - 48;
        if ( 1 <= judge && judge <= 7 ) return judge;
        else std::cout << -1 << std::endl;
    }while (true);
    return 0;
}