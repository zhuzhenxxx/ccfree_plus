#include "ccfree/email/email.h"
#include "ccfree/email/smtp.h"

void test() {
    ccfree::EMail::ptr email = ccfree::EMail::Create(
            "user@163.com", "passwd",
            "hello world", "<B>hi xxx</B>hell world", {"564628276@qq.com"});
    ccfree::EMailEntity::ptr entity = ccfree::EMailEntity::CreateAttach("ccfree/ccfree.h");
    if(entity) {
        email->addEntity(entity);
    }

    entity = ccfree::EMailEntity::CreateAttach("ccfree/address.cc");
    if(entity) {
        email->addEntity(entity);
    }

    auto client = ccfree::SmtpClient::Create("smtp.163.com", 465, true);
    if(!client) {
        std::cout << "connect smtp.163.com:25 fail" << std::endl;
        return;
    }

    auto result = client->send(email, true);
    std::cout << "result=" << result->result << " msg=" << result->msg << std::endl;
    std::cout << client->getDebugInfo() << std::endl;
    //result = client->send(email, true);
    //std::cout << "result=" << result->result << " msg=" << result->msg << std::endl;
    //std::cout << client->getDebugInfo() << std::endl;
}

int main(int argc, char** argv) {
    ccfree::IOManager iom(1);
    iom.schedule(test);
    iom.stop();
    return 0;
}
