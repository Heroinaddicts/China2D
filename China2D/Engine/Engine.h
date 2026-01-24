#ifndef __Engine_h__
#define __Engine_h__

#include "China2DApi.h"
#include "SafeString.h"
#include <map>

namespace China2D {
	class IEngineComponent;
	class Engine : public Api::IEngine {
	public:
		virtual ~Engine() {}

		static Engine* GetInstance();

		Api::IRenderHI* GetRenderHI();

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
		void Initialize();

	private:
		static Engine* s_Instance;

		std::map<std::string, std::string> _ParameterMap;
		std::vector<std::string> _ModuleNames;
		std::string _Name;

		std::vector<IEngineComponent*> _Components;
	};
}

#endif //__Engine_h__
