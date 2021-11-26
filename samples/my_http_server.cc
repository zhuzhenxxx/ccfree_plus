#include "ccfree/http/http_server.h"
#include "ccfree/log.h"

ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();
ccfree::IOManager::ptr worker;
void run() {
    g_logger->setLevel(ccfree::LogLevel::INFO);
    ccfree::Address::ptr addr = ccfree::Address::LookupAnyIPAddress("0.0.0.0:8020");
    if(!addr) {
        CCFREE_LOG_ERROR(g_logger) << "get address error";
        return;
    }

    ccfree::http::HttpServer::ptr http_server(new ccfree::http::HttpServer(true, worker.get()));
    //ccfree::http::HttpServer::ptr http_server(new ccfree::http::HttpServer(true));
    bool ssl = false;
    while(!http_server->bind(addr, ssl)) {
        CCFREE_LOG_ERROR(g_logger) << "bind " << *addr << " fail";
        sleep(1);
    }

    if(ssl) {
        //http_server->loadCertificates("/home/apps/soft/ccfree/keys/server.crt", "/home/apps/soft/ccfree/keys/server.key");
    }

    http_server->start();
}

int main(int argc, char** argv) {
    ccfree::IOManager iom(1);
    worker.reset(new ccfree::IOManager(4, false));
    iom.schedule(run);
    return 0;
}
