#include "ccfree/application.h"

int main(int argc, char** argv) {
    ccfree::Application app;
    if(app.init(argc, argv)) {
        return app.run();
    }
    return 0;
}
