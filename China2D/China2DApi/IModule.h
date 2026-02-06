#ifndef __iModule_h__
#define __iModule_h__

#include "MultiSys.h"

namespace China2D {
    namespace Api {
        class IEngine;
        class IModule {
        public:
            virtual ~IModule() {}
            IModule() : _Name(""), _Next(nullptr) {}

            virtual bool Initialize(IEngine* const engine) = 0;
            virtual bool Launch(IEngine* const engine) = 0;
            virtual bool Destroy(IEngine* const engine) = 0;

            virtual void Update(IEngine* const engine) {}
            virtual void FixedUpdate(IEngine* const engine) {}
            virtual void LateUpdate(IEngine* const engine) {}

            const char* const _Name;
            IModule* const _Next;
        };
    }
}

#define GET_MODULES_FUNC_NAME "GetModules"

#ifdef WIN32
#define DLL_INSTANCE \
    static China2D::Api::IModule * static_modules = nullptr; \
    extern "C" __declspec(dllexport) China2D::Api::IModule * __cdecl GetModules() {\
        return static_modules; \
    }
#else
#define DLL_INSTANCE \
    static China2D::Api::IModule * static_modules = nullptr; \
    extern "C" China2D::Api::IModule * GetModules() { \
        return static_modules; \
    }
#endif //WIN32

#define CREATE_MODULE(Module) \
class Factory##Module {\
public:\
    Factory##Module(China2D::Api::IModule * & pModule) {\
        China2D::Api::IModule * p = txnew Module();\
        const char * temp = #Module; \
        memcpy((void *)&(p->_Name), &temp, sizeof(const char *));\
        memcpy((void *)&(p->_Next), &pModule, sizeof(pModule));\
        pModule = p;\
    }\
};\
Factory##Module factroy##Module(static_modules);

#define GetModule(engine, p, name)\
    p = engine->GetModule<I##name>(#name); \
    XASSERT(p, "wtf");

#endif //__iModule_h__
