#include "ArrayTask.h"


bool maskCheck(const arr<char> &mask, const arr<char> &checkd) {
    int maskP = 0;
    int checkdP = 0;
    for (; maskP < mask.size && checkdP < checkd.size; maskP++, checkdP++) {
        if (mask[maskP] == '*') {
            ++maskP; ++checkdP;
            while (checkdP < checkd.size && mask[maskP] != checkd[checkdP]) {
                ++checkdP;
            }
            continue;
        }
        if (mask[maskP] == '?') {
            continue;
        }
        if (mask[maskP] != checkd[checkdP]) {
            return false;
        }
    }
    return checkdP == checkd.size && maskP == mask.size;
}


void arrayTask() {
    arr<char> arr1{"wof@stud.nstu.ru"};
    arr<char> arr2{"aboba@stud.nstu.ru"};
    arr<char> arr3{"hello"};
    arr<char> mask1{"*@stud.ns?u.ru"};
    arr<char> mask2{"*@stud.n?u.ru"};
    //cout << mask2 << endl;
    cout << maskCheck(mask1, arr1) << endl;
    cout << maskCheck(mask1, arr2) << endl;
    cout << maskCheck(mask2, arr1) << endl;
    cout << maskCheck(mask1, arr2) << endl;
}