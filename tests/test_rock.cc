#include "ccfree/ccfree.h"
#include "ccfree/rock/rock_stream.h"

static ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

ccfree::RockConnection::ptr conn(new ccfree::RockConnection);
void run() {
    conn->setAutoConnect(true);
    ccfree::Address::ptr addr = ccfree::Address::LookupAny("127.0.0.1:8061");
    if(!conn->connect(addr)) {
        CCFREE_LOG_INFO(g_logger) << "connect " << *addr << " false";
    }
    conn->start();

    ccfree::IOManager::GetThis()->addTimer(1000, [](){
        ccfree::RockRequest::ptr req(new ccfree::RockRequest);
        static uint32_t s_sn = 0;
        req->setSn(++s_sn);
        req->setCmd(100);
        req->setBody("hello world sn=" + std::to_string(s_sn));

        auto rsp = conn->request(req, 300);
        if(rsp->response) {
            CCFREE_LOG_INFO(g_logger) << rsp->response->toString();
        } else {
            CCFREE_LOG_INFO(g_logger) << "error result=" << rsp->result;
        }
    }, true);
}

int main(int argc, char** argv) {
    ccfree::IOManager iom(1);
    iom.schedule(run);
    return 0;
}
