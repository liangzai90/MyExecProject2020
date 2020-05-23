#include <iostream>
#include "classA.h"
#include "test2.h"
using namespace std;

int main()
{

    ClassA AObj;
    AObj.print();

    printTest2();
    cout << "Hello world ! " << endl;
    return 0;
}
