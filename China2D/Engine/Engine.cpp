#include "Engine.h"
#include "IEngineComponent.h"

#include "SafeSystem.h"
#include "Graphics/OpenGL/RenderHIOpenGL.h"
#include "PlatformGlfw/PlatformGlfw.h"

#include "Components/Log/Log.h"

namespace China2D {
    Engine* g_Engine = nullptr;

    Engine* Engine::GetInstance() {
        if (nullptr == g_Engine) {
            g_Engine = txnew Engine();
        }

        return g_Engine;
    }

    void Engine::SetEngineDesc(const Api::EngineDesc& desc) {
		_Desc = desc;
    }

    void Engine::Shutdown() {
        for (int i = 0; i < _Components.size(); i++) {
            _Components[i]->Release(this);
        }
        _Components.clear();

        for (auto it = _Windows.begin(); it != _Windows.end(); it++) {
            (*it)->Destroy();
        }
        _Windows.clear();

        if (nullptr != _RHI) {
            _RHI->Shutdown();
            txdel _RHI;
            _RHI = nullptr;
        }

        if (nullptr != _Platform) {
            _Platform->Shutdown();
            txdel _Platform;
            _Platform = nullptr;
        }
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

    bool Engine::Launch() {
		for (int i = 0; i != _Components.size(); i++) {
			if (!_Components[i]->Initialize(this)) {
				ErrorLog(this, "Component initialize falid");
				return false;
			}
		}

		for (int i = 0; i != _Components.size(); i++) {
			if (!_Components[i]->Launch(this)) {
				ErrorLog(this, "Component Launch falid");
				return false;
			}
		}

		switch (_Desc.Platform) {
		case Api::ePlatform::GLFW: {
			_Platform = txnew PlatformGlfw();
			break;
		}
		default:
			ErrorLog(this, "China2D only support platform glfw now");
			return false;
		}

		if (!_Platform->Initialize()) {
			_Platform->Shutdown();
			delete _Platform;
			_Platform = nullptr;
			return false;
		}

		switch (_Desc.RHI) {
		case Api::eRHI::OpenGL: {
			_RHI = txnew RenderHIOpenGL(AllocID(), "RenderHIOpenGL");
			break;
		}
		default:
			ErrorLog(this, "China2D only support opengl noew");
			return false;
		}

		if (!_RHI->Initialize()) {
			_RHI->Shutdown();
			delete _RHI;
			_RHI = nullptr;
			return false;
		}

        return true;
    }

    void Engine::SetMinLogLevel(const unsigned int level) {
        Log::GetInstance()->SetMinLogLevel(level);
    }

    unsigned int Engine::GetMinLogLevel() {
        return Log::GetInstance()->GetMinLogLevel();
    }

    void Engine::LogAsync(const unsigned int level, const char* header, const char* content, const bool console, const char* file, const int line) {
        Log::GetInstance()->LogAsync(level, header, content, console, file, line);
    }

    void Engine::LogSync(const unsigned int level, const char* header, const char* content, const bool console, const char* file, const int line) {
		Log::GetInstance()->LogSync(level, header, content, console, file, line);
    }

    Api::IPlatform* Engine::GetPlatform() const {
        return nullptr;
    }

    Api::IRenderHI* Engine::GetRenderHI() const {
		return _RHI;
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
