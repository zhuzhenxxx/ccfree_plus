#include "rock_server.h"
#include "ccfree/log.h"
#include "ccfree/module.h"

namespace ccfree {

static ccfree::Logger::ptr g_logger = CCFREE_LOG_NAME("system");

RockServer::RockServer(const std::string& type
                       ,ccfree::IOManager* worker
                       ,ccfree::IOManager* io_worker
                       ,ccfree::IOManager* accept_worker)
    :TcpServer(worker, io_worker, accept_worker) {
    m_type = type;
}

void RockServer::handleClient(Socket::ptr client) {
    CCFREE_LOG_DEBUG(g_logger) << "handleClient " << *client;
    ccfree::RockSession::ptr session(new ccfree::RockSession(client));
    session->setWorker(m_worker);
    ModuleMgr::GetInstance()->foreach(Module::ROCK,
            [session](Module::ptr m) {
        m->onConnect(session);
    });
    session->setDisconnectCb(
        [](AsyncSocketStream::ptr stream) {
             ModuleMgr::GetInstance()->foreach(Module::ROCK,
                    [stream](Module::ptr m) {
                m->onDisconnect(stream);
            });
        }
    );
    session->setRequestHandler(
        [](ccfree::RockRequest::ptr req
           ,ccfree::RockResponse::ptr rsp
           ,ccfree::RockStream::ptr conn)->bool {
            //CCFREE_LOG_INFO(g_logger) << "handleReq " << req->toString()
            //                         << " body=" << req->getBody();
            bool rt = false;
            ModuleMgr::GetInstance()->foreach(Module::ROCK,
                    [&rt, req, rsp, conn](Module::ptr m) {
                if(rt) {
                    return;
                }
                rt = m->handleRequest(req, rsp, conn);
            });
            return rt;
        }
    ); 
    session->setNotifyHandler(
        [](ccfree::RockNotify::ptr nty
           ,ccfree::RockStream::ptr conn)->bool {
            CCFREE_LOG_INFO(g_logger) << "handleNty " << nty->toString()
                                     << " body=" << nty->getBody();
            bool rt = false;
            ModuleMgr::GetInstance()->foreach(Module::ROCK,
                    [&rt, nty, conn](Module::ptr m) {
                if(rt) {
                    return;
                }
                rt = m->handleNotify(nty, conn);
            });
            return rt;
        }
    );
    session->start();
}

}
