#include "ccfree/daemon.h"
#include "ccfree/iomanager.h"
#include "ccfree/log.h"

static ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

ccfree::Timer::ptr timer;
int server_main(int argc, char** argv) {
    CCFREE_LOG_INFO(g_logger) << ccfree::ProcessInfoMgr::GetInstance()->toString();
    ccfree::IOManager iom(1);
    timer = iom.addTimer(1000, [](){
            CCFREE_LOG_INFO(g_logger) << "onTimer";
            static int count = 0;
            if(++count > 10) {
                exit(1);
            }
    }, true);
    return 0;
}

int main(int argc, char** argv) {
    return ccfree::start_daemon(argc, argv, server_main, argc != 1);
}
