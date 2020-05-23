#ifndef __AUTHEN_HPP__
#define __AUTHEN_HPP__
#include "stdafx.h"
#include "MongoDB.hpp"
#include "json/json.h"
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

    //register
    if (ID_C2S_REGISTER == loginPara.iAct)
    {
        cout << "[Authen] Register user: " << loginPara.szUserName << endl;
        CMongoDB::userRegister(loginPara, retData);
    }
    //login
    else if (ID_C2S_LOGIN == loginPara.iAct)
    {
        cout << "[Authen] Login user: " << loginPara.szUserName << endl;
        CMongoDB::userLogin(loginPara, retData);
    }
    else
    {
        cout << "[Authen]  UNKNOW  MESSAGE "
             << " iAct:" << loginPara.iAct << ",name:" << loginPara.szUserName << ", pwd:" << loginPara.szPwd << endl;
    }
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

    
    if(0 != retData.iState)
    {
        ws->end(retData.iState, retData.msg);
    }
}

#endif