#include "ccfree/uri.h"
#include <iostream>

int main(int argc, char** argv) {
    //ccfree::Uri::ptr uri = ccfree::Uri::Create("http://www.ccfree.top/test/uri?id=100&name=ccfree#frg");
    //ccfree::Uri::ptr uri = ccfree::Uri::Create("http://admin@www.ccfree.top/test/中文/uri?id=100&name=ccfree&vv=中文#frg中文");
    ccfree::Uri::ptr uri = ccfree::Uri::Create("http://admin@www.ccfree.top");
    //ccfree::Uri::ptr uri = ccfree::Uri::Create("http://www.ccfree.top/test/uri");
    std::cout << uri->toString() << std::endl;
    auto addr = uri->createAddress();
    std::cout << *addr << std::endl;
    return 0;
}
