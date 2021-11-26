#include "ccfree/tcp_server.h"
#include "ccfree/iomanager.h"
#include "ccfree/log.h"

ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

void run() {
    auto addr = ccfree::Address::LookupAny("0.0.0.0:8033");
    //auto addr2 = ccfree::UnixAddress::ptr(new ccfree::UnixAddress("/tmp/unix_addr"));
    std::vector<ccfree::Address::ptr> addrs;
    addrs.push_back(addr);
    //addrs.push_back(addr2);

    ccfree::TcpServer::ptr tcp_server(new ccfree::TcpServer);
    std::vector<ccfree::Address::ptr> fails;
    while(!tcp_server->bind(addrs, fails)) {
        sleep(2);
    }
    tcp_server->start();
    
}
int main(int argc, char** argv) {
    ccfree::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
