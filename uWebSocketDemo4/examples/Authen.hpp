#ifndef __AUTHEN_HPP__
#define __AUTHEN_HPP__
#include "stdafx.h"
#include "MongoDB.hpp"
#include "json/json.h"

#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>
using namespace std;

//解析客户端连接请求里面的参数
void GetUserLoginPara(const char *szQuery, LogInParaDef &loginPara)
{
    char strKey1[32] = {};
    char strKey2[32] = {};
    char strKey3[32] = {};
    //username=henry1&password=123456&act=1
    sscanf(szQuery, "%[^=]=%[^&]&%[^=]=%[^&]&%[^=]=%d", strKey1, loginPara.szUserName, strKey2, loginPara.szPwd, strKey3, &loginPara.iAct);
    printf("GetUserLoginPara-------------------Begin:\r\n");
    printf("strKey1:%s, strValue1:%s \r\n", strKey1, loginPara.szUserName);
    printf("strKey2:%s, strValue2:%s \r\n", strKey2, loginPara.szPwd);
    printf("strKey3:%s, iValue3:%d \r\n", strKey3, loginPara.iAct);
    printf("GetUserLoginPara-------------------End:\r\n");
}

//处理客户端的注册和登陆请求
inline void HandleUserRAndL(LogInParaDef &loginPara, RetLoginDef &retData)
{
    RetLoginDef retLogin = {0};
    memset(&retData, 0, sizeof(retData));

    CMongoDB::printMillisecond("TIMER1");

    //register
    if (ID_C2S_REGISTER == loginPara.iAct)
    {
        cout << "[Authen] Register user: " << loginPara.szUserName << endl;

        CMongoDB::printMillisecond("TIMER2");

        auto result1(std::async(CMongoDB::userRegister, std::ref(loginPara), std::ref(retData)));
        bool bResult1 = result1.get();
        cout << "[Authen] Register bResult1: " << bResult1 << endl;

        CMongoDB::printMillisecond("TIMER3");
    }
    //login
    else if (ID_C2S_LOGIN == loginPara.iAct)
    {
        cout << "[Authen] Login user: " << loginPara.szUserName << endl;

        CMongoDB::printMillisecond("TIMER4");

        auto result2(std::async(CMongoDB::userLogin, std::ref(loginPara), std::ref(retData)));
        bool bResult2 = result2.get();
        cout << "[Authen] Login bResult2: " << bResult2 << endl;

        CMongoDB::printMillisecond("TIMER5");
    }
    else
    {
        cout << "[Authen]  UNKNOW  MESSAGE "
             << " iAct:" << loginPara.iAct << ",name:" << loginPara.szUserName << ", pwd:" << loginPara.szPwd << endl;
    }

    CMongoDB::printMillisecond("TIMER6");
}

void rspClientLogin(auto *ws, RetLoginDef &retData)
{
    Json::Value sendObjVal;
    //common data
    sendObjVal["state"] = retData.iState;
    sendObjVal["msgId"] = retData.iMsgID;
    sendObjVal["userId"] = retData.iUserId;

    sendObjVal["userName"] = retData.szUserName;
    sendObjVal["jsMsg"] = retData.msg;

    //Trans str to json string.
    Json::StreamWriterBuilder wbuilder;
    wbuilder["indentation"] = "";
    //    wbuilder["indentation"] = "\t";
    std::string document = Json::writeString(wbuilder, sendObjVal);
    ws->send(document, uWS::OpCode::TEXT);

    if (0 != retData.iState)
    {
        ws->end(retData.iState, retData.msg);
    }
}

#endif