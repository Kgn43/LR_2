#include "list.h"


template<typename T>
void list<T>::backInsert(T value) {
    listNode<T>* newLast = new listNode(value);
    if (last == nullptr){
        last = newLast;
        first = newLast;
    }
    else{
        newLast->previous = last;
        last->next = newLast;
        last = newLast;
    }
}

template<typename T>
void list<T>::headInsert(T value) {
    listNode<T>* newFirst = new listNode(value);
    if (last == nullptr){
        last = newFirst;
        first = newFirst;
    }
    else{
        first->previous = newFirst;
        newFirst->next = first;
        first = newFirst;
    }
}


template<typename T>
void list<T>::delLast() {
    if (this->first->next == nullptr){
        delete this->last;
        this->first = nullptr;
        this->last = nullptr;
    }
    else {
        last = last->previous;
        delete last->next;
        last->next = nullptr;
    }
}


template<typename T>
void list<T>::delFirst() {
    if (this->last->previous == nullptr){
        delete this->first;
        this->first = nullptr;
        this->last = nullptr;
    }
    else {
        this->first = this->first->next;
        delete this->first->previous;
        this->first->previous = nullptr;
    }
}


template<typename T>
bool list<T>::find(T value) {
    listNode<T> *tmp = first;
    while (tmp != nullptr){
        if (tmp->value == value){
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}



template<typename T>
void list<T>::delByVal(T val) {
    if (this->first->value == val) {
        delFirst();
        return;
    }
    if (this->last->value == val) {
        delLast();
        return;
    }
    listNode<T> *tmp = first;
    while (tmp != nullptr){
        if (tmp->value == val){
            tmp->next->previous = tmp->previous;
            tmp->previous->next = tmp->next;
            delete tmp;
            return;
        }
        tmp = tmp->next;
    }
    cout << "Not found " << val << endl;
}


list<string> splitToList(const string &input, char delimiter){
    string word;
    list<string> output;
    for (auto ch : input){
        if (ch == delimiter) {
            output.backInsert(word);
            word = "";
        }
        else{
            word += ch;
        }
    }
    if (word != ""){
        output.backInsert(word);
    }
    return output;
}


string unSplitList(const list<string>& input, char delimiter){
    listNode<string>* curr = input.first;
    string output;
    while (curr != nullptr){
        output += curr->value + delimiter;
        curr = curr->next;
    }
    return output;
}
