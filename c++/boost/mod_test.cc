#include <string>
#include <iostream>
#include <map>
#include <tr1/functional>

#include "module.h"
#include "downstream/memcached/server.h"
#include "downstream/memcached/request.h"
#include "downstream/memcached/response.h"
#include "downstream/http/server.h"
#include "downstream/http/request.h"
#include "downstream/http/response.h"

using namespace std::tr1::placeholders;

class TestModule : public cloud_ucs::Module
{
    public:
        TestModule();
        ~TestModule();

        bool Init(const std::string& conf, int *thread_num);

        void Echo(const std::map<std::string, std::string>& params, const cloud_ucs::InvokeCompleteHandler& cb);
        void SetKey(const std::map<std::string, std::string>& params, const cloud_ucs::InvokeCompleteHandler& cb);
        void GetBaidu(const std::map<std::string, std::string>& params, const cloud_ucs::InvokeCompleteHandler& cb);

        void HandleSetKey(cloud_ucs::downstream::ErrCode ec, 
                boost::shared_ptr<cloud_ucs::downstream::memcached::SetResponse> response,
                const cloud_ucs::InvokeCompleteHandler& complete_handler,
                boost::shared_ptr<cloud_ucs::downstream::memcached::SetRequest> request);

        void HandleGetBaidu(cloud_ucs::downstream::ErrCode ec, 
                boost::shared_ptr<cloud_ucs::downstream::http::GetResponse> response, 
                const cloud_ucs::InvokeCompleteHandler& complete_handler, 
                boost::shared_ptr<cloud_ucs::downstream::http::GetRequest> request);

    private:
        cloud_ucs::downstream::memcached::Server* mc_server_;
        cloud_ucs::downstream::http::Server* baidu_server_;
};

TestModule::TestModule()
{
}

TestModule::~TestModule()
{
    delete mc_server_;
    delete baidu_server_;
}

bool TestModule::Init(const std::string& conf, int* thread_num)
{
    *thread_num = 1;

    std::cout << "TestModule::Init conf: " << conf << std::endl;

    Register("Echo", std::tr1::bind(&TestModule::Echo, this, _1, _2));
    Register("SetKey", std::tr1::bind(&TestModule::SetKey, this, _1, _2));
    Register("GetBaidu", std::tr1::bind(&TestModule::GetBaidu, this, _1, _2));

    mc_server_ = new cloud_ucs::downstream::memcached::Server(this, "tempt118.ops.zwt.qihoo.net", 11213);
    baidu_server_ = new cloud_ucs::downstream::http::Server(this, "www.baidu.com", 80);

    return true;
}

void TestModule::Echo(const std::map<std::string, std::string>& params, const cloud_ucs::InvokeCompleteHandler& cb)
{
    std::map<std::string, std::string>::const_iterator iter = params.begin();
    for (; iter != params.end(); ++iter)
    {
        printf("TestModule::Echo params %s->%s\n", iter->first.c_str(), iter->second.c_str());
    }

    cloud_ucs::InvokeResult result;
    result.__set_results(params);

    cb(result);
}

void TestModule::SetKey(const std::map<std::string, std::string>& params, const cloud_ucs::InvokeCompleteHandler& cb)
{
    cloud_ucs::InvokeResult result;
    std::map<std::string, std::string>::const_iterator iter = params.begin();
    for (; iter != params.end(); ++iter)
    {
        printf("TestModule::SetKey params %s->%s\n", iter->first.c_str(), iter->second.c_str());
    }

    std::map<std::string, std::string>::const_iterator iter_key = params.find("key");
    if (iter_key == params.end())
    {
        result.__set_ec(1000);
        result.__set_msg("");
        return;
    }

    std::map<std::string, std::string>::const_iterator iter_value = params.find("value");
    if (iter_value == params.end())
    {
        result.__set_ec(1000);
        result.__set_msg("");
        return;
    }

    boost::shared_ptr<cloud_ucs::downstream::memcached::SetRequest> req(
            new cloud_ucs::downstream::memcached::SetRequest(
                iter_key->second, iter_value->second));
    req->Execute(mc_server_, cb,
            std::tr1::bind(&TestModule::HandleSetKey, this,
                std::tr1::placeholders::_1,
                std::tr1::placeholders::_2,
                std::tr1::placeholders::_3,
                req));
}

void TestModule::HandleSetKey(cloud_ucs::downstream::ErrCode ec, 
        boost::shared_ptr<cloud_ucs::downstream::memcached::SetResponse> response,
        const cloud_ucs::InvokeCompleteHandler& complete_handler,
        boost::shared_ptr<cloud_ucs::downstream::memcached::SetRequest> request) 
{
    if (ec != cloud_ucs::downstream::OK) 
    {
        cloud_ucs::InvokeResult result;
        result.__set_ec(2);
        result.__set_msg("memcached server connection failed.");
        complete_handler(result);
        return;
    }
    // User logic:
    // ...
    // ...

    std::map<std::string, std::string> my_res;
    // Initialize the response to client:
    // ...
    // ...

    cloud_ucs::InvokeResult result;
    result.__set_results(my_res);
    complete_handler(result);
    return;
}

void TestModule::GetBaidu(const std::map<std::string, std::string>& params, const cloud_ucs::InvokeCompleteHandler& cb)
{
    std::map<std::string, std::string>::const_iterator iter = params.begin();
    for (; iter != params.end(); ++iter)
    {
        printf("TestModule::GetBaidu params %s->%s\n", iter->first.c_str(), iter->second.c_str());
    }

    iter = params.find("uri");
    if (iter == params.end())
    {
        cloud_ucs::InvokeResult result;
        result.__set_ec(1000);
        result.__set_msg("");
        return;
    }

    boost::shared_ptr<cloud_ucs::downstream::http::GetRequest> req(
            new cloud_ucs::downstream::http::GetRequest(iter->second));

    req->Execute(baidu_server_, cb,
            std::tr1::bind(&TestModule::HandleGetBaidu, this,
                std::tr1::placeholders::_1,
                std::tr1::placeholders::_2,
                std::tr1::placeholders::_3,
                req));
}

void TestModule::HandleGetBaidu(cloud_ucs::downstream::ErrCode ec, 
        boost::shared_ptr<cloud_ucs::downstream::http::GetResponse> response,
        const cloud_ucs::InvokeCompleteHandler& complete_handler,
        boost::shared_ptr<cloud_ucs::downstream::http::GetRequest> request) 
{
    if (ec != cloud_ucs::downstream::OK) 
    {
        cloud_ucs::InvokeResult result;
        result.__set_ec(ec);
        result.__set_msg("GetBaidu failed.");
        complete_handler(result);
        return;
    }
    // User logic:
    // ...
    // ...

    std::cout << response << std::endl;
    std::map<std::string, std::string> my_res;
    // Initialize the response to client:
    // ...
    // ...
    my_res["body"] = std::string(response->body()); 

    cloud_ucs::InvokeResult result;
    result.__set_results(my_res);
    complete_handler(result);
    return;
}

EXPORT_MODULE(TestModule)
