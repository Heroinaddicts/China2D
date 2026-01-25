#ifndef __IRenderHIPlatform_h__
#define __IRenderHIPlatform_h__

#include "China2DApi.h"

namespace China2D {
	class IRenderHIPlatform : public Api::IRenderHI {
	public:
		virtual ~IRenderHIPlatform() {}

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;
	};
}

#endif //__IRenderHIPlatform_h__
