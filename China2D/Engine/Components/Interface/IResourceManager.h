#ifndef __IResourceManager_h__
#define __IResourceManager_h__

#include "IEngineComponent.h"

namespace China2D {
	class IResourceManager : public IEngineComponent, public Api::IResourceManagerApi {
	public:
		virtual ~IResourceManager() {}
	};
}

#endif //__IResourceManager_h__
