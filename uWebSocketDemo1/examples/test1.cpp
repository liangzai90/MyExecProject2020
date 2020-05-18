#include <iostream>
#include <string>
using namespace std;


class  CCar
{
    public:
    string strCarName;
    CCar(string name){
    strCarName = name;
    cout <<"Car constructor."<<endl;    
    };
    
    ~CCar(){cout <<"Car constructor."<<endl;};
    
    public:
    void PrintCarInfo(){
        cout <<"This is car info: "<< strCarName <<endl;
    }
};

