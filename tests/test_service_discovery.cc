#include "ccfree/streams/service_discovery.h"
#include "ccfree/iomanager.h"
#include "ccfree/rock/rock_stream.h"
#include "ccfree/log.h"
#include "ccfree/worker.h"

ccfree::ZKServiceDiscovery::ptr zksd(new ccfree::ZKServiceDiscovery("127.0.0.1:21812"));
ccfree::RockSDLoadBalance::ptr rsdlb(new ccfree::RockSDLoadBalance(zksd));

static ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

std::atomic<uint32_t> s_id;
void on_timer() {
    g_logger->setLevel(ccfree::LogLevel::INFO);
    //CCFREE_LOG_INFO(g_logger) << "on_timer";
    ccfree::RockRequest::ptr req(new ccfree::RockRequest);
    req->setSn(++s_id);
    req->setCmd(100);
    req->setBody("hello");

    auto rt = rsdlb->request("ccfree.top", "blog", req, 1000);
    if(!rt->response) {
        if(req->getSn() % 50 == 0) {
            CCFREE_LOG_ERROR(g_logger) << "invalid response: " << rt->toString();
        }
    } else {
        if(req->getSn() % 1000 == 0) {
            CCFREE_LOG_INFO(g_logger) << rt->toString();
        }
    }
}

void run() {
    zksd->setSelfInfo("127.0.0.1:2222");
    zksd->setSelfData("aaaa");

    std::unordered_map<std::string, std::unordered_map<std::string,std::string> > confs;
    confs["ccfree.top"]["blog"] = "fair";
    rsdlb->start(confs);
    //CCFREE_LOG_INFO(g_logger) << "on_timer---";

    ccfree::IOManager::GetThis()->addTimer(1, on_timer, true);
}

int main(int argc, char** argv) {
    ccfree::WorkerMgr::GetInstance()->init({
        {"service_io", {
            {"thread_num", "1"}
        }}
    });
    ccfree::IOManager iom(1);
    iom.addTimer(1000, [](){
            std::cout << rsdlb->statusString() << std::endl;
    }, true);
    iom.schedule(run);
    return 0;
}
