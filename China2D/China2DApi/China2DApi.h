#ifndef __China2DApi_h__
#define __China2DApi_h__

#include "MultiSys.h"

namespace China2D {
	class IWindow {
	public:
		virtual ~IWindow() {}
	};

	class IWindowApi {
	public:
		virtual ~IWindowApi() {}

		virtual IWindow CreateWindow(const std::string& title, const int width, const int height) = 0;
	};



	class IEngine {
	public:
		virtual ~IEngine() {}

		virtual IWindowApi* GetWindowApi() const = 0;
	};
}

#endif //__China2DApi_h__
