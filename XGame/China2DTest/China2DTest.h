#ifndef __China2DTest_h__
#define __China2DTest_h__

#include "Header.h"

class China2DTest : public IChina2DTest {
public:
    virtual ~China2DTest() {}
private:
    // Í¨¹ý IChina2DTest ¼Ì³Ð
    bool Initialize(Api::IEngine* const engine) override;
    bool Launch(Api::IEngine* const engine) override;
    bool Destroy(Api::IEngine* const engine) override;

};

#endif //__China2DTest_h__
