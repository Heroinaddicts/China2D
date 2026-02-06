#ifndef __iTaskManager_h__
#define __iTaskManager_h__

#include "IEngineComponent.h"
#include "ITaskManagerApi.h"

namespace China2D {
    class ITaskManager : public IEngineComponent, public Api::ITaskManagerApi {
    public:
        virtual ~ITaskManager() {}
    };
}

#endif //__iTaskManager_h__
