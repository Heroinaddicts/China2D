#ifndef __IEngineComponent_h__
#define __IEngineComponent_h__

#include "China2DApi.h"

namespace China2D {
	class Engine;
	class IEngineComponent {
	public:
		virtual ~IEngineComponent() {}

		virtual bool Initialize(Engine* const engine) = 0;
		virtual bool Launch(Engine* const engine) = 0;

		virtual void EarlyUpdate(Engine* const engine) = 0;
		virtual void Update(Engine* const engine) = 0;
		virtual void LaterUpdate(Engine* const engine) = 0;

		virtual void FixedUpdate(Engine* const engine) = 0;

		virtual void Release(Engine* const engine) = 0;
	};
}

#define RegistEngineComponent(Component) \
	class Component##Factroy {\
	public:\
		Component##Factroy() {\
			Engine::GetInstance()->RegistComponent(Component::GetInstance());\
		}\
	};\
	Component##Factroy __##Component;

#endif //__IEngineComponent_h__
