#include "ccfree/ccfree.h"

static ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

void test_fiber() {
    static int s_count = 5;
    CCFREE_LOG_INFO(g_logger) << "test in fiber s_count=" << s_count;

    sleep(1);
    if(--s_count >= 0) {
        ccfree::Scheduler::GetThis()->schedule(&test_fiber, ccfree::GetThreadId());
    }
}

int main(int argc, char** argv) {
    CCFREE_LOG_INFO(g_logger) << "main";
    ccfree::Scheduler sc(3, false, "test");
    sc.start();
    sleep(2);
    CCFREE_LOG_INFO(g_logger) << "schedule";
    sc.schedule(&test_fiber);
    sc.stop();
    CCFREE_LOG_INFO(g_logger) << "over";
    return 0;
}
