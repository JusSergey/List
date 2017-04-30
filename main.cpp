#include <iostream>
#include <list>
#include "List.h"

using namespace std;

typedef List<int> LIST;

template <typename T>
void print(const List<T> &lst) {

    if (lst.empty())
        return;

    for (auto it = lst.cbegin(); it != lst.cend(); ++it){
        std::cout << it.data() << "   ";
    }

    std::cout << '\n';
}

int main () {

    LIST l1{1,2, 3, 4, 5};
    LIST l2{1,3, 5, 7, 9};

    {
        List<List<int>> l3;
        l3.push_back(std::move(l1));
        l3.push_back(std::move(l2));

        l3.find(l2).data().begin().data()=-1;

        for (auto i = l3.begin(); i != l3.end(); ++i)
            print(i.data());
    }

    cin.get();

    return 0;
}


