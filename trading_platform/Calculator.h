#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
using namespace std;
class cal {
public:
    string calculator(string exp);
    int com(char ch1, char ch2);
    float run(char opr, float ope1, float ope2);
    bool isOpt(char ch);
    string get_num(string exp, int& idx);
    bool normalize(string& exp);  //deal with '-'
};

#endif // CALCULATOR_H
