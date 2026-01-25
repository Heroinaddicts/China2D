#ifndef __PlatformGlfw_h__
#define __PlatformGlfw_h__

#include "IBasePlatform.h"

namespace China2D {
	class PlatformGlfw : public IBasePlatform {
	public:
		virtual ~PlatformGlfw() {}

		Api::IWindow* CreateWindow(int w, int h, const std::string& title) override;
		bool Initialize() override;
		void Shutdown() override;
	};
}

#endif //__PlatformGlfw_h__
