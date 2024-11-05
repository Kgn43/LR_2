#ifndef LAB_1_H
#define LAB_1_H

#include "generalFuncs.h"
#include "arr_funcs.h"
#include "list_funcs.h"
#include "stack_funcs.h"
#include "queue_funcs.h"
#include "hashMap_funcs.h"
#include "set_funcs.h"

#include <fstream>
#include <iostream>


string delFirstLetter(const string &input);

void printOneVar(const fileData &var);
void ultimatePrint(const request& request);
structures getType(const string& fName);

structures structRequest(const string& input);
commands commandRequest(const string& input);
request getRequest(int argc, char *argv[]);

#endif // LAB_1_H
