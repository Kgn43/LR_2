#include "hashMap_funcs.h"

#include <iostream>
#include "arr.h"
#include <sstream>
using std::string;


struct request{
    arr<string> query;
    string file;
    bool isCallHelp = false; //проиграли бит, но выиграли больше на обработке запроса
};


request getRequest(int argc, char *argv[] ){
    request output;
    for (int i = 0; i < argc; ++i){
        if (static_cast<string>(argv[i]) == "--help") {
            output.isCallHelp = true;
            return output;
        }
        if (static_cast<string>(argv[i]) == "--file") {
            //если после флага ничего нет || если после флага другой флаг
            if (i + 1 == argc || argv[i + 1][0] == '-') { //Если первое условие выполняется - второе не приведёт к ошибке т.к. не будет проверяться
                throw runtime_error(("Error: empty query.\n Specify what to execute"));
            } else {
                output.file = argv[i + 1];
                continue;
            }
        }
        if (static_cast<string>(argv[i]) == "--query") {
            if (i + 1 == argc || argv[i + 1][0] == '-') { //если после флага ничего нет || если после флага другой флаг
                throw runtime_error(("Error: empty query.\n Specify what to execute"));
            } else {
                output.query = splitToArr(static_cast<string>(argv[i + 1]));
            }
        }
    }
    return output;
}


bool isFileExist(const std::string& fileName){
    std::ifstream file(fileName);
    if(!file.is_open()) return false;
    file.close();
    return true;
}


int secondTask(int argc, char *argv[]) {
    try {
        request request = getRequest(argc, argv);
        if (argc == 1){
            cout << "0 arguments were entered." << endl << "add --help for more information" << endl;
            return 1;
        }
        if (request.query.size == 0){
            cout << "An empty query was given: add --help" << endl;
            return 1;
        }
        if (request.query[0] == "print"){
            if (!isFileExist(request.file) || request.file.empty()){ //проверяем доступ указанного файла/указан ли файл
                throw runtime_error(("Error: wrong file name or file doesn't exist"));
            }
            consolePrint(request);
        } else {
            structures strucType = structRequest(request.query[0][0]); //определяем по букве структуру
            if (!isFileExist(request.file) || request.file.empty()){ //проверяем доступ указанного файла/указан ли файл
                throw runtime_error(("Error: wrong file name or file doesn't exist"));
            }
            request.query[0] = delFirstLetter(request.query[0]); //убираем букву для упрощения чтения команды
            switch (strucType) {
                case Array:
                    switch (commandRequest(request.query[0])) {
                        case push:
                            arrPush(request);
                            break;
                        case del:
                            arrDel(request);
                            break;
                        case Get:
                            arrGet(request);
                            break;
                        default:
                            cout << "There is no such Array processing command" << endl;
                    }
                    break;

            }
        }
    }
    catch (exception &ex) {
        cout << ex.what() << endl;
        return -1;
    }
}


void printHashMap(const request &request) {
    ifstream file(request.file, ios::in); //откуда читаем
    string variableLine; //считываемая строка с файла
    if (request.query.size == 1){ //вывести все переменные
        fileData var;
        while (getline(file, variableLine)) { //проверяем все существующие переменные
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
            var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
            //определяем реальную переменную этого Типа данных
            hashMap currVar = hMFromStr(var.data);
            cout << var.name << " = " << currVar << endl;
        }
    }
    else if (request.query.size == 2) { //вывести одну переменную
        string name = request.query[1]; //имя искомой переменной
        fileData var;
        bool varIsExist = false;
        while (getline(file, variableLine)){ //проверяем все существующие переменные
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
            var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
            if (var.name == name){ //если такая переменная существует
                varIsExist = true; //закрываем защёлку
                hashMap currVar = hMFromStr(var.data); //определяем реальную переменную этого Типа данных
                cout << var.name << " = " << currVar << endl;
            }
        }
        if (!varIsExist){
            cout << "Wrong variable name" << endl;
        }
    }
    else {
        cout << "Wrong syntax" << endl;
    }
    file.close();
}


