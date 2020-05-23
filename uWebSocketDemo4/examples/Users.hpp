#ifndef __USERS_H_HENRY_
#define __USERS_H_HENRY_
#include "stdafx.h"
#include "App.h"
#include "json/json.h"
#include "libusockets.h"
#include "MongoDB.hpp"

using namespace std;

class CUsers
{
public:
    //    CUsers(uWS::WebSocket<false, true> &&ws, uWS::OpCode &&opCode);
    CUsers(uWS::WebSocket<false, true> *ws, uWS::OpCode opCode) : m_pwsClient(ws), m_OpCode(opCode)
    {
        //init(_behavior);
        cout << "create a new User" << endl;
    }
    ~CUsers()
    {
        cout << "deleted one User." << endl;
    };

public:
    /** 消息入口，服务器 接收并处理 客户端发来的消息.根据主消息号、子消息号去判断具体消息   */
    void handleInComing(std::string_view message, uWS::OpCode opCode)
    {
        cout << "handleInComing begin:" << endl;
        //  string strTemp2(message);
        string strTemp(std::move(message));
        std::istringstream iss(strTemp.c_str()); //need tarns to isstring type  .
        Json::Value readValue;
        Json::CharReaderBuilder rbuilder;
        rbuilder["collectComments"] = false;
        std::string errs;
        bool ok = Json::parseFromStream(rbuilder, iss, &readValue, &errs);
        cout << "----------parse json data:--------------" << endl;
        cout << "ok: " << ok << endl;
        cout << "state: " << readValue["state"].asInt() << endl;
        cout << "msgId: " << readValue["msgId"].asString() << endl;
        cout << "timeStamp: " << readValue["timeStamp"].asInt() << endl;
        cout << "jsData: " << readValue["jsData"].asString() << endl;

        string strJsData = readValue["jsData"].asString();
        cout << "strJsData:" << strJsData << endl;
        //====send a msg to client >>>>>
        SendClientMsg();
    }
    /**处理 客户端断开连接 */
    void handleClose()
    {
        cout << "handleClose----------------->>>>>" << endl;
    }

    //================= handle client msg
    /**处理客户端的 hello 消息 */
    //TODO:参数转为右值形式
    void handleSayHello(std::string_view message)
    {
        cout << "handleSayHello----------------->>>>>" << endl;
    }

    //=============== send msg to client
    void SendClientMsg()
    {
        Json::Value sendObjVal;
        //common data
        sendObjVal["state"] = 0;
        sendObjVal["msgId"] = ID_S2C_TEST1;
        
        sendObjVal["timeStamp"] = time(NULL);

        /// other Add data
        sendObjVal["userId"] = userInfo.iUserId;
        sendObjVal["userName"] = userInfo.szUserName;
        sendObjVal["jsMsg"] = "Hello client.S2C:到此一游20200520";

        //Trans str to json string.
        Json::StreamWriterBuilder wbuilder;
        wbuilder["indentation"] = "";
        //    wbuilder["indentation"] = "\t";
        std::string document = Json::writeString(wbuilder, sendObjVal);
        m_pwsClient->send(document, m_OpCode);
    }
    void SendErrorCode(MsgTypeBaseDef oneError)
    {
        cout << "SendErrorCode----------------->>>>>" << endl;
    }

    void SetUserInfo(UserInfoDef &_userInfo)
    {
        userInfo.iUserId = _userInfo.iUserId;
        snprintf(userInfo.szUserName, sizeof(userInfo.szUserName), _userInfo.szUserName);
    }

private:
    void init(const uWS::App::WebSocketBehavior &behavior)
    {
        cout << "init----------------->>>>>" << endl;
    }

private:
    // template <bool SSL, bool isServer>.
    //param1:false is no ssl,is App; true is ssl,is SSLApp.
    //param2:true, is server; false, is client.
    // wsClient can send msg to client.
    uWS::WebSocket<false, true> *m_pwsClient;
    uWS::OpCode m_OpCode;
    UserInfoDef userInfo;
    //    uWS::App::WebSocketBehavior& behavior;
};

#endif
