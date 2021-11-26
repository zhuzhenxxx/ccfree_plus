#include "ccfree/http/http_server.h"
#include "ccfree/log.h"

static ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

#define XX(...) #__VA_ARGS__


ccfree::IOManager::ptr worker;
void run() {
    g_logger->setLevel(ccfree::LogLevel::INFO);
    //ccfree::http::HttpServer::ptr server(new ccfree::http::HttpServer(true, worker.get(), ccfree::IOManager::GetThis()));
    ccfree::http::HttpServer::ptr server(new ccfree::http::HttpServer(true));
    ccfree::Address::ptr addr = ccfree::Address::LookupAnyIPAddress("0.0.0.0:8020");
    while(!server->bind(addr)) {
        sleep(2);
    }
    auto sd = server->getServletDispatch();
    sd->addServlet("/ccfree/xx", [](ccfree::http::HttpRequest::ptr req
                ,ccfree::http::HttpResponse::ptr rsp
                ,ccfree::http::HttpSession::ptr session) {
            rsp->setBody(req->toString());
            return 0;
    });

    sd->addGlobServlet("/ccfree/*", [](ccfree::http::HttpRequest::ptr req
                ,ccfree::http::HttpResponse::ptr rsp
                ,ccfree::http::HttpSession::ptr session) {
            rsp->setBody("Glob:\r\n" + req->toString());
            return 0;
    });

    sd->addGlobServlet("/ccfreex/*", [](ccfree::http::HttpRequest::ptr req
                ,ccfree::http::HttpResponse::ptr rsp
                ,ccfree::http::HttpSession::ptr session) {
            rsp->setBody(XX(<html>
<head><title>404 Not Found</title></head>
<body>
<center><h1>404 Not Found</h1></center>
<hr><center>nginx/1.16.0</center>
</body>
</html>
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
));
            return 0;
    });

    server->start();
}

int main(int argc, char** argv) {
    ccfree::IOManager iom(1, true, "main");
    worker.reset(new ccfree::IOManager(3, false, "worker"));
    iom.schedule(run);
    return 0;
}
