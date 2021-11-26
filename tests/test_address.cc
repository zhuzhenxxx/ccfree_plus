#include "ccfree/address.h"
#include "ccfree/log.h"

ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

void test() {
    std::vector<ccfree::Address::ptr> addrs;

    CCFREE_LOG_INFO(g_logger) << "begin";
    bool v = ccfree::Address::Lookup(addrs, "localhost:3080");
    //bool v = ccfree::Address::Lookup(addrs, "www.baidu.com", AF_INET);
    //bool v = ccfree::Address::Lookup(addrs, "www.ccfree.top", AF_INET);
    CCFREE_LOG_INFO(g_logger) << "end";
    if(!v) {
        CCFREE_LOG_ERROR(g_logger) << "lookup fail";
        return;
    }

    for(size_t i = 0; i < addrs.size(); ++i) {
        CCFREE_LOG_INFO(g_logger) << i << " - " << addrs[i]->toString();
    }

    auto addr = ccfree::Address::LookupAny("localhost:4080");
    if(addr) {
        CCFREE_LOG_INFO(g_logger) << *addr;
    } else {
        CCFREE_LOG_ERROR(g_logger) << "error";
    }
}

void test_iface() {
    std::multimap<std::string, std::pair<ccfree::Address::ptr, uint32_t> > results;

    bool v = ccfree::Address::GetInterfaceAddresses(results);
    if(!v) {
        CCFREE_LOG_ERROR(g_logger) << "GetInterfaceAddresses fail";
        return;
    }

    for(auto& i: results) {
        CCFREE_LOG_INFO(g_logger) << i.first << " - " << i.second.first->toString() << " - "
            << i.second.second;
    }
}

void test_ipv4() {
    //auto addr = ccfree::IPAddress::Create("www.ccfree.top");
    auto addr = ccfree::IPAddress::Create("127.0.0.8");
    if(addr) {
        CCFREE_LOG_INFO(g_logger) << addr->toString();
    }
}

int main(int argc, char** argv) {
    //test_ipv4();
    //test_iface();
    test();
    return 0;
}
