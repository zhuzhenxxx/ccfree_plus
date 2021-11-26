#include "ccfree/ccfree.h"

ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

void run_in_fiber() {
    CCFREE_LOG_INFO(g_logger) << "run_in_fiber begin";
    ccfree::Fiber::YieldToHold();
    CCFREE_LOG_INFO(g_logger) << "run_in_fiber end";
    ccfree::Fiber::YieldToHold();
}

void test_fiber() {
    CCFREE_LOG_INFO(g_logger) << "main begin -1";
    {
        ccfree::Fiber::GetThis();
        CCFREE_LOG_INFO(g_logger) << "main begin";
        ccfree::Fiber::ptr fiber(new ccfree::Fiber(run_in_fiber));
        fiber->swapIn();
        CCFREE_LOG_INFO(g_logger) << "main after swapIn";
        fiber->swapIn();
        CCFREE_LOG_INFO(g_logger) << "main after end";
        fiber->swapIn();
    }
    CCFREE_LOG_INFO(g_logger) << "main after end2";
}

int main(int argc, char** argv) {
    ccfree::Thread::SetName("main");

    std::vector<ccfree::Thread::ptr> thrs;
    for(int i = 0; i < 3; ++i) {
        thrs.push_back(ccfree::Thread::ptr(
                    new ccfree::Thread(&test_fiber, "name_" + std::to_string(i))));
    }
    for(auto i : thrs) {
        i->join();
    }
    return 0;
}
