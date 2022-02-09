#include <iostream>

#include "question.hpp"

using namespace std;

int main()
{
    Question q(4);

    Set p(4);
    p[2] = 1;

    cout << sizeof(Set) << endl;
    
    cout << q << endl;

    cout << q.is_total() << endl;
    cout << q.covers(p) << endl;

    p[0] = 1;

    cout << q.is_total() << endl;

    Set big(4, 0b0111);
    q.add(big);

    cout << q << endl;

    cout << q.is_total() << endl;

    Set total(4,0b1111);
    q.add(total);

    cout << q << endl;
    cout << q.is_total() << endl;


    return 0;
}
