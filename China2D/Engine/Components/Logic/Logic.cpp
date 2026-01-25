#include "Logic.h"
#include "Engine.h"

#include "MultiSys.h"
#include <vector>

#ifdef WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif //WIN32

namespace China2D {
	RegistEngineComponent(Logic);

    typedef Api::IModule* (*__GetModules)(void);

    Logic* Logic::GetInstance() {
        static Logic s_Logic;
        return &s_Logic;
    }

    Api::IModule* Logic::FindModule(const std::string& name) {
        auto itor = _ModuleMap.find(name);
        if (_ModuleMap.end() != itor) {
            return itor->second;
        }

        return nullptr;
    }

    bool Logic::Initialize(Engine* const engine) {
        return true;
    }

    bool Logic::Launch(Engine* const engine) {
        const char* module_path = engine->GetLaunchParameter("module_path");
        module_path ? _ModulePath = module_path : _ModulePath = SafeSystem::File::GetDirectoryOfCurrentExe();

        const std::vector<std::string>& moduleNames = engine->GetModuleNames();
        for (int i = 0; i < moduleNames.size(); i++) {
#ifdef WIN32
            std::string path = _ModulePath + "/" + moduleNames[i] + ".dll";
            HINSTANCE hinst = ::LoadLibraryA(path.c_str());
            if (!hinst) {
                ErrorLog(engine, "load %s error code %d\n", path.c_str(), ::GetLastError());
                return false;
            }

            __GetModules fun = (__GetModules)::GetProcAddress(hinst, GET_MODULES_FUNC_NAME);
#endif //Win32

#ifdef Linux
            dlerror();
            std::string path = _ModulePath + "/lib" + moduleNames[i] + ".so";
            void* handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!handle) {
                const char* err = dlerror();
                ErrorLog(engine, "load %s error %s", path.c_str(), err ? err : "unknown error");
                return false;
            }

            __GetModules fun = (__GetModules)dlsym(handle, GET_MODULES_FUNC_NAME);
#endif //Linux
            XASSERT(fun, "Can not export dll function GetModules, dll %s", path.c_str());
            Api::IModule* module = fun();
            while (nullptr != module) {
                if (false == module->Initialize(engine)) {
                    ErrorLog(engine, "Module %s Initialize failed", module->_Name);
                    return false;
                }

                TraceLog(engine, "Module %s Initialized", module->_Name);
                _ModuleMap.insert(std::make_pair(module->_Name, module));
                module = module->_Next;
            }
        }

        for (auto itor = _ModuleMap.begin(); itor != _ModuleMap.end(); itor++) {
            if (false == itor->second->Launch(engine)) {
                ErrorLog(engine, "Module %s Launch failed", itor->second->_Name);
                return false;
            }
            TraceLog(engine, "Module %s Launched", itor->second->_Name);
        }

        return true;
    }

    void Logic::Release(Engine* const engine) {
        for (auto itor = _ModuleMap.begin(); itor != _ModuleMap.end(); itor++) {
            if (false == itor->second->Destroy(engine)) {
                ErrorLog(engine, "Module %s Destroy failed", itor->second->_Name);
            }
        }
    }

    void Logic::EarlyUpdate(Engine* const engine) {

    }

    void Logic::Update(Engine* const engine) {
        for (auto itor = _ModuleMap.begin(); itor != _ModuleMap.end(); itor++) {
            itor->second->Update(engine);
        }
    }

    void Logic::LaterUpdate(Engine* const engine) {

    }

    void Logic::FixedUpdate(Engine* const engine) {

    }
}
