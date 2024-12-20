#ifndef LIST_H
#define LIST_H

#include "Pair.h"
#include <string>
#include <sstream>
using std::string, std::ostream;

template <typename T>
struct ListNode {
    T value;
    ListNode* next;
    ListNode* previous;

    //конструкторы
    ListNode(T val, ListNode* following, ListNode* prev) : value(val), next(following), previous(prev) {}
    ListNode(T val) : value(val), next(nullptr), previous(nullptr) {}
    ListNode() : value(T()), next(nullptr), previous(nullptr) {} //не уверен, но тут могут возникать ошибки, если нет конструктора по умолчанию для АТД
};



template <typename T>
struct List{
    ListNode<T>* first;
    ListNode<T>* last;

    //конструктор
    List<T>(): first(nullptr), last(nullptr) {}

    void headInsert(T value);
    void backInsert(T value);
    void delFirst();
    void delLast();
    void delByVal(T val);
    bool find(T value);


    friend ostream& operator<<(ostream& os, const List<T>& ls) {
        ListNode<T> *curr = ls.first;
        os << "{";
        while (curr != nullptr){
            os << "[" << curr->value << "]";
            if (curr->next != nullptr) {
                os << " <=> ";
            }
            curr = curr->next;
        }
        os << "}";
        return os;
    }


};

template struct List<Pair>;
template struct List<int>;
template struct List<string>;

List<string> splitToList(const string &input, const char &delimiter = ' ');
string unSplitList(const List<string>& input, const char &delimiter = ' ');
List<Pair> splitToListPair(const string &input, const string& pairDelimiter, const char &keyValueDelimiter);


#endif // LIST_H
