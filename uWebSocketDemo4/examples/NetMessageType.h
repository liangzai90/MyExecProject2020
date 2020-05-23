#ifndef __NET_MESSAGE_TYPE_H__
#define __NET_MESSAGE_TYPE_H__

const int MAX_MESSAGE_LENGTH = 1024;
const int NAME_LENGTH = 32;
const int PWD_LENGTH = 32;
const int ERR_MSG_LENGTH = 100;
const int MONGO_URL_LENGTH = 100;

/**服务器和客户端通信的消息结构体V2.0 */
typedef struct tagMsgTypeBase
{
    int iState;                        //0正常，1,2,3,4分别对应不同的错误类型
    int iMsgId;                        //消息号
    int iTimeStamp;                    //时间戳
    char szMsgBuf[MAX_MESSAGE_LENGTH]; //消息字段内容，通常是一个json格式数据
} MsgTypeBaseDef;

//User  register/login data
typedef struct tagLogInPara
{
    int iAct;                     //1:register, 2:login
    char szUserName[NAME_LENGTH]; // 玩家名称
    char szPwd[PWD_LENGTH];       //玩家密码
} LogInParaDef;

//返回客户端注册/登陆的数据
typedef struct tagRetLogin
{
    int iState;                   //0正常，1,2,3,4分别对应不同的错误类型
    int iMsgID;                   //消息号
    int iUserId;                  //玩家id
    char szUserName[NAME_LENGTH]; //玩家名称
    char msg[ERR_MSG_LENGTH];     //返回给客户端的字符串
} RetLoginDef;

//服务器接收客户端消息的消息号
enum MsgID2Server
{
    ID_C2S_REGISTER = 1,
    ID_C2S_LOGIN
};

//客户端接收消息对应的消息号
enum MsgID2Client
{
    ID_S2C_REGISTER = 1000,
    ID_S2C_LOGIN,
    ID_S2C_TEST1
};

//Mongo Info
typedef struct tagMongoInfo
{
    char szUrl[MONGO_URL_LENGTH];     //mongo IP
    char szDbName[MONGO_URL_LENGTH];  //Mongo DataBase
    char szColName[MONGO_URL_LENGTH]; //Mongo table
} MongoInfoDef;

//userInfo
typedef struct tagUserInfo
{
    char szUserName[NAME_LENGTH]; // 玩家名称
    int iUserId;                  //玩家id
}UserInfoDef;

#endif