#include "StackTask.h"

#include "Set.h"


void secondTask() {
    Set set;
    for (int i = 1 ; i < 20 ; i++) {
        set.insert(i);
    }
    cout << set;
    set.del(44);
    cout << set;
    set.del(18);
    cout << set;
    set.del(19);
    cout << set;
    set.del(4);
    cout << set;
    cout << set.at(55) << endl;
    cout << set.at(5) << endl;
}



int main() {
     // stackTask();
     // secondTask();

    return 0;
}