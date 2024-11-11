#include "HashTask.h"


int recFunc(const hashMap &hm, hashMap &result, const string &key) {
    int num = 0;
    for (int i = 0; i < hm.bucketCount; ++i) {
        auto node = hm.buckets[i].first;
        while (node != nullptr) {
            if (node->value.value == key) {
                if (node->value.key != node->value.value) num++;
            }
            node = node->next;
        }
    }
    if (num == 0) {
        return 0;
    }
    for (int i = 0; i < hm.bucketCount; ++i) {
        auto node = hm.buckets[i].first;
        while (node != nullptr) {
            if (node->value.value == key) {
                if (node->value.key != node->value.value) num += recFunc(hm, result, node->value.key);
            }
            node = node->next;
        }
    }
    cout << num << endl;
    return num;
}


hashMap solve(hashMap &hm1) {
    hashMap result;
    hashMap hmInputCopy;
    hmInputCopy.copy(hm1);
    Pair pr;

    while (hmInputCopy.pairCount != 0) {
        pr = hmInputCopy.Get();
        if (!result.at(pr.key)) {
            result.insert(pr.key, "0");
        }
        if (!result.at(pr.value)) {
            result.insert(pr.value, "0");
        }
        hmInputCopy.del(pr.key);
    }
    for (int i = 0; i < hm1.bucketCount; ++i) {
        auto node = hm1.buckets[i].first;
        while (node != nullptr) {
            pr = result.Get(node->value.key);
            pr.value = to_string(recFunc(hm1, result, node->value.key));
            result.del(pr.key);
            result.insert(pr);
            node = node->next;
        }
    }
    cout << result << endl;
    return result;
}


void hashTask() {
    hashMap hm1;
    hm1.insert("A", "B");
    hm1.insert("C", "B");
    hm1.insert("D", "F");
    hm1.insert("B", "F");
    hm1.insert("F", "F");
    cout << hm1 << endl;
    const hashMap result = solve(hm1);
    cout << result << endl;
}

