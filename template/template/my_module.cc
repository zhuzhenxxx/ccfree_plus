#include "my_module.h"
#include "ccfree/config.h"
#include "ccfree/log.h"

namespace name_space {

static ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

MyModule::MyModule()
    :ccfree::Module("project_name", "1.0", "") {
}

bool MyModule::onLoad() {
    CCFREE_LOG_INFO(g_logger) << "onLoad";
    return true;
}

bool MyModule::onUnload() {
    CCFREE_LOG_INFO(g_logger) << "onUnload";
    return true;
}

bool MyModule::onServerReady() {
    CCFREE_LOG_INFO(g_logger) << "onServerReady";
    return true;
}

bool MyModule::onServerUp() {
    CCFREE_LOG_INFO(g_logger) << "onServerUp";
    return true;
}

}

extern "C" {

ccfree::Module* CreateModule() {
    ccfree::Module* module = new name_space::MyModule;
    CCFREE_LOG_INFO(name_space::g_logger) << "CreateModule " << module;
    return module;
}

void DestoryModule(ccfree::Module* module) {
    CCFREE_LOG_INFO(name_space::g_logger) << "CreateModule " << module;
    delete module;
}

}
