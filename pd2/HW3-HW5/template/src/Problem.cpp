#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <cmath>
#include <sstream>
#include "Problem.h"
#define red(text)    "\033[31m" text "\033[0m"
#define green(text)  "\033[32m" text "\033[0m"
#define yellow(text) "\033[33m" text "\033[0m"
#define blue(text)   "\033[34m" text "\033[0m"
#define magenta(text) "\033[35m" text "\033[0m"
#define cyan(text)   "\033[36m" text "\033[0m"
#define white(text)  "\033[37m" text "\033[0m"

Problem::Problem(std::string title, std::string input, std::string output, int magic_num) {
    problem_title = title;
    input_path = input;
    output_path = output;
    magic_number = magic_num;
}
void ProblemSystem::adding_problem(Problem problem) {
    problem_list.push_back(problem);
}
void ProblemSystem::init(std::string &PROBLEM_DATA_PATH) {
    // TODO: Loading problem data from PROBLEM_DATA_PATH
    std::ifstream file(PROBLEM_DATA_PATH);
    if( !file.is_open() ) {
        std::cerr << "Error\n";
        std::cerr << "Please check your csv file in " << PROBLEM_DATA_PATH << "\n";
        exit(1);
    }
    std::string readline;
    while( getline(file, readline) ) {
        std::string title, input_path, output_path;
        int magic_num;
        // TODO: spilt by char ',' (Hints: stringstream)
        std::stringstream ss(readline);
        getline(ss, title, ',');
        getline(ss, input_path, ',');
        getline(ss, output_path, ',');
        ss >> magic_num;
        Problem new_problem(title, input_path, output_path, magic_num);
        ProblemSystem::adding_problem(new_problem);
    }
    file.close();
}

std::vector<Problem>* ProblemSystem::list_problem() {
    return &problem_list;
}
void ProblemSystem::newproblem_set(std::string PROBLEM_DATA_PATH) {

    // write code here
    std::string title, input_path, output_path;
    int magic_num;
    std::cout << "Now, please input the input path(testcase): ";
    std::cin >> input_path;
    std::cout << "Ok! your input path is " << input_path << '\n';
    std::cout << "Plz input the output path(testcase): ";
    std::cin >> output_path;
    std::cout << "OK! your output path is " << output_path << '\n';
    std::cout << "Plz input the magic number (for this problem): ";
    std::cin >> magic_num;
    std::cout << "Final! plz input the problem name: ";
    std::cin.ignore();
    getline(std::cin, title);
    std::cout << "OK! your problem name(title) is " << title << '\n';
    Problem new_problem(title, input_path, output_path, magic_num);
    problem_list.push_back(new_problem);
    try { // update problem data
        std::ofstream info_out(PROBLEM_DATA_PATH, std::ios::app);
        if( !info_out ) {
            throw std::runtime_error("Error: File does not exist - " + PROBLEM_DATA_PATH);
        }

        info_out << "\n"+title+","+input_path+","+output_path+"," << magic_num;
        info_out.close();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }
}
void ProblemSystem::submitCode(){
    std::string title;
    std::cout << "Plz input the problem ID: ";
    std::cin >> title;
    std::string codeName;
    std::cout << "Plz input your code name: ";
    std::cin >> codeName;

    Problem* problem_ptr;
    for (auto &p: problem_list){
        if (p.getTitle() == title) { problem_ptr = &p; break; }
    }
    int index_of_cpp = codeName.rfind(".cpp");
    std::string cmd1 = "g++ ./"+codeName+" -o "+codeName.substr(0, index_of_cpp);
    int compile_result = system(cmd1.c_str());
    if (compile_result != 0){
        std::cout << "Judge result: Compile Error\n";
        return;
    }

    std::string cmd2 = "./"+codeName.substr(0, index_of_cpp)+" < "+problem_ptr->getInputPath()+" > "+"./"+codeName.substr(0, index_of_cpp)+".txt";
    system(cmd2.c_str());

    auto readLines = [](const std::string& path){
        std::ifstream f(path);
        std::string lines = "", temp;
        while (getline(f, temp)){
            lines += temp;
        }
        return lines;
    };

    auto out = readLines(codeName.substr(0, index_of_cpp)+".txt");
    auto answer = readLines(problem_ptr->getOutputPath());
    if (out != answer){
        std::cout << "Judge result: Wrong Answer\n";
        return;
    }
    std::cout << "Judge result: Accepted\n";
}
void ProblemSystem::listAllProblem(){
    for (int i = 0; i < problem_list.size(); i++){
        std::cout << "Problem " << static_cast<char>('A'+i) << ": " << problem_list[i].getTitle() << '\n';
    }
}
#define epsilon 1e-6
#define max_iter 100
template<typename Func>
double newton_raphson(double x0, Func f, double (*f_prime)(double)){
    static int iter = 0;
    if (iter >= max_iter) return x0;

    double fx0 = f(x0); 
    double fpx0 = f_prime(x0);
    double x1 = (0-fx0)/fpx0+x0;
    if (abs(x0-x1) < epsilon) return x1;
    else{
        iter++;
        return newton_raphson(x1, f, f_prime);
    }
}
void ProblemSystem::randomProblem(){
    std::mt19937 gen(time(0));
    std::uniform_real_distribution<double> dis(0.0, 0.5);
    double val = dis(gen);
    auto f = [val](double x){
        return 0.5 * (1.0 + std::erf(x))-val;
    };
    auto f_prime = [](double x){
        return std::exp(-x*x) / std::sqrt(M_PI);
    };
    int i = 0;
    while (!(f(i) > 0 && f(i-1) < 0)){
        i--;
    }
    double ans = newton_raphson(i, f, f_prime);
    std::string ans_string = std::to_string(ans);
    //std::cout << ans_string << '\n';
    int index_of_dot = ans_string.find(".");
    ans_string = ans_string[1, index_of_dot]+ans_string.substr(index_of_dot+1, ans_string.size());
    long tran_ans = std::stoi(ans_string);
    int sum = 0;
    while (tran_ans){
        int num = tran_ans%10;
        sum += num;
        tran_ans /= 10;
    }
    std::cout << "Problem chosen by system:\n" << problem_list[sum%problem_list.size()].getTitle() << '\n';
}
