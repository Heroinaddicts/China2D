#ifndef __Texture_h__
#define __Texture_h__

#include "China2DApi.h"
#include <OpenGL/Glfw/src/internal.h>

namespace China2D {
	class Texture : public Api::ITexture {
	public:
		virtual ~Texture() {}

	private:
		GLuint _TextureID;
		int _Width;
		int _Height;
	};
}

#endif //__Texture_h__
