#include "stdafx.h"
#include "App.h"
#include "asyncMongo.hpp"
#include "StringIconv.h"
#include "Users.hpp"
#include "Authen.hpp"
#include "MongoDB.hpp"

using namespace std;

//TODO:允许生成core文件的命令
//ulimit -c unlimited

//统计客户端数量
static int COUNT_CLIENTS = 1;
//管理所有的客户端类
static map<uWS::WebSocket<false, true> *, CUsers *> mapUsers;

//TODO1:时间戳转换函数
void TestOutputTime()
{
}

int main()
{
    //InitMongo
    MongoInfoDef mgInfo = {};
    snprintf(mgInfo.szUrl, sizeof(mgInfo.szUrl), "mongodb://localhost:27017");
    snprintf(mgInfo.szDbName, sizeof(mgInfo.szDbName), "db_henry");
    snprintf(mgInfo.szColName, sizeof(mgInfo.szColName), "tb_henry");
    CMongoDB::SetMongoInfo(mgInfo);
    //TestOutputTime();
    //======================================================
    /* ws->getUserData returns one of these */
    struct PerSocketData
    {
    };
    /* Very simple WebSocket echo server */
    uWS::App myWS;
    uWS::App::WebSocketBehavior behavior = {};
    behavior.compression = uWS::SHARED_COMPRESSOR;
    behavior.maxPayloadLength = 16 * 1024;
    behavior.idleTimeout = 30;
    behavior.maxBackpressure = 1 * 1024 * 1204;

    /* Handlers */
    behavior.open = [](auto *ws, auto *req) {
        // WebSocket*  ws
        // HttpRequest* req
        std::string strIP(ws->getRemoteAddress());
        cout << "getRemoteAddress: " << strIP.c_str() << endl;
        //getQuery(): username=henry1&password=123456&act=1
        cout << "getQuery(): " << req->getQuery() << endl;

        CMongoDB::printMillisecond("TIMERA1");

        LogInParaDef loginPara = {};
        string strQuery(req->getQuery());              //url附带的参数
        GetUserLoginPara(strQuery.c_str(), loginPara); //解析url里面的参数

        CMongoDB::printMillisecond("TIMERA2");

        RetLoginDef retData = {};
        HandleUserRAndL(loginPara, retData); //处理登陆/注册请求
        rspClientLogin(ws, retData);         //返回客户端[注册/登陆]返回的消息

        CMongoDB::printMillisecond("TIMERA3");

        if (0 == retData.iState && retData.iUserId > 0)
        {

            CMongoDB::printMillisecond("TIMERA4");

            UserInfoDef userInfo;
            userInfo.iUserId = retData.iUserId;
            snprintf(userInfo.szUserName, sizeof(userInfo.szUserName), retData.szUserName);
            CUsers *oneUser = new CUsers(ws, uWS::OpCode::TEXT, userInfo); ///behavior.message   how to bind this...
            mapUsers[ws] = oneUser;

            CMongoDB::printMillisecond("TIMERA5");
        }
        else
        {
            cout << "something wrong.register or login failed." << endl;
        }

        CMongoDB::printMillisecond("TIMERA6");
    };

    /// bool send(std::string_view message, uWS::OpCode opCode = uWS::OpCode::BINARY, bool compress = false)
    behavior.message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
        cout << "message:-----------------BBBBBBBBBBBBBBBBBBBBBBBBBBBBB-------behavior.message" << endl;
        // cout << "opCode: " << opCode << endl;
        // cout << "message: " << message << endl;
        // cout << "message.size(): " << message.size() << endl;
        // ///==================== parse client msg====================
        // mapUsers[ws]->handleInComing(message, opCode);
    };

    behavior.drain = [](auto *ws) {
        /* Check getBufferedAmount here */
        cout << "------------behavior.drain ---------" << endl;
    };

    behavior.ping = [](auto *ws) {
        cout << "-----------------behavior.ping ---------" << endl;
    };

    behavior.pong = [](auto *ws) {
        cout << "-----------behavior.pong ---------" << endl;
    };

    behavior.close = [](auto *ws, int code, std::string_view message) {
        cout << "-------------------behavior.close ---------" << endl;
        cout << "message:" << message << endl;
        delete mapUsers[ws];
    };

    //    myWS.ws<PerSocketData>("/*", behavior);
    myWS.get("/*", [](auto *res, auto *req) {
        res->end("Hello uWebSockets World!");
    });

    myWS.ws<PerSocketData>("/*", std::move(behavior));

    myWS.listen(9001, [](auto *token) {
        if (token)
        {
            std::cout << "Thread " << std::this_thread::get_id() << " listening on port " << 9001 << std::endl;
        }
        else
        {
            std::cout << "Thread " << std::this_thread::get_id() << " failed to listen on port 9001" << std::endl;
        }
    });

    myWS.run();
}
