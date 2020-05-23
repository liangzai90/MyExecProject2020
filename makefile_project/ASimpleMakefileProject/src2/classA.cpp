#include <iostream>
#include "classA.h"

using namespace std;

ClassA::ClassA()
{
    cout <<"ClassA  construct"<<endl;
}

ClassA::~ClassA()
{
    cout <<"ClassA  destruct"<<endl;
}

void ClassA::print()
{
    cout <<"I am ClassA "<<endl;
}