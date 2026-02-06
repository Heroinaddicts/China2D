#ifndef __ResrouceManager_h__
#define __ResrouceManager_h__

#include "IResourceManager.h"

namespace China2D {
	class ResrouceManager : public IResourceManager {
	public:
		virtual ~ResrouceManager() {}

		static ResrouceManager* GetInstance();

		// 通过 IResourceManager 继承
		bool Initialize(Engine* const engine) override;
		bool Launch(Engine* const engine) override;
		void EarlyUpdate(Engine* const engine) override;
		void Update(Engine* const engine) override;
		void LaterUpdate(Engine* const engine) override;
		void FixedUpdate(Engine* const engine) override;
		void Release(Engine* const engine) override;

		Api::ITexture* LoadTexture(const std::string& path) override;
		Api::IRenderMesh* LoadMesh(const std::string& path) override;

		void LoadTextureAsync(const std::string& path, std::function<void(Api::ITexture*)> callback) override;
		void LoadRenderMeshAsync(const std::string& path, std::function<void(Api::IRenderMesh*)> callback) override;

		void DestroyResource(Api::IResource* resource) override;
	};
}

#endif //__ResrouceManager_h__
