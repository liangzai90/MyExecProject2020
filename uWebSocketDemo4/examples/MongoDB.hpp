#ifndef __H_MONGODB__
#define __H_MONGODB__

#include "stdafx.h"
//INC_DIR=-I/opt/mongo-cxx-driver/include/mongocxx/v_noabi/  -I/opt/mongo-cxx-driver/include/bsoncxx/v_noabi/
//LIB_DIR=-L/opt/mongo-cxx-driver/lib64/
//LIB=-lmongocxx -lbsoncxx

#include <chrono>
#include <mongocxx/index_model.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/basic/helpers.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/uri.hpp>

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

class CMongoDB
{
public:
    static void SetMongoInfo(MongoInfoDef &_mgInfo);

    static bool userRegister(const LogInParaDef &loginPara, RetLoginDef &retData);

    static bool userLogin(const LogInParaDef &loginPara, RetLoginDef &retData);

    static void MongoTest();

private:
    static void createMonoInstance();
    static MongoInfoDef mgInfo;
    static bool bMgInstance;
    static int iBaseUserID;

private:
    CMongoDB() = delete;
    ~CMongoDB() = delete;
};

#endif