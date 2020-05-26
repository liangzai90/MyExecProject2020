#ifndef __USERS_H_HENRY_
#define __USERS_H_HENRY_
#include "stdafx.h"
#include "App.h"
#include "f2/function2.hpp"
#include <string_view>
#include "json/json.h"
#include "libusockets.h"
#include "MongoDB.hpp"
using namespace std;

#define USER_SSL false
#define IS_SERVER true

class CUsers
{
public:
    CUsers(uWS::WebSocket<USER_SSL, IS_SERVER> *ws, uWS::OpCode opCode, UserInfoDef &_userInfo);
    ~CUsers();

public:
    /** 消息入口，服务器 接收并处理 客户端发来的消息.根据主消息号、子消息号去判断具体消息   */
    void handleInComing(std::string_view message, uWS::OpCode opCode);

    /**处理 客户端断开连接 */
    void handleClose();

    //================= handle client msg
    /**处理客户端的 hello 消息 */
    //TODO:参数转为右值形式
    void handleSayHello(std::string_view message);

    //=============== send msg to client
    void SendClientMsg(std::string strMsg, int msgID = ID_S2C_TEST1, int iState = 0, time_t timeStamp = time(NULL));

    void SendErrorCode(MsgTypeBaseDef oneError);

public:
    //两种写法，一种是User类里面写很多的静态方法，然后作为回调函数，传给websocket
    //第二种，写一些 lambda表达式，传给websocket。
    //两者的区别是，第一种方法需要定义很多静态函数；第二种方法不需要去定义静态函数

    // //TODO: define some callback here..
    // static void messageHandler(uWS::WebSocket<USER_SSL, IS_SERVER> *, std::string_view, uWS::OpCode);
    // static void drainHandler(uWS::WebSocket<USER_SSL, IS_SERVER> *);
    // static void closeHandler(uWS::WebSocket<USER_SSL, IS_SERVER> *, int, std::string_view);
    // static void pingHandler(uWS::WebSocket<USER_SSL, IS_SERVER> *);
    // static void pongHandler(uWS::WebSocket<USER_SSL, IS_SERVER> *);

private:
    // template <bool SSL, bool isServer>.
    //param1:false is no ssl,is App; true is ssl,is SSLApp.
    //param2:true, is server; false, is client.
    // wsClient can send msg to client.
    uWS::WebSocket<USER_SSL, IS_SERVER> *m_pwsClient;
    uWS::OpCode m_OpCode;
    UserInfoDef userInfo;
};

#endif
