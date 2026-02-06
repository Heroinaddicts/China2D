#include "Texture.h"
#include "GLInc.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace China2D {
	Texture* Texture::LoadFromFile(const std::string& path) {
        int width, height, channels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

        if (data == nullptr) {
            return nullptr;
        }

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return txnew Texture(textureID, width, height);
	}
}
