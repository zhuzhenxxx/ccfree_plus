#include "ccfree/socket.h"
#include "ccfree/log.h"
#include "ccfree/iomanager.h"

static ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

void run() {
    ccfree::IPAddress::ptr addr = ccfree::Address::LookupAnyIPAddress("0.0.0.0:8050");
    ccfree::Socket::ptr sock = ccfree::Socket::CreateUDP(addr);
    if(sock->bind(addr)) {
        CCFREE_LOG_INFO(g_logger) << "udp bind : " << *addr;
    } else {
        CCFREE_LOG_ERROR(g_logger) << "udp bind : " << *addr << " fail";
        return;
    }
    while(true) {
        char buff[1024];
        ccfree::Address::ptr from(new ccfree::IPv4Address);
        int len = sock->recvFrom(buff, 1024, from);
        if(len > 0) {
            buff[len] = '\0';
            CCFREE_LOG_INFO(g_logger) << "recv: " << buff << " from: " << *from;
            len = sock->sendTo(buff, len, from);
            if(len < 0) {
                CCFREE_LOG_INFO(g_logger) << "send: " << buff << " to: " << *from
                    << " error=" << len;
            }
        }
    }
}

int main(int argc, char** argv) {
    ccfree::IOManager iom(1);
    iom.schedule(run);
    return 0;
}
