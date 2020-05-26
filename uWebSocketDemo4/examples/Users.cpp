#include "stdafx.h"
#include "App.h"
#include "f2/function2.hpp"
#include <string_view>
#include "json/json.h"
#include "libusockets.h"
#include "MongoDB.hpp"
#include "Users.hpp"
using namespace std;

CUsers::CUsers(uWS::WebSocket<USER_SSL, IS_SERVER> *ws, uWS::OpCode opCode, UserInfoDef &_userInfo) : m_pwsClient(ws), m_OpCode(opCode)
{
    userInfo.iUserId = _userInfo.iUserId;
    snprintf(userInfo.szUserName, sizeof(userInfo.szUserName), _userInfo.szUserName);

    cout << "create a new User" << endl;
    std::string strMsg1("S2C:Create A New User Success!");
    SendClientMsg(strMsg1);

    //=======================bind some callback function to websocket
    m_pwsClient->InitCallbackMessageHandler([=](uWS::WebSocket<USER_SSL, IS_SERVER> *ws, std::string_view message, uWS::OpCode opCode) {
        cout << "InitCallbackMessageHandler-----------------receive client msg-----AAAAAAAA" << endl;
        cout << "opCode: " << opCode << endl;
        cout << "message: " << message << endl;
        cout << "message.size(): " << message.size() << endl;
        handleInComing(message, opCode);
    });

    m_pwsClient->InitCallbackDrainHandler([=](uWS::WebSocket<USER_SSL, IS_SERVER> *ws) {
        cout << "InitCallbackDrainHandler-----------------receive client msg-----BBBBBBBB" << endl;
        std::string strMsg("InitCallbackDrainHandler");
        SendClientMsg(strMsg);
    });

    m_pwsClient->InitCallbackCloseHandler([=](uWS::WebSocket<USER_SSL, IS_SERVER> *ws, int iState, std::string_view message) {
        cout << "InitCallbackCloseHandler-----------------receive client msg-----CCCCCCCC" << endl;
        cout << "iState: " << iState << endl;
        cout << "message: " << message << endl;
        std::string strMsg("InitCallbackCloseHandler");
        SendClientMsg(strMsg);
    });

    m_pwsClient->InitCallbackPingHandler([=](uWS::WebSocket<USER_SSL, IS_SERVER> *ws) {
        cout << "InitCallbackPingHandler-----------------receive client msg-----DDDDDDDD" << endl;
        std::string strMsg("InitCallbackPingHandler");
        SendClientMsg(strMsg);
    });

    m_pwsClient->InitCallbackPongHandler([=](uWS::WebSocket<USER_SSL, IS_SERVER> *ws) {
        cout << "InitCallbackPongHandler-----------------receive client msg-----EEEEEEEE" << endl;
        std::string strMsg("InitCallbackPongHandler");
        SendClientMsg(strMsg);
    });
}

CUsers::~CUsers()
{
    cout << "deleted one User." << endl;
}

/** 消息入口，服务器 接收并处理 客户端发来的消息.根据主消息号、子消息号去判断具体消息   */
void CUsers::handleInComing(std::string_view message, uWS::OpCode opCode)
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

    // string strJsData = readValue["jsData"].asString();
    // cout << "strJsData:" << strJsData << endl;
    //====send a msg to client >>>>>
    std::string strMsg("S2C:.何亮123");
    SendClientMsg(strMsg);
}

/**处理 客户端断开连接 */
void CUsers::handleClose()
{
    cout << "handleClose----------------->>>>>" << endl;
}

//================= handle client msg
/**处理客户端的 hello 消息 */
//TODO:参数转为右值形式
void CUsers::handleSayHello(std::string_view message)
{
    cout << "handleSayHello----------------->>>>>" << endl;
}

//=============== send msg to client
void CUsers::SendClientMsg(std::string strMsg, int msgID, int iState, time_t timeStamp)
{
    Json::Value sendObjVal;
    //common data
    sendObjVal["state"] = 0;
    sendObjVal["msgId"] = ID_S2C_TEST1;

    sendObjVal["timeStamp"] = time(NULL);

    /// other Add data
    sendObjVal["userId"] = userInfo.iUserId;
    sendObjVal["userName"] = userInfo.szUserName;
    sendObjVal["jsMsg"] = strMsg.c_str();

    //Trans str to json string.
    Json::StreamWriterBuilder wbuilder;
    wbuilder["indentation"] = "";
    //    wbuilder["indentation"] = "\t";
    std::string document = Json::writeString(wbuilder, sendObjVal);
    m_pwsClient->send(document, m_OpCode);
}

void CUsers::SendErrorCode(MsgTypeBaseDef oneError)
{
    cout << "SendErrorCode----------------->>>>>" << endl;
}
