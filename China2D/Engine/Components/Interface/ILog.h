#ifndef __ILog_h__
#define __ILog_h__

#include "IEngineComponent.h"

namespace China2D {
	class ILog : public IEngineComponent {
	public:
		virtual ~ILog() {}

		virtual void SetMinLogLevel(const unsigned int level) = 0;
		virtual unsigned int GetMinLogLevel() const = 0;

		virtual void LogAsync(const unsigned int level, const char* header, const char* content, const bool console, const char* file, const int line) = 0;
		virtual void LogSync(const unsigned int level, const char* header, const char* content, const bool console, const char* file, const int line) = 0;
	};
}

#endif //__ILog_h__
