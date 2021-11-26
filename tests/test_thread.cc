#include "ccfree/ccfree.h"
#include <unistd.h>

ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

int count = 0;
//ccfree::RWMutex s_mutex;
ccfree::Mutex s_mutex;

void fun1() {
    CCFREE_LOG_INFO(g_logger) << "name: " << ccfree::Thread::GetName()
                             << " this.name: " << ccfree::Thread::GetThis()->getName()
                             << " id: " << ccfree::GetThreadId()
                             << " this.id: " << ccfree::Thread::GetThis()->getId();

    for(int i = 0; i < 100000; ++i) {
        //ccfree::RWMutex::WriteLock lock(s_mutex);
        ccfree::Mutex::Lock lock(s_mutex);
        ++count;
    }
}

void fun2() {
    while(true) {
        CCFREE_LOG_INFO(g_logger) << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    }
}

void fun3() {
    while(true) {
        CCFREE_LOG_INFO(g_logger) << "========================================";
    }
}

int main(int argc, char** argv) {
    CCFREE_LOG_INFO(g_logger) << "thread test begin";
    YAML::Node root = YAML::LoadFile("/home/ccfree/test/ccfree/bin/conf/log2.yml");
    ccfree::Config::LoadFromYaml(root);

    std::vector<ccfree::Thread::ptr> thrs;
    for(int i = 0; i < 1; ++i) {
        ccfree::Thread::ptr thr(new ccfree::Thread(&fun2, "name_" + std::to_string(i * 2)));
        //ccfree::Thread::ptr thr2(new ccfree::Thread(&fun3, "name_" + std::to_string(i * 2 + 1)));
        thrs.push_back(thr);
        //thrs.push_back(thr2);
    }

    for(size_t i = 0; i < thrs.size(); ++i) {
        thrs[i]->join();
    }
    CCFREE_LOG_INFO(g_logger) << "thread test end";
    CCFREE_LOG_INFO(g_logger) << "count=" << count;

    return 0;
}
