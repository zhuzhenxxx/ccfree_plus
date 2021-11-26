#include "ccfree/ccfree.h"
#include "ccfree/ns/ns_protocol.h"
#include "ccfree/ns/ns_client.h"

static ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

int type = 0;

void run() {
    g_logger->setLevel(ccfree::LogLevel::INFO);
    auto addr = ccfree::IPAddress::Create("127.0.0.1", 8072);
    //if(!conn->connect(addr)) {
    //    CCFREE_LOG_ERROR(g_logger) << "connect to: " << *addr << " fail";
    //    return;
    //}
    if(type == 0) {
        for(int i = 0; i < 5000; ++i) {
            ccfree::RockConnection::ptr conn(new ccfree::RockConnection);
            conn->connect(addr);
            ccfree::IOManager::GetThis()->addTimer(3000, [conn, i](){
                    ccfree::RockRequest::ptr req(new ccfree::RockRequest);
                    req->setCmd((int)ccfree::ns::NSCommand::REGISTER);
                    auto rinfo = std::make_shared<ccfree::ns::RegisterRequest>();
                    auto info = rinfo->add_infos();
                    info->set_domain(std::to_string(rand() % 2) + "domain.com");
                    info->add_cmds(rand() % 2 + 100);
                    info->add_cmds(rand() % 2 + 200);
                    info->mutable_node()->set_ip("127.0.0.1");
                    info->mutable_node()->set_port(1000 + i);
                    info->mutable_node()->set_weight(100);
                    req->setAsPB(*rinfo);

                    auto rt = conn->request(req, 100);
                    CCFREE_LOG_INFO(g_logger) << "[result="
                        << rt->result << " response="
                        << (rt->response ? rt->response->toString() : "null")
                        << "]";
            }, true);
            conn->start();
        }
    } else {
        for(int i = 0; i < 1000; ++i) {
            ccfree::ns::NSClient::ptr nsclient(new ccfree::ns::NSClient);
            nsclient->init();
            nsclient->addQueryDomain(std::to_string(i % 2) + "domain.com");
            nsclient->connect(addr);
            nsclient->start();
            CCFREE_LOG_INFO(g_logger) << "NSClient start: i=" << i;

            if(i == 0) {
                //ccfree::IOManager::GetThis()->addTimer(1000, [nsclient](){
                //    auto domains = nsclient->getDomains();
                //    domains->dump(std::cout, "    ");
                //}, true);
            }
        }

        //conn->setConnectCb([](ccfree::AsyncSocketStream::ptr ss) {
        //    auto conn = std::dynamic_pointer_cast<ccfree::RockConnection>(ss);
        //    ccfree::RockRequest::ptr req(new ccfree::RockRequest);
        //    req->setCmd((int)ccfree::ns::NSCommand::QUERY);
        //    auto rinfo = std::make_shared<ccfree::ns::QueryRequest>();
        //    rinfo->add_domains("0domain.com");
        //    req->setAsPB(*rinfo);
        //    auto rt = conn->request(req, 1000);
        //    CCFREE_LOG_INFO(g_logger) << "[result="
        //        << rt->result << " response="
        //        << (rt->response ? rt->response->toString() : "null")
        //        << "]";
        //    return true;
        //});

        //conn->setNotifyHandler([](ccfree::RockNotify::ptr nty,ccfree::RockStream::ptr stream){
        //        auto nm = nty->getAsPB<ccfree::ns::NotifyMessage>();
        //        if(!nm) {
        //            CCFREE_LOG_ERROR(g_logger) << "invalid notify message";
        //            return true;
        //        }
        //        CCFREE_LOG_INFO(g_logger) << ccfree::PBToJsonString(*nm);
        //        return true;
        //});
    }
}

int main(int argc, char** argv) {
    if(argc > 1) {
        type = 1;
    }
    ccfree::IOManager iom(5);
    iom.schedule(run);
    return 0;
}
