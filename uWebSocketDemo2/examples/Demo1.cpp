#include "App.h"
#include <thread>
#include <algorithm>
#include "test1.cpp"
#include <iostream>
#include <string>
#include "../include/json/json.h"
using namespace std;

void testJsonReandWrite()
{
  Json::Value objectRoot;
    objectRoot["id"] = 12345;
    objectRoot["name"] = "Henry";


    cout <<"------------StreamWriterBuilder------------"<<endl;
    Json::StreamWriterBuilder wbuilder;
    wbuilder["indentation"] = "";
//    wbuilder["indentation"] = "\t";
    std::string document = Json::writeString(wbuilder, objectRoot);
    cout <<"StreamWriterBuilder: "<<document<<endl;

 
 
 
    char strBuf[]="{ \"id\":666, \"name\":\"HenryHe\"}";
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

}


int main() {

//===========================================
    
    CCar bmwCar("BMW 666");
    bmwCar.PrintCarInfo();
    
    testJsonReandWrite();
    
//===========================================
    
    

    /* ws->getUserData returns one of these */
    struct PerSocketData {

    };

    /* Simple echo websocket server, using multiple threads */
    std::vector<std::thread *> threads(std::thread::hardware_concurrency());

    std::transform(threads.begin(), threads.end(), threads.begin(), [](std::thread *t) {
        return new std::thread([]() {

            /* Very simple WebSocket echo server */
            uWS::App().ws<PerSocketData>("/*", {
                /* Settings */
                .compression = uWS::SHARED_COMPRESSOR,
                .maxPayloadLength = 16 * 1024,
                .idleTimeout = 10,
                .maxBackpressure = 1 * 1024 * 1204,
                /* Handlers */
                .open = [](auto *ws, auto *req) {

                },
                .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
					/// bool send(std::string_view message, uWS::OpCode opCode = uWS::OpCode::BINARY, bool compress = false) 
                    ws->send(message, opCode);
                },
                .drain = [](auto *ws) {
                    /* Check getBufferedAmount here */
                },
                .ping = [](auto *ws) {

                },
                .pong = [](auto *ws) {

                },
                .close = [](auto *ws, int code, std::string_view message) {

                }
            }).listen(9001, [](auto *token) {
                if (token) {
                    std::cout << "Thread " << std::this_thread::get_id() << " listening on port " << 9001 << std::endl;
                } else {
                    std::cout << "Thread " << std::this_thread::get_id() << " failed to listen on port 9001" << std::endl;
                }
            }).run();

        });
    });

    std::for_each(threads.begin(), threads.end(), [](std::thread *t) {
        t->join();
    });
}

