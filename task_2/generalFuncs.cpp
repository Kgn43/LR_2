#include "generalFuncs.h"

void callHelp(){ //я слишком поздно понял, что можно было написать батник))) ну, пусть будет так

    std::cout << std::endl << std::endl << "add --file FileName --query 'your query'" << std::endl << std::endl << std::endl << std::endl;

    std::cout << "Array syntax:" << std::endl;

    std::cout << "push:" << std::endl;
    std::cout << "\t\'Apush arrayName index value\'  - insert value by index" <<std::endl;
    std::cout << "\t\tOR" << std::endl;
    std::cout << "\t\'Apush arrayName value\'  - insert value at the end" << std::endl;

    std::cout << "delete:" << std::endl;
    std::cout << "\t\'Adel arrayName index\'  - delete value by index" <<std::endl;

    std::cout << "get:" << std::endl;
    std::cout << "\t\'AGet arrayName index\'  - get value from array by index" <<std::endl;
    std::cout << std::endl;


    std::cout << "Stack syntax:" << std::endl;

    std::cout << "push:" << std::endl;
    std::cout << "\t\'Spush stackName value\'  - insert value at the end" <<std::endl;

    std::cout << "pop:" << std::endl;
    std::cout << "\t\'Spop stackName\'  - delete last inserted value" <<std::endl;

    std::cout << "get:" << std::endl;
    std::cout << "\t\'SGet stackName\'  - get last inserted value" <<std::endl;
    std::cout << std::endl;


    std::cout << "List syntax:" << std::endl;

    std::cout << "push:" << std::endl;
    std::cout << "\t\'Lpush listName begin/end value\'  - insert value at the begin/end of list" << std::endl;

    std::cout << "del:" << std::endl;
    std::cout << "\t\'Ldel listName value/begin/end\'  - delete element from begin/end or delete by value" << std::endl;

    std::cout << "get:" << std::endl;
    std::cout << "\t\'LGet listName searchedValue\'  - determine if there is an element with this value in the list" << std::endl;
    std::cout << std::endl;


    std::cout << "Queue syntax:" << std::endl;

    std::cout << "push:" << std::endl;
    std::cout << "\t\'Qpush queueName value\'  - insert value at the end of queue" << std::endl;

    std::cout << "pop:" << std::endl;
    std::cout << "\t\'Qpop queueName\'  - delete element from begin of the queue" << std::endl;

    std::cout << "get:" << std::endl;
    std::cout << "\t\'QGet queueName\'  - get first inserted value" << std::endl;
    std::cout << std::endl;


    std::cout << "HashMap syntax:" << std::endl;

    std::cout << "insert:" << std::endl;
    std::cout << "\t\'Hinsert hashMapName key value\'  - insert value" << std::endl;

    std::cout << "del:" << std::endl;
    std::cout << "\t\'Hdel hashMapName key\'  - delete element from hashMap by key" << std::endl;

    std::cout << "get:" << std::endl;
    std::cout << "\t\'HGet hashMapName\'  - get one pair key-value" << std::endl;
    std::cout << std::endl;
    std::cout << "\t\tOR" << std::endl;
    std::cout << "\t\'push hashMapName key\'  - get one pair value by key" << std::endl;

}


bool isFileExist(const std::string& fileName){
    std::ifstream file(fileName);
    if(!file.is_open()) return false;
    file.close();
    return true;
}


string delFirstLetter(const string &input){
    string output;
    bool z = false;
    for(auto ch : input){
        if(!z){
            z = true;
        }
        else {
            output += ch;
        }
    }
    return output;
}


commands commandRequest(const string& input){
    if (input == "push") return commands::push;
    if (input == "pop") return commands::pop;
    if (input == "del") return commands::del;
    if (input == "Get") return commands::Get;
    if (input == "set") return commands::set;
    if (input == "insert") return commands::insert;
    if (input == "add") return commands::add;
    if (input == "at") return commands::at;
    else{
        throw runtime_error("This command isn't exist");
    }
}


structures structRequest(const string& input){
    if (input[0] == 'S' && input[1] == 'e' && input[2] == 't') return structures::SetStruct;
    if (input[0] == 'A') return structures::Array;
    if (input[0] == 'L') return structures::List;
    if (input[0] == 'Q') return structures::Queue;
    if (input[0] == 'S') return structures::stack;
    if (input[0] == 'H') return structures::HashMap;
    else{
        throw runtime_error("This structure is not exist");
    }
}


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


structures getType(const string& fName){
    string splited = splitToArr(fName, '.')[0];
    if (splited == "arr") return structures::Array;
    if (splited == "list") return structures::List;
    if (splited == "queue") return structures::Queue;
    if (splited == "stack") return structures::stack;
    if (splited == "hashMap") return structures::HashMap;
    if (splited == "set") return structures::SetStruct;
    else{
        throw runtime_error("This structure isn't exist");
    }
}


bool isItNumber(const std::string& str) {
    for (auto ch : str) {
        if (!isdigit(ch)) return false;
    }
    return true;
}


