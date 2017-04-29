#include <iostream>
#include <list>
#include "List.h"

using namespace std;

typedef List<int> LIST;


int main () {

    LIST l, l2;

    for (int i = 0; i < 10; i++)
        l.push_back(i);


    l2 = l;
    l2.reverse();

    l.print();
    l2.print();

    cin.get();

    return 0;
}


