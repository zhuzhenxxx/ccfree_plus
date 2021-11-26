#ifndef __CCFREE_HTTP_SERVLETS_CONFIG_SERVLET_H__
#define __CCFREE_HTTP_SERVLETS_CONFIG_SERVLET_H__

#include "ccfree/http/servlet.h"

namespace ccfree {
namespace http {

class ConfigServlet : public Servlet {
public:
    ConfigServlet();
    virtual int32_t handle(ccfree::http::HttpRequest::ptr request
                   , ccfree::http::HttpResponse::ptr response
                   , ccfree::http::HttpSession::ptr session) override;
};

}
}

#endif
