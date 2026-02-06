#ifndef __Texture_h__
#define __Texture_h__

#include "China2DApi.h"
#include <OpenGL/Glfw/src/internal.h>

namespace China2D {
	class Texture : public Api::ITexture {
	public:
		virtual ~Texture() {}

		static Texture* LoadFromFile(const std::string& path);

	private:
		Texture(GLuint textureID, int width, int height)
			: _TextureID(textureID), _Width(width), _Height(height) {}

	private:
		GLuint _TextureID;
		int _Width;
		int _Height;
	};
}

#endif //__Texture_h__
