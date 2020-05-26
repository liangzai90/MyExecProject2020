#include "stdafx.h"
#include "MongoDB.hpp"
//INC_DIR=-I/opt/mongo-cxx-driver/include/mongocxx/v_noabi/  -I/opt/mongo-cxx-driver/include/bsoncxx/v_noabi/
//LIB_DIR=-L/opt/mongo-cxx-driver/lib64/
//LIB=-lmongocxx -lbsoncxx

#include <chrono>
#include <mongocxx/index_model.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/options/find.hpp>
#include <mongocxx/options/find_one_and_update.hpp>
#include <mongocxx/exception/exception.hpp>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/basic/helpers.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/json.hpp>

using bsoncxx::type;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using namespace std;

//static member declare Needed.
MongoInfoDef CMongoDB::mgInfo;
bool CMongoDB::bMgInstance = false; //mongo 实例只能初始化一次
int CMongoDB::iBaseUserID = 10000;  //userid最小值

void CMongoDB::createMonoInstance()
{
    mongocxx::instance instance{}; // This should be done only once.
    CMongoDB::bMgInstance = true;
}

void CMongoDB::printMillisecond(const char* tag)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    cout <<tag<<":--------------:"<< tv.tv_sec*1000 + tv.tv_usec/1000 <<endl;
}

void CMongoDB::MongoTest()
{
    cout << "CMongoDB::MongoTest()" << endl;
    mongocxx::client client{mongocxx::uri{}};
    mongocxx::database db = client[CMongoDB::mgInfo.szDbName];
    // Query for all the documents in a collection.
    {
        // @begin: cpp-query-all
        cout << "find() userlist ------------->>>Start" << endl;
        auto cursor = db[CMongoDB::mgInfo.szColName].find(make_document(kvp("username", "henry666")));

        auto count = std::distance(cursor.begin(), cursor.end());
        cout << "count:" << count << endl;

        if (cursor.begin() == cursor.end())
        {
            cout << "cursor length() is 000" << endl;
        }
        for (auto &&doc : cursor)
        {
            std::cout << bsoncxx::to_json(doc) << std::endl;
        }
        cout << "find() userlist ------------->>>End" << endl;
        // @end: cpp-query-all
    }

    {

        // stdx::optional<bsoncxx::document::value> mongocxx::collection::find_one_and_update	(
        //	  bsoncxx::document::view_or_value 	filter,
        //    bsoncxx::document::view_or_value 	update,
        //    const options::find_one_and_update & 	options = options::find_one_and_update()
        // )

        cout << "find_one_and_update() userlist ------------" << endl;
        // @begin: cpp-update-top-level-fields

        // stdx::optional<bsoncxx::document::value> find_one_and_update(
        //     bsoncxx::document::view_or_value filter,
        //     bsoncxx::document::view_or_value update,
        //     const options::find_one_and_update& options = options::find_one_and_update());

        mongocxx::options::find_one_and_update opts;                       //返回类型设置
        opts.upsert(true);                                                 //如果没有，插入新的
        opts.return_document(mongocxx::options::return_document::k_after); //返回更新后的文档

        auto doc = db[CMongoDB::mgInfo.szColName].find_one_and_update(
            make_document(kvp("username", "henry5")),
            make_document(kvp("$inc", make_document(kvp("userid", 1)))),
            opts);

        auto testa = doc->view();

        cout << "find_one_and_update:" << bsoncxx::to_json(testa) << endl;
        cout << "length:" << testa.length() << endl;

        if (testa["userid"] && testa["userid"].type() == type::k_int32)
        {
            cout << "userid:" << testa["userid"].get_int32().value << endl;
        }

        if (testa["username"] && testa["username"].type() == type::k_utf8)
        {
            cout << "username:" << testa["username"].get_utf8().value << endl;

            std::string level = string(testa["username"].get_utf8().value);
            if (level.compare("henry5") == 0)
            {
                cout << "Is henry5" << endl;
            }
            else
            {
                cout << "is NOT henry5" << endl;
            }
        }

        //            make_document(kvp("$set", make_document(kvp("password", "555"))))
        // @end: cpp-update-top-level-fields
    }

    {
        cout << "update_one() userlist ------------" << endl;
        // @begin: cpp-update-top-level-fields
        db[CMongoDB::mgInfo.szColName].update_one(
            make_document(kvp("username", "henry1")),
            make_document(kvp("$set", make_document(kvp("password", "666")))));
        // @end: cpp-update-top-level-fields
    }
}

