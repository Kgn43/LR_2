#include "HashTask.h"




void hashTask() {
    hashMap hm1;
    hm1.insert("A", "Boris");
    cout << hm1 << endl;
    hm1.insert("B", "Boris");
    cout << hm1 << endl;
    hm1.insert("C", "Boris");
    cout << hm1 << endl;
    hm1.insert("D", "Britva");
    cout << hm1 << endl;
    hm1.insert("E", "Britva");
    cout << hm1 << endl;
    hashMap result;
    Pair pr;
    Pair buff;
    int num;
    while (hm1.pairCount != 0) {
        pr = hm1.Get();
        if (!result.at(pr.key)) {
            result.insert(pr.key, "0");
        }
        if (result.at(pr.value)) {
            buff = result.Get(pr.value);
            num = stoi(buff.value);
            ++num;
            result.del(buff.key);
            result.insert(buff.key, to_string(num));
        }
        else {
            result.insert(pr.value, "0");
        }
        hm1.del(pr.key);
    }
    cout << result << endl;
}

