#include "ccfree/module.h"
#include "ccfree/singleton.h"
#include <iostream>
#include "ccfree/log.h"
#include "ccfree/db/redis.h"

static ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

class A {
public:
    A() {
        std::cout << "A::A " << this << std::endl;
    }

    ~A() {
        std::cout << "A::~A " << this << std::endl;
    }

};

class MyModule : public ccfree::RockModule {
public:
    MyModule()
        :RockModule("hello", "1.0", "") {
        //ccfree::Singleton<A>::GetInstance();
    }

    bool onLoad() override {
        ccfree::Singleton<A>::GetInstance();
        std::cout << "-----------onLoad------------" << std::endl;
        return true;
    }

    bool onUnload() override {
        ccfree::Singleton<A>::GetInstance();
        std::cout << "-----------onUnload------------" << std::endl;
        return true;
    }

    bool onServerReady() {
        registerService("rock", "ccfree.top", "blog");
        auto rpy = ccfree::RedisUtil::Cmd("local", "get abc");
        if(!rpy) {
            CCFREE_LOG_ERROR(g_logger) << "redis cmd get abc error";
        } else {
            CCFREE_LOG_ERROR(g_logger) << "redis get abc: "
                << (rpy->str ? rpy->str : "(null)");
        }
        return true;
    }

    bool handleRockRequest(ccfree::RockRequest::ptr request
                        ,ccfree::RockResponse::ptr response
                        ,ccfree::RockStream::ptr stream) {
        //CCFREE_LOG_INFO(g_logger) << "handleRockRequest " << request->toString();
        //sleep(1);
        response->setResult(0);
        response->setResultStr("ok");
        response->setBody("echo: " + request->getBody());

        usleep(100 * 1000);
        auto addr = stream->getLocalAddressString();
        if(addr.find("8061") != std::string::npos) {
            if(rand() % 100 < 50) {
                usleep(10 * 1000);
            } else if(rand() % 100 < 10) {
                response->setResult(-1000);
            }
        } else {
            //if(rand() % 100 < 25) {
            //    usleep(10 * 1000);
            //} else if(rand() % 100 < 10) {
            //    response->setResult(-1000);
            //}
        }
        return true;
        //return rand() % 100 < 90;
    }

    bool handleRockNotify(ccfree::RockNotify::ptr notify 
                        ,ccfree::RockStream::ptr stream) {
        CCFREE_LOG_INFO(g_logger) << "handleRockNotify " << notify->toString();
        return true;
    }

};

extern "C" {

ccfree::Module* CreateModule() {
    ccfree::Singleton<A>::GetInstance();
    std::cout << "=============CreateModule=================" << std::endl;
    return new MyModule;
}

void DestoryModule(ccfree::Module* ptr) {
    std::cout << "=============DestoryModule=================" << std::endl;
    delete ptr;
}

}
