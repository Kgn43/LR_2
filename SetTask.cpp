#include "SetTask.h"


void fill(Set &set1, Set &set2) {
    set1.clear();
    set2.clear();
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set1.insert(4);
    set1.insert(5);
    set1.insert(6);
    set1.insert(7);

    set2.insert(5);
    set2.insert(6);
    set2.insert(7);
    set2.insert(8);
    set2.insert(9);
    set2.insert(10);
}


Set setUnion(Set &set1, Set &set2) {
    Set result;
    int num;
    while (set1.pairCount != 0){
        num = set1.Get();
        result.insert(num);
        set1.del(num);
    }
    while (set2.pairCount != 0){
        num = set2.Get();
        if (!result.at(num)) result.insert(num);
        set2.del(num);
    }
    return result;
}


Set setIntersection(Set &set1, const Set &set2) {
    Set result;
    while (set1.pairCount != 0){
        int num = set1.Get();
        if (set2.at(num)) result.insert(num);
        set1.del(num);
    }
    return result;
}


Set setDifference(Set &set1, Set &set2) {
    Set result;
    int num;
    while (set1.pairCount != 0){
        num = set1.Get();
        result.insert(num);
        set1.del(num);
    }
    while (set2.pairCount != 0){
        num = set2.Get();
        if (result.at(num)) {
            result.del(num);
        }
        set2.del(num);
    }
    return result;
}


void setTask() {
    Set set1;
    Set set2;
    fill(set1, set2);
    cout << "set1: " << set1 << endl;
    cout << "set2: " << set2 << endl;
    cout << "set1 union set2: " << setUnion(set1, set2) << endl;
    fill(set1, set2);
    cout << "set1 intersection set2: " << setIntersection(set1, set2) << endl;
    fill(set1, set2);
    cout << "set1 difference set2: " << setDifference(set1, set2) << endl;
    fill(set1, set2);
    cout << "set2 difference set1: " << setDifference(set2, set1) << endl;
}