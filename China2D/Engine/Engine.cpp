#include "Engine.h"
#include "IEngineComponent.h"

#include "SafeSystem.h"


namespace China2D {

    Engine * Engine::s_Instance = nullptr;

    Engine* Engine::GetInstance() {
        if (nullptr == s_Instance) {
            s_Instance = txnew Engine();
            s_Instance->Initialize();
        }

        return s_Instance;
    }

    bool Engine::AnalysisLaunchParameters(const int argc, const char** args, const char** env) {
        for (int i = 1; i < argc; ++i) {
            std::vector<std::string> parms;
            int count = China2D::SafeString::Split(args[i], " ", parms);
            for (int index = 0; index < parms.size(); index++) {
                if (strncmp(parms[index].c_str(), "--", 2) == 0) {
                    const char* start = parms[index].c_str() + 2;
                    const char* equal = strstr(start, "=");
                    if (equal != nullptr) {
                        std::string name(start, equal);
                        std::string val(equal + 1);
                        _ParameterMap[name] = val;
                        TraceLog(this, "Launch args %s=%s", name.c_str(), val.c_str());
                    }
                    else if (strlen(parms[index].c_str()) > 2) {
                        _ParameterMap[parms[index].c_str() + 2] = "";
                        TraceLog(this, "Launch args %s", parms[index].c_str() + 2);
                    }
                }
            }
        }

        const char* modules = GetLaunchParameter("modules");
        if (modules) {
            SafeString::Split(modules, ";", _ModuleNames);
        }

        const char* name = GetLaunchParameter("name");
        _Name = name ? name : "China2D";
        return true;
    }

    void Engine::Initialize() {
		for (int i = 0; i != _Components.size(); i++) {
			if (!_Components[i]->Initialize(this)) {
				ErrorLog(this, "Component initialize falid");
				return;
			}
		}

		for (int i = 0; i != _Components.size(); i++) {
			if (!_Components[i]->Launch(this)) {
				ErrorLog(this, "Component Launch falid");
				return;
			}
		}
    }

    void Engine::SetMinLogLevel(const unsigned int level) {

    }

    unsigned int Engine::GetMinLogLevel() {
        return 0;
    }

    void Engine::LogAsync(const unsigned int level, const char* header, const char* content, const bool console, const char* file, const int line) {
    }

    void Engine::LogSync(const unsigned int level, const char* header, const char* content, const bool console, const char* file, const int line) {

    }

    Api::IRenderHI* Engine::GetRenderHI() {
        return nullptr;
    }

    void Engine::Update() {
		while (true) {
			for (int i = 0; i != _Components.size(); i++) {
				_Components[i]->EarlyUpdate(this);
			}

			for (int i = 0; i != _Components.size(); i++) {
				_Components[i]->Update(this);
			}

			for (int i = 0; i != _Components.size(); i++) {
				_Components[i]->LaterUpdate(this);
			}
        }
    }
}
