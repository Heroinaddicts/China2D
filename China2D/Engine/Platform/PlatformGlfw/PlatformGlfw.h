#ifndef __PlatformGlfw_h__
#define __PlatformGlfw_h__

#include "IBasePlatform.h"
#include <set>
namespace China2D {
	class PlatformGlfw : public IBasePlatform {
	public:
		virtual ~PlatformGlfw() {}

		Api::IWindow* CreateWindow(int w, int h, const std::string& title) override;
		void ReleaseWindow(Api::IWindow* const window) override;
		bool Initialize() override;
		void Shutdown() override;

		void PullEvents() override;

	private:
		std::set<Api::IWindow*> _Windows;
	};
}

#endif //__PlatformGlfw_h__
