#ifndef __CCFREE_HTTP_WS_SERVER_H__
#define __CCFREE_HTTP_WS_SERVER_H__

#include "ccfree/tcp_server.h"
#include "ws_session.h"
#include "ws_servlet.h"

namespace ccfree {
namespace http {

class WSServer : public TcpServer {
public:
    typedef std::shared_ptr<WSServer> ptr;

    WSServer(ccfree::IOManager* worker = ccfree::IOManager::GetThis()
             , ccfree::IOManager* io_worker = ccfree::IOManager::GetThis()
             , ccfree::IOManager* accept_worker = ccfree::IOManager::GetThis());

    WSServletDispatch::ptr getWSServletDispatch() const { return m_dispatch;}
    void setWSServletDispatch(WSServletDispatch::ptr v) { m_dispatch = v;}
protected:
    virtual void handleClient(Socket::ptr client) override;
protected:
    WSServletDispatch::ptr m_dispatch;
};

}
}

#endif
