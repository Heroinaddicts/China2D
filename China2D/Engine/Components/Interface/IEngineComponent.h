#ifndef __IEngineComponent_h__
#define __IEngineComponent_h__

#include "IModule.h"

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

#endif //__IEngineComponent_h__
