#ifndef __CCFREE_HTTP_SERVLETS_STATUS_SERVLET_H__
#define __CCFREE_HTTP_SERVLETS_STATUS_SERVLET_H__

#include "ccfree/http/servlet.h"

namespace ccfree {
namespace http {

class StatusServlet : public Servlet {
public:
    StatusServlet();
    virtual int32_t handle(ccfree::http::HttpRequest::ptr request
                   , ccfree::http::HttpResponse::ptr response
                   , ccfree::http::HttpSession::ptr session) override;
};

}
}

#endif
