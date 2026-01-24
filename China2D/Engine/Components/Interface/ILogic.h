#ifndef __ILogic_h__
#define __ILogic_h__

#include "IEngineComponent.h"

namespace China2D {
    class ILogic : public IEngineComponent {
    public:
        virtual ~ILogic() {}

        virtual Api::IModule* FindModule(const std::string& name) = 0;
    };
}

#endif //__ILogic_h__
