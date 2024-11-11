#include "StackTask.h"


char oneExpr(const char &op1, const char &opert ,const char &op2) {
    if (opert == '+') {
        if (op1 == '1' || op2 == '1') return '1';
        return '0';
    }
    if (opert == '^') {
        if (op1 != op2) return '1';
        return '0';
    }
    throw std::invalid_argument("Invalid operator");
}


string solveNot(const string &expr) {
    //solve '!'
    string exprBuff;
    for (int i = 0; i < expr.size(); ++i) {
        if (expr[i] == '!') {
            if (i == expr.size() - 1) {
                throw std::invalid_argument("Invalid expression");
            }
            if (expr[i + 1] == '!') {
                ++i;
                continue;
            }
            if (expr[i+1] == '0') {
                exprBuff += '1';
                ++i;
                continue;
            }
            if (expr[i+1] == '1') {
                exprBuff += '0';
                ++i;
                continue;
            }
            throw std::invalid_argument("Invalid expression");
        }
        exprBuff += expr[i];
    }
    return exprBuff;
}


string solveMultiply(const string &expr) {
    //solve '*'
    string exprBuff;
    for (int i = 0; i < expr.size(); ++i) {
        if (expr[i] == '*') {
            if (i == expr.size() - 1) {
                throw std::invalid_argument("Invalid expression");
            }
            if (exprBuff[exprBuff.size()-1] != '0' && exprBuff[exprBuff.size()-1] != '1') {
                throw std::invalid_argument("Invalid expression");
            }
            if (expr[i + 1] == '1' && exprBuff[exprBuff.size()-1] == '1') {
                ++i;
            }
            else {
                exprBuff[exprBuff.size()-1] = '0';
                ++i;
            }
        }
        else {
            exprBuff += expr[i];
        }
    }
    return exprBuff;
}


char toSolve(string expr) {
    if (expr.size() == 1) {return expr[0];}
    for (const auto &c : expr) {
        if (!(c == '!' || c == '*' || c == '^' || c == '+' || c == '0' || c == '1')) {
            throw std::invalid_argument("Invalid expression");
        }
    }
    for (int i = 0; i < expr.size(); ++i) {
        if ((expr[i] == '1' || expr[i] == '0') && (expr[i + 1] == '1' || expr[i + 1] == '0')) {
            throw std::invalid_argument("Invalid expression");
        }
    }
    expr = solveNot(expr);
    expr = solveMultiply(expr);
    Stack<char> exprNums;
    Stack<char> exprOps;
    for (const auto& ch : expr) {
        if (ch == '1' || ch == '0') {
            exprNums.push(ch);
        }
        else if (ch == '*' || ch == '^' || ch == '+' || ch == '!') {
            exprOps.push(ch);
        }
    }
    char operand1;
    char operand2;
    while (exprOps.size > 0) {
        operand1 = exprNums.getLast();
        exprNums.pop();
        operand2 = exprNums.getLast();
        exprNums.pop();
        exprNums.push(oneExpr(operand1, exprOps.getLast(), operand2));
        exprOps.pop();
    }
    return exprNums.getLast();
}


string nestedExpressionFind(const string &expression) {
    Stack<char> scobe;
    int maxEnclosed = 0;
    int exprStartPos = 0;
    int exprStartPosTmp = 0;
    int exprEndPos = 0;
    for (size_t i = 0; i < expression.size(); i++) {
        if (expression[i] == '(' ) {
            scobe.push(expression[i] );
            exprStartPosTmp = i;
        }
        else if (expression[i] == ')') {
            if (scobe.size > maxEnclosed) {
                exprEndPos = i;
                exprStartPos = exprStartPosTmp;
                maxEnclosed = scobe.size;
            }
            scobe.pop();

        }
    }
    if (scobe.size != 0) {
        throw std::invalid_argument("Invalid expression: unbalanced brackets");
    }
    if (exprEndPos == 0) {
        exprEndPos = expression.size() - 1;
    }
    string enclosedExpr;
    for (size_t i = exprStartPos; i <= exprEndPos; i++) {
        if (expression[i] == '(' || expression[i] == ')') {continue;}
        enclosedExpr += expression[i];
    }
    string exprBuff;
    for (size_t i = 0; i < expression.size(); i++) {
        if (i < exprStartPos) exprBuff += expression[i];
        else if (i > exprEndPos) exprBuff += expression[i];
        else {
            exprBuff += toSolve(enclosedExpr);
            i += exprEndPos - exprStartPos;
        }
    }
    return exprBuff;
}


char getAnswer(string expression) {
    while (expression.size() != 1) {
        expression = nestedExpressionFind(expression);
    }
    return expression[0];
}


void stackTask() {
    string expr = "!1+1*!0";
    cout << expr << endl;
    cout << getAnswer(expr) << endl;
    expr = "!(((1*0)))*(!0^0)";
    cout << expr << endl;
    cout << getAnswer(expr) << endl;
}