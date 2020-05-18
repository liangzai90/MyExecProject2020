#include <iostream>
#include <string>
#include "../include/json/json.h"

using namespace std;

// g++ demo1.cpp -I ../include  ./lib_json/libjsoncpp.a -std=c++11

int main()
{
    Json::Value objectRoot;
    objectRoot["id"] = 1234;
    objectRoot["name"] = "henry";


    cout <<"------------StreamWriterBuilder------------"<<endl;
    Json::StreamWriterBuilder wbuilder;
    wbuilder["indentation"] = "";
//    wbuilder["indentation"] = "\t";
    std::string document = Json::writeString(wbuilder, objectRoot);
    cout <<"StreamWriterBuilder: "<<document<<endl;

 
 
 
    char strBuf[]="{ \"id\":666, \"name\":\"henryHe\"}";
    cout <<"------------CharReaderBuilder------------"<<endl;
    std::istringstream iss(strBuf);  ////need tarns to isstring type  .
    Json::Value readValue;
    Json::CharReaderBuilder rbuilder;
    rbuilder["collectComments"] = false;
    std::string errs;
    bool ok = Json::parseFromStream(rbuilder, iss , &readValue, &errs);
    cout <<"ok: "<<ok<<endl;
    cout <<"id: "<<readValue["id"]<<endl;
    cout <<"name: "<<readValue["name"]<<endl;
    

//  const std::string rawJson = R"({"Age": 20, "Name": "colin"})";
//  const int rawJsonLength = static_cast<int>(rawJson.length());
//	cout <<   rawJsonLength<<endl;
//	cout <<   rawJson<<endl;


cout <<"hello world"<<endl;

  return 0;
}




