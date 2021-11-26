#ifndef __CCFREE_NS_NAME_SERVER_MODULE_H__
#define __CCFREE_NS_NAME_SERVER_MODULE_H__

#include "ccfree/module.h"
#include "ns_protocol.h"

namespace ccfree {
namespace ns {

class NameServerModule;
class NSClientInfo {
friend class NameServerModule;
public:
    typedef std::shared_ptr<NSClientInfo> ptr;
private:
    NSNode::ptr m_node;
    std::map<std::string, std::set<uint32_t> > m_domain2cmds;
};

class NameServerModule : public RockModule {
public:
    typedef std::shared_ptr<NameServerModule> ptr;
    NameServerModule();

    virtual bool handleRockRequest(ccfree::RockRequest::ptr request
                        ,ccfree::RockResponse::ptr response
                        ,ccfree::RockStream::ptr stream) override;
    virtual bool handleRockNotify(ccfree::RockNotify::ptr notify
                        ,ccfree::RockStream::ptr stream) override;
    virtual bool onConnect(ccfree::Stream::ptr stream) override;
    virtual bool onDisconnect(ccfree::Stream::ptr stream) override;
    virtual std::string statusString() override;
private:
    bool handleRegister(ccfree::RockRequest::ptr request
                        ,ccfree::RockResponse::ptr response
                        ,ccfree::RockStream::ptr stream);
    bool handleQuery(ccfree::RockRequest::ptr request
                        ,ccfree::RockResponse::ptr response
                        ,ccfree::RockStream::ptr stream);
    bool handleTick(ccfree::RockRequest::ptr request
                        ,ccfree::RockResponse::ptr response
                        ,ccfree::RockStream::ptr stream);

private:
    NSClientInfo::ptr get(ccfree::RockStream::ptr rs);
    void set(ccfree::RockStream::ptr rs, NSClientInfo::ptr info);

    void setQueryDomain(ccfree::RockStream::ptr rs, const std::set<std::string>& ds);

    void doNotify(std::set<std::string>& domains, std::shared_ptr<NotifyMessage> nty);

    std::set<ccfree::RockStream::ptr> getStreams(const std::string& domain);
private:
    NSDomainSet::ptr m_domains;

    ccfree::RWMutex m_mutex;
    std::map<ccfree::RockStream::ptr, NSClientInfo::ptr> m_sessions;

    /// sessoin 关注的域名
    std::map<ccfree::RockStream::ptr, std::set<std::string> > m_queryDomains;
    /// 域名对应关注的session
    std::map<std::string, std::set<ccfree::RockStream::ptr> > m_domainToSessions;
};

}
}

#endif
