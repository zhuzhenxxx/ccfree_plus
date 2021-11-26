#include "ccfree/ccfree.h"
#include "ccfree/ds/array.h"

static ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

struct PidVid {
    PidVid(uint32_t p = 0, uint32_t v = 0)
        :pid(p), vid(v) {}
    uint32_t pid;
    uint32_t vid;

    bool operator<(const PidVid& o) const {
        return memcmp(this, &o, sizeof(o)) < 0;
    }
};

void gen() {
    ccfree::ds::Array<int> tmp;
    std::vector<int> vs;
    for(int i = 0; i < 10000; ++i) {
        int v = rand();
        tmp.insert(v);
        vs.push_back(v);
        CCFREE_ASSERT(tmp.isSorted());
    }

    std::ofstream ofs("./array.data");
    tmp.writeTo(ofs);

    for(auto& i : vs) {
        auto idx = tmp.exists(i);
        CCFREE_ASSERT(idx >= 0);
        tmp.erase(idx);
        CCFREE_ASSERT(tmp.isSorted());
    }
    CCFREE_ASSERT(tmp.size() == 0);
    
}

void test() {
    for(int i = 0; i < 10000; ++i) {
        CCFREE_LOG_INFO(g_logger) << "i=" << i;
        std::ifstream ifs("./array.data");
        ccfree::ds::Array<int> tmp;
        if(!tmp.readFrom(ifs)) {
            CCFREE_LOG_INFO(g_logger) << "error";
        }
        CCFREE_ASSERT(tmp.isSorted());
        if(i % 100 == 0) {
            CCFREE_LOG_INFO(g_logger) << "over..." << (i + 1);
        }
    }
}

int main(int argc, char** argv) {
    gen();
    test();
    return 0;
}
