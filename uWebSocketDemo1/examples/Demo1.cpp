#include "App.h"
#include <thread>
#include <algorithm>
#include "test1.cpp"

int main() {

    
    CCar bmwCar("BMW 666");
    bmwCar.PrintCarInfo();

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