void CMongoDB::SetMongoInfo(MongoInfoDef &_mgInfo)
{
    memset(&(CMongoDB::mgInfo), 0, sizeof(CMongoDB::mgInfo));
    snprintf(CMongoDB::mgInfo.szUrl, sizeof(CMongoDB::mgInfo.szUrl), _mgInfo.szUrl);
    snprintf(CMongoDB::mgInfo.szDbName, sizeof(CMongoDB::mgInfo.szDbName), _mgInfo.szDbName);
    snprintf(CMongoDB::mgInfo.szColName, sizeof(CMongoDB::mgInfo.szColName), _mgInfo.szColName);
    if (!CMongoDB::bMgInstance)
    {
        cout << "createMonoInstance  ----11111 " << endl;
        CMongoDB::createMonoInstance();
    }
    else
    {
        cout << "createMonoInstance  ----2222 " << endl;
    }
}

bool CMongoDB::userRegister(LogInParaDef &loginPara, RetLoginDef &retData)
{
    cout << "CMongoDB::userRegister" << endl;
    bool bSuccess = true;
    mongocxx::client client{mongocxx::uri{}};
    mongocxx::database db = client[CMongoDB::mgInfo.szDbName];

    cout << "find() userlist ------------->>>Start" << endl;
    //TODO:STEP1:find info if exist
    auto cursor = db[CMongoDB::mgInfo.szColName].find(make_document(kvp("username", loginPara.szUserName)));
    auto count = std::distance(cursor.begin(), cursor.end());
    if (count != 0L)
    {
        // invalid
        cout << "Invalid register.账号已存在" << endl;
        bSuccess = false;
        retData.iState = 1;
        retData.iMsgID = ID_S2C_REGISTER;
        snprintf(retData.szUserName, sizeof(retData.szUserName), loginPara.szUserName);
        snprintf(retData.msg, sizeof(retData.msg), "账号已存在，请登录");
        return bSuccess;
    }
    else
    {
        //TODO:STEP2: generator and get userid
        mongocxx::options::find_one_and_update opts;                       //返回类型设置
        opts.upsert(true);                                                 //如果没有，插入新的
        opts.return_document(mongocxx::options::return_document::k_after); //返回更新后的文档
        auto doc = db[CMongoDB::mgInfo.szColName].find_one_and_update(
            make_document(kvp("INCREASE_KEY", "henry2020")),
            make_document(kvp("$inc", make_document(kvp("USER_COUNT", 1)))),
            opts);
        auto oneUserView = doc->view(); //value to view
        if (oneUserView["USER_COUNT"] && oneUserView["USER_COUNT"].type() == type::k_int32)
        {
            int iUserId = oneUserView["USER_COUNT"].get_int32().value + CMongoDB::iBaseUserID;
            retData.iUserId = iUserId;
            retData.iState = 0;
            retData.iMsgID = ID_S2C_REGISTER;
            snprintf(retData.szUserName, sizeof(retData.szUserName), loginPara.szUserName);
            snprintf(retData.msg, sizeof(retData.msg), "注册成功");

            //TODO:STEP3:insert one user info
            mongocxx::collection coll = db[CMongoDB::mgInfo.szColName];
            bsoncxx::document::value oneUser = make_document(
                kvp("username", loginPara.szUserName),
                kvp("password", loginPara.szPwd),
                kvp("userid", iUserId));
            try
            {
                coll.insert_one(std::move(oneUser));
            }
            catch (const mongocxx::exception &e)
            {
                std::cout << "An exception occurred while inserting: " << e.what() << std::endl;
                retData.iState = 2;
                bSuccess = false;
                return bSuccess;
            }

            cout << "注册成功.userid:" << retData.iUserId << ", username:" << retData.szUserName << endl;
            return bSuccess; //register success
        }
        else
        {
            cout << "数据库异常，注册失败" << endl;
            bSuccess = false;
            retData.iState = 1;
            retData.iMsgID = ID_S2C_REGISTER;
            snprintf(retData.szUserName, sizeof(retData.szUserName), loginPara.szUserName);
            snprintf(retData.msg, sizeof(retData.msg), "数据库异常，注册失败");
            return bSuccess;
        }
    }
    return bSuccess;
}

