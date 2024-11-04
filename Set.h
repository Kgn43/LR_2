#ifndef SET_H
#define SET_H

#include "list.h"
#include "arr.h"
#include <iostream>

#define BUCKETS 10

using std::cout, std::endl, std::ostream;


struct Set {
    arr<list<int>> buckets;
    size_t bucketCount;
    size_t pairCount;

    Set(): pairCount(0), bucketCount(BUCKETS), buckets(BUCKETS){} //создаёт BUCKETS бакет
    explicit Set(size_t num): pairCount(0), bucketCount(num), buckets(num){} //создаёт num бакетов

    void insert(const int& value);
    void del(const int& value);
    bool at(const int& value) const;

    friend ostream& operator<<(ostream& os, const Set& set) {
        os << "{";
        for (size_t i = 0; i < set.bucketCount; i++){
            if (set.buckets[i].first == nullptr) continue;
            auto node = set.buckets[i].first;
            while (node != nullptr) {
                os << node->value;
                if (node->next != nullptr) {
                    os << ", ";
                }
                node = node->next;
            }
            if (i+1 < set.bucketCount && set.buckets[i + 1].first != nullptr) {
                os << ", ";
            }
        }
        os << "}" << endl;
        return os;
    }

    Set hMFromStr(const string& line);
    string strFromHM(Set input);

    size_t hash(const int& value) const;
    void coliseum();
    int Get() const {
        for (size_t i = 0; i < this->buckets.size; ++i){
            if (this->buckets[i].first != nullptr) return this->buckets[i].first->value;
        }
        //error
        return 0;
    }
};





#endif //SET_H
