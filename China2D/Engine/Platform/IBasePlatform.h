#ifndef __IBasePlatform_h__
#define __IBasePlatform_h__

#include "China2DApi.h"

namespace China2D {
	class IBasePlatform : public Api::IPlatform {
	public:
		virtual ~IBasePlatform() {}

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;
	};
}

#endif //__IBasePlatform_h__
