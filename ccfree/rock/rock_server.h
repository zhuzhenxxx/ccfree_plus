#ifndef __CCFREE_ROCK_SERVER_H__
#define __CCFREE_ROCK_SERVER_H__

#include "ccfree/rock/rock_stream.h"
#include "ccfree/tcp_server.h"

namespace ccfree {

class RockServer : public TcpServer {
public:
    typedef std::shared_ptr<RockServer> ptr;
    RockServer(const std::string& type = "rock"
               ,ccfree::IOManager* worker = ccfree::IOManager::GetThis()
               ,ccfree::IOManager* io_worker = ccfree::IOManager::GetThis()
               ,ccfree::IOManager* accept_worker = ccfree::IOManager::GetThis());

protected:
    virtual void handleClient(Socket::ptr client) override;
};

}

#endif
