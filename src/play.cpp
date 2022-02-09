#include <iostream>

#include "question.hpp"

using namespace std;

int main()
{
    Question q(4);

    Set p(4);
    p[2] = 1;
    
    cout << q << endl;

    cout << q.covers(p) << endl;

    p[0] = 1;

    cout << q.covers(p) << endl;

    q.add(p);

    cout << q << endl;

    return 0;
}
