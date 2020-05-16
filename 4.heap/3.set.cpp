/*************************************************************************
	> File Name: 3.set.cpp
	> Author: 
	> Mail: 
	> Created Time: 六  5/16 18:13:41 2020
 ************************************************************************/

#include <iostream>
#include <set>
using namespace std;

set<int> s;

int main() {
    s.insert(2);
    s.insert(1);
    s.insert(3);
    cout << *(s.begin()) << endl;
    s.erase(s.begin());
    cout << *(s.begin()) << endl;
    return 0;
}
