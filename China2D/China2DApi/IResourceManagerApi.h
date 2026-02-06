#ifndef __IResourceManagerApi_h__
#define __IResourceManagerApi_h__

#include "MultiSys.h"
#include "Structs.h"
#include "ITexture.h"
#include "IRenderMesh.h"
#include "IResource.h"

namespace China2D {
    namespace Api {
        class IResourceManagerApi {
        public:
            virtual ~IResourceManagerApi() {}

            virtual ITexture* LoadTexture(const std::string& filePath) = 0;
            virtual IRenderMesh* LoadMesh(const std::string& filePath) = 0;

			virtual void LoadTextureAsync(const std::string& filePath, std::function<void(ITexture*)> callback) = 0;
			virtual void LoadRenderMeshAsync(const std::string& filePath, std::function<void(IRenderMesh*)> callback) = 0;

            virtual void DestroyResource(IResource* resource) = 0;
        };
    }
}

#endif //__IResourceManagerApi_h__
