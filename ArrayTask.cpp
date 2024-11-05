#include "ArrayTask.h"


bool maskCheck(const arr<char> &mask, const arr<char> &checkd) {
    for (int i = 0, j = 0; i < checkd.size(); i++) {
        if (mask[i] == '*') {
            ++i; ++j;
            while (mask[i] != checkd[j]) {
                ++j;
            }
           
        }
    }
}


void arrayTask() {
    arr<char> arr1{"wof@stud.nstu.ru"};
    arr<char> arr2{"hello"};
    arr<char> arr3{"*@stud.ns?u.ru"};
    arr<char> arr4{"*@stud.n?u.ru"};
    cout << arr4 << endl;

}