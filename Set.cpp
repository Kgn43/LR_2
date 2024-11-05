#include "Set.h"

size_t Set::hash(const int& value) const {
    int hash = 0;
    int buff = value;
    while (buff != 0) {
        hash += buff % 10;
        buff = buff / 10;
    }
    return hash % this->bucketCount;
}



void Set::coliseum() {
    Set newSet(this->bucketCount * 2);
    list<int> oneBucket;
    listNode<int>* node;
    for (size_t i = 0; i < this->buckets.size; ++i){
        oneBucket = this->buckets[i];
        node = oneBucket.first;
        while(node != nullptr){
            newSet.insert(node->value);
            node = node->next;
        }
    }
    buckets = newSet.buckets;
    bucketCount = newSet.bucketCount;
    pairCount = newSet.pairCount;
}

void Set::insert(const int& value) {
    size_t thisHash = hash(value);
    bool isExist = false;
    for (auto i = this->buckets[thisHash].first; i != nullptr; i = i->next){
        if (i->value == value) isExist = true;
    }
    if (!isExist){
        this->buckets[thisHash].backInsert(value);
        this->pairCount++;
        if (this->bucketCount * this->bucketCount <= this->pairCount){
            coliseum();
        }
    }
    else {
        cout << "This value = " << value << " already in set" << endl;
    }
}


void Set::del(const int& value) {
    size_t thisHash = hash(value);
    this->buckets[thisHash].delByVal(value);
    this->pairCount--;

}

bool Set::at(const int &key) const {
    size_t thisHash = hash(key);
    listNode<int>* node = this->buckets[thisHash].first;
    while(node != nullptr){
        if (node->value == key){
            return true;
        }
        node = node->next;
    }
    return false;
}



Set hMFromStr(const string& line){
    arr<string> values = splitToArr(line, '_');
    Set output;
    for (size_t i = 0; i < values.size; ++i){
        output.insert(stoi(values[i]));
    }
    return output;
}


string strFromHM(Set input){
    string output;
    int num;
    while (input.pairCount != 0){
        num = input.Get();
        output += to_string(num) + "_";
        input.del(num);
    }
    return output;
}