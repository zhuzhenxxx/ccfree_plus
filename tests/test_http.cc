#include "ccfree/http/http.h"
#include "ccfree/log.h"

void test_request() {
    ccfree::http::HttpRequest::ptr req(new ccfree::http::HttpRequest);
    req->setHeader("host" , "www.ccfree.top");
    req->setBody("hello ccfree");
    req->dump(std::cout) << std::endl;
}

void test_response() {
    ccfree::http::HttpResponse::ptr rsp(new ccfree::http::HttpResponse);
    rsp->setHeader("X-X", "ccfree");
    rsp->setBody("hello ccfree");
    rsp->setStatus((ccfree::http::HttpStatus)400);
    rsp->setClose(false);

    rsp->dump(std::cout) << std::endl;
}

int main(int argc, char** argv) {
    test_request();
    test_response();
    return 0;
}
