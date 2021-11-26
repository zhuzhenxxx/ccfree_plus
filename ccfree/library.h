#ifndef __CCFREE_LIBRARY_H__
#define __CCFREE_LIBRARY_H__

#include <memory>
#include "module.h"

namespace ccfree {

class Library {
public:
    static Module::ptr GetModule(const std::string& path);
};

}

#endif