void hashSetInsert(const request& request){
//структура команды: insert имяТаблицы ключ значение
    fstream file(request.file, ios::in);
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    if (request.query.size != 4) throw runtime_error("Wrong command syntax");
    string name = request.query[1];
    string key = request.query[2]; //ключ
    string value = request.query[3]; //значение
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
        var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
        if (var.name == name){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            hashMap currVar = hMFromStr(var.data); //определяем реальную переменную этого Типа данных
            currVar.insert(key, value); //закидываем то, что просят
            variableLine = var.name + ';' + strFromHM(currVar);//превращаем переменную в текст
            tmpFile << variableLine << endl;
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    if (!varIsExist){
        cout << "making new HashMap" << endl;
        hashMap newVar;//да, делаем это всегда.
        newVar.insert(key, value);
        variableLine = name + ';' + strFromHM(newVar);//превращаем переменную в текст
        tmpFile << variableLine;
    }
    file.close();
    tmpFile.close();
    file.open(request.file, ios::out);
    tmpFile.open("tmp.data", ios::in);
    while (getline(tmpFile, variableLine)){
        file << variableLine << endl;
    }
    file.close();
    tmpFile.close();
}


void hashSetDel(const request& request){
    //команда: del имяТаблицы ключ
    fstream tmpFile("tmp.data", ios::out);
    if(!tmpFile.is_open()) throw runtime_error("Tmp file doesn't exist");
    fstream file(request.file, ios::in);
    if (request.query.size != 3) throw runtime_error("Wrong command syntax");
    string name = request.query[1]; //имя очереди
    string key = request.query[2];
    string variableLine; //считываемая строка с файла
    fileData var;
    bool varIsExist = false;
    while (getline(file, variableLine)){ //проверяем все существующие переменные
        if (variableLine == " " || variableLine.empty()) continue;
        var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
        var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
        if (var.name == name){ //если такая переменная существует
            varIsExist = true; //закрываем защёлку
            hashMap currVar = hMFromStr(var.data); //определяем реальную переменную этого Типа данных
            currVar.del(key);
            variableLine = var.name + ';' + strFromHM(currVar);//превращаем переменную в текст
            if (currVar.pairCount != 0){
                tmpFile << variableLine << endl;
            }
        }
        else {
            tmpFile << variableLine << endl;
        }
    }
    file.close();
    tmpFile.close();
    if (!varIsExist){
        cout << "Tis queue doesn't exist" << endl;
    } else {
        file.open(request.file, ios::out);
        tmpFile.open("tmp.data", ios::in);
        while (getline(tmpFile, variableLine)){
            file << variableLine << endl;
        }
        file.close();
        tmpFile.close();
    }
}


void hashSetGet(const request& request){
//структура команды: Get имяТаблицы [ключ]
    fstream file(request.file, ios::in);
    if (request.query.size == 2) {
        string name = request.query[1];
        string variableLine; //считываемая строка с файла
        fileData var;
        bool varIsExist = false;
        while (getline(file, variableLine)){ //проверяем все существующие переменные
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
            var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
            if (var.name == name){ //если такая переменная существует
                varIsExist = true; //закрываем защёлку
                hashMap currVar = hMFromStr(var.data); //определяем реальную переменную этого Типа данных
                cout << currVar.Get() << endl;
            }
        }
        if (!varIsExist){
            cout << "This hashMap isn't exist" << endl;
        }
    }
    else if (request.query.size == 3){
        string name = request.query[1];
        string key = request.query[2];
        string variableLine; //считываемая строка с файла
        fileData var;
        bool varIsExist = false;
        while (getline(file, variableLine)){ //проверяем все существующие переменные
            if (variableLine == " " || variableLine.empty()) continue;
            var.name = splitToArr(variableLine, ';')[0]; //определяем их имена
            var.data = splitToArr(variableLine, ';')[1]; //и то, что они хранят
            if (var.name == name){ //если такая переменная существует
                varIsExist = true; //закрываем защёлку
                hashMap currVar = hMFromStr(var.data); //определяем реальную переменную этого Типа данных
                if (currVar.pairCount == 0) cout << "this HashMap is empty" << endl;
                else {
                    if (currVar.Get(key).key.empty()){
                        cout << "there is no value for this key" << endl;
                    }
                    else {
                        cout << currVar.Get(key) << endl;
                    }
                }
            }
        }
        if (!varIsExist){
            cout << "This hashMap isn't exist" << endl;
        }
    }
    else throw runtime_error("Wrong command syntax");

}

