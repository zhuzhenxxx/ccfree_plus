#include "ccfree/http/ws_server.h"
#include "ccfree/log.h"

static ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

void run() {
    ccfree::http::WSServer::ptr server(new ccfree::http::WSServer);
    ccfree::Address::ptr addr = ccfree::Address::LookupAnyIPAddress("0.0.0.0:8020");
    if(!addr) {
        CCFREE_LOG_ERROR(g_logger) << "get address error";
        return;
    }
    auto fun = [](ccfree::http::HttpRequest::ptr header
                  ,ccfree::http::WSFrameMessage::ptr msg
                  ,ccfree::http::WSSession::ptr session) {
        session->sendMessage(msg);
        return 0;
    };

    server->getWSServletDispatch()->addServlet("/ccfree", fun);
    while(!server->bind(addr)) {
        CCFREE_LOG_ERROR(g_logger) << "bind " << *addr << " fail";
        sleep(1);
    }
    server->start();
}

int main(int argc, char** argv) {
    ccfree::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
