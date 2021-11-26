#include <iostream>
#include "ccfree/log.h"
#include "ccfree/util.h"

int main(int argc, char** argv) {
    ccfree::Logger::ptr logger(new ccfree::Logger);
    logger->addAppender(ccfree::LogAppender::ptr(new ccfree::StdoutLogAppender));

    ccfree::FileLogAppender::ptr file_appender(new ccfree::FileLogAppender("./log.txt"));
    ccfree::LogFormatter::ptr fmt(new ccfree::LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);
    file_appender->setLevel(ccfree::LogLevel::ERROR);

    logger->addAppender(file_appender);

    //ccfree::LogEvent::ptr event(new ccfree::LogEvent(__FILE__, __LINE__, 0, ccfree::GetThreadId(), ccfree::GetFiberId(), time(0)));
    //event->getSS() << "hello ccfree log";
    //logger->log(ccfree::LogLevel::DEBUG, event);
    std::cout << "hello ccfree log" << std::endl;

    CCFREE_LOG_INFO(logger) << "test macro";
    CCFREE_LOG_ERROR(logger) << "test macro error";

    CCFREE_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");

    auto l = ccfree::LoggerMgr::GetInstance()->getLogger("xx");
    CCFREE_LOG_INFO(l) << "xxx";
    return 0;
}