bool CMongoDB::userLogin(LogInParaDef &loginPara, RetLoginDef &retData)
{
    bool bSuccess = true;
    retData.iMsgID = ID_S2C_LOGIN;
    snprintf(retData.szUserName, sizeof(retData.szUserName), loginPara.szUserName);
    mongocxx::client client{mongocxx::uri{}};
    mongocxx::database db = client[CMongoDB::mgInfo.szDbName];
    //TODO:STEP1:find info if exist
    auto cursor = db[CMongoDB::mgInfo.szColName].find(make_document(kvp("username", loginPara.szUserName)));

    //TODO:[error]用了distance，容器就变为空了
    //    auto count = std::distance(cursor.begin(), cursor.end());
    if (cursor.begin() == cursor.end())
    {
        // invalid
        cout << "Invalid login.账号不存在，请注册" << endl;
        bSuccess = false;
        retData.iState = 1;
        snprintf(retData.msg, sizeof(retData.msg), "账号不存在，请注册");
        return bSuccess;
    }
    // else if (count != 1)
    // {
    //     // invalid
    //     cout << "Invalid login.数据库异常，玩家存在多条注册信息。请联系客服或管理员" << endl;
    //     bSuccess = false;
    //     retData.iState = 2;
    //     snprintf(retData.szUserName, sizeof(retData.szUserName), loginPara.szUserName);
    //     snprintf(retData.msg, sizeof(retData.msg), loginPara.szUserName, "数据库异常，玩家存在多条注册信息。请联系客服或管理员");
    //     return bSuccess;
    // }
    else
    {
        //TODO:STEP2:check password
        auto oneUserView = *cursor.begin();
        if (oneUserView["password"] && oneUserView["password"].type() == type::k_utf8)
        {
            std::string password(oneUserView["password"].get_utf8().value); //TODO.test this string...
            if (password.compare(loginPara.szPwd) != 0)
            {
                cout << "Invalid login.密码不正确,登陆失败" << endl;
                bSuccess = false;
                retData.iState = 2;
                snprintf(retData.msg, sizeof(retData.msg), "密码不正确,登陆失败");
                return bSuccess;
            }
            if (oneUserView["userid"] && oneUserView["userid"].type() == type::k_int32)
            {
                retData.iUserId = oneUserView["userid"].get_int32().value;
            }
            else
            {
                cout << "Invalid login.数据库异常，获取userid错误..不是int32类型" << endl;
                bSuccess = false;
                retData.iState = 2;
                snprintf(retData.msg, sizeof(retData.msg), "数据库异常，获取userid错误");
                return bSuccess;
            }

            cout << "登陆成功.userid:" << retData.iUserId << ", username:" << retData.szUserName << endl;
            bSuccess = true;
            retData.iState = 0; //login success
            snprintf(retData.msg, sizeof(retData.msg), ",登陆成功");
            return bSuccess;
        }
    }
    return bSuccess;
}

///    mongocxx::client client{mongocxx::uri{"mongodb://localhost/?replicaSet=replset"}};
///    mongocxx::uri uri{"mongodb://localhost:27017/?minPoolSize=3&maxPoolSize=3"};
///    mongocxx::client client{mongocxx::uri{"mongodb://localhost:27017"}};
