#ifndef __Engine_h__
#define __Engine_h__

#include "China2DApi.h"
#include "SafeString.h"
#include <map>
#include <set>
	
namespace China2D {
	class IEngineComponent;
	class Window;
	class Engine : public Api::IEngine {
	public:
		virtual ~Engine() {}

		static Engine* GetInstance();

#define EngineAllocID Engine::AllocID()
		static unsigned int AllocID() {
			static unsigned int s_NextID = 0;
			return s_NextID++;
		}

		__forceinline const std::string &GetName() const {
			return _Name;
		}

		__forceinline bool IsShutdown() const {
			return false;
		}

		bool Initialize() override;
		Api::IWindow* CreateWindow(const std::string& title, int width, int height) override;
		Api::IRenderer* GetRenderer2D() override;
		Api::IResourceManagerApi* GetResourceManagerApi() override;

		bool Launch();
		void Shutdown() override;

		bool AnalysisLaunchParameters(const int argc, const char** args, const char** env);
		__forceinline const char* GetLaunchParameter(const std::string& name) const {
			auto itor = _ParameterMap.find(name);
			if (_ParameterMap.end() == itor) {
				return nullptr;
			}

			return itor->second.c_str();
		}
		__forceinline const std::vector<std::string>& GetModuleNames() const { return _ModuleNames; }

		__forceinline void RegistComponent(IEngineComponent* const component) {
			_Components.push_back(component);
		}

		void SetMinLogLevel(const unsigned int level) override;
		unsigned int GetMinLogLevel() override;
		void LogAsync(const unsigned int level, const char* header, const char* content, const bool console, const char* file, const int line) override;
		void LogSync(const unsigned int level, const char* header, const char* content, const bool console, const char* file, const int line) override;

		void Update();

	private:
		Window * _Window;
		std::map<std::string, std::string> _ParameterMap;
		std::string _Name;
		std::vector<std::string> _ModuleNames;
		std::vector<IEngineComponent*> _Components;
	};

	extern Engine* g_Engine;
}

#endif //__Engine_h__
