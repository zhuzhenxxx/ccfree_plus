#include "ccfree/env.h"
#include <unistd.h>
#include <iostream>
#include <fstream>

struct A {
    A() {
        std::ifstream ifs("/proc/" + std::to_string(getpid()) + "/cmdline", std::ios::binary);
        std::string content;
        content.resize(4096);

        ifs.read(&content[0], content.size());
        content.resize(ifs.gcount());

        for(size_t i = 0; i < content.size(); ++i) {
            std::cout << i << " - " << content[i] << " - " << (int)content[i] << std::endl;
        }
    }
};

A a;

int main(int argc, char** argv) {
    std::cout << "argc=" << argc << std::endl;
    ccfree::EnvMgr::GetInstance()->addHelp("s", "start with the terminal");
    ccfree::EnvMgr::GetInstance()->addHelp("d", "run as daemon");
    ccfree::EnvMgr::GetInstance()->addHelp("p", "print help");
    if(!ccfree::EnvMgr::GetInstance()->init(argc, argv)) {
        ccfree::EnvMgr::GetInstance()->printHelp();
        return 0;
    }

    std::cout << "exe=" << ccfree::EnvMgr::GetInstance()->getExe() << std::endl;
    std::cout << "cwd=" << ccfree::EnvMgr::GetInstance()->getCwd() << std::endl;

    std::cout << "path=" << ccfree::EnvMgr::GetInstance()->getEnv("PATH", "xxx") << std::endl;
    std::cout << "test=" << ccfree::EnvMgr::GetInstance()->getEnv("TEST", "") << std::endl;
    std::cout << "set env " << ccfree::EnvMgr::GetInstance()->setEnv("TEST", "yy") << std::endl;
    std::cout << "test=" << ccfree::EnvMgr::GetInstance()->getEnv("TEST", "") << std::endl;
    if(ccfree::EnvMgr::GetInstance()->has("p")) {
        ccfree::EnvMgr::GetInstance()->printHelp();
    }
    return 0;
}
