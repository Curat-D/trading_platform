#include <stack>
#include "Calculator.h"


string cal::calculator(string exp) {
    string res;
    exp += ';';
    if (exp.find("()") != exp.npos) {
        res = "操作符误用0";
        return res;
    }
    normalize(exp);
    stack<float> ope;
    stack<char> opt;
    opt.push(';');
    for (int i = 0; i < exp.size(); i++) {
        //as an operator
        if (isOpt(exp[i])) {
            int x = com(opt.top(), exp[i]);
            while (x == 1) {
                float ope1, ope2;
                if (ope.empty()) {
                    res = "操作符误用1";
                    return res;
                }
                else {
                    ope2 = ope.top();
                    ope.pop();
                    if (ope.empty()) {
                        res = "操作符误用2";
                        return res;
                    }
                    ope1 = ope.top();
                    ope.pop();
                }
                float tmp = run(opt.top(), ope1, ope2);
                ope.push(tmp);
                opt.pop();
                x = com(opt.top(), exp[i]);
            }
            if (x == -1)
                opt.push(exp[i]);
            else if (x == 0) {
                if (exp[i] == ')') {
                    if (opt.empty()) {
                        res = "操作符误用3";
                        return res;
                    }
                    else
                        opt.pop();
                }
                else if (exp[i] == ';') {
                    if (ope.empty()) {
                        res = "操作符误用4";
                        return res;
                    }
                    else {
                        float R = ope.top();
                        ope.pop();
                        if (!ope.empty()) {
                            res = "操作符误用5";
                            return res;
                        }
                        res = to_string(R);
                        string::size_type idx_of_point;
                        idx_of_point = res.find(".");
                        if (idx_of_point == res.npos) {
                            res += ".0";
                            return res;
                        }
                        else {
                            res = res.substr(0, idx_of_point + 2);
                            return res;
                        }
                    }
                }
                else {
                    res = "操作符误用9";
                    return res;
                }
            }
        }
        else {
            if ((exp[i] < '0' || exp[i] > '9') && exp[i] != '.') {
                res = "操作符误用6";
                return res;
            }
            string OPE = get_num(exp, i);
            if (i == -1) {
                res = "操作符误用7";
                return res;
            }
            float num = atof(OPE.c_str());
            ope.push(num);
        }
    }
    res = "操作符误用8";
    return res;
}

int cal::com(char c1, char c2)
{
    int a1, a2;
    if ('+' == c1 || '-' == c1)
        a1 = 3;
    if ('*' == c1 || '/' == c1)
        a1 = 5;
    if ('(' == c1)
        a1 = 1;
    if (')' == c1)
        a1 = 6;
    if (';' == c1)
        a1 = 0;

    if ('+' == c2 || '-' == c2)
        a2 = 2;
    if ('*' == c2 || '/' == c2)
        a2 = 4;
    if ('(' == c2)
        a2 = 6;
    if (')' == c2)
        a2 = 1;
    if (';' == c2)
        a2 = 0;
    if (a1 > a2)
        return 1;
    else if (a1 == a2)
        return 0;
    else
        return -1;
}

float cal::run(char opt, float ope1, float ope2) {
    switch (opt)
    {
    case '+':
        return ope1 + ope2;
        break;
    case '-':
        return ope1 - ope2;
        break;
    case'*':
        return ope1 * ope2;
        break;
    case '/':
        return ope1 / ope2;
        break;
    default:
        return 0.0;
        break;
    }
}

bool cal::isOpt(char ch) {
    if (ch == '+'
        || ch == '-'
        || ch == '*'
        || ch == '/'
        || ch == '('
        || ch == ')'
        || ch == ';')
        return true;
    else
        return false;
}

string cal::get_num(string exp, int& idx) {
    int tmp = idx;
    while (idx < exp.size() && !isOpt(exp[idx])) {
        if ((exp[idx] >= '0' && exp[idx] <= '9') || exp[idx] == '.')
            idx++;
        else {
            idx = -1;
            return 0;
        }
    }
    string res = exp.substr(tmp, idx - tmp);
    idx--;
    return res;
}

bool cal::normalize(string& exp) {
    for (int i = 0; i < exp.size(); i++) {
        if (exp[i] == '-') {
            if (i == 0 || exp[i - 1] == '(')
                exp = exp.insert(i,1,'0');
        }
    }
    return 0;
}
