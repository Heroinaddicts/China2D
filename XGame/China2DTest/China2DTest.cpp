#include "China2DTest.h"

Api::IEngine* g_Engine = nullptr;
static China2DTest* s_Self = nullptr;

bool China2DTest::Initialize(Api::IEngine* const engine) {
    g_Engine = engine;
    s_Self = this;
    return true;
}

bool China2DTest::Launch(Api::IEngine* const engine) {
    return true;
}

bool China2DTest::Destroy(Api::IEngine* const engine) {
    return true;
}
