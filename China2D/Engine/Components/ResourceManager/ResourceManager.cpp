#include "ResourceManager.h"
#include "Engine.h"

namespace China2D {
    RegistEngineComponent(ResrouceManager);

    ResrouceManager* ResrouceManager::GetInstance() {
        static ResrouceManager s_Instance;
        return &s_Instance;
    }

    bool ResrouceManager::Initialize(Engine* const engine) {
        return true;
    }

    bool ResrouceManager::Launch(Engine* const engine) {
        return true;
    }

    void ResrouceManager::EarlyUpdate(Engine* const engine) {
    }

    void ResrouceManager::Update(Engine* const engine) {
    }

    void ResrouceManager::LaterUpdate(Engine* const engine) {
    }

    void ResrouceManager::FixedUpdate(Engine* const engine) {
    }

    void ResrouceManager::Release(Engine* const engine) {
    }

    Api::ITexture* ResrouceManager::LoadTexture(const std::string& path) {
        return nullptr;
    }

    Api::IRenderMesh* ResrouceManager::LoadMesh(const std::string& path) {
        return nullptr;
    }

    void ResrouceManager::LoadTextureAsync(const std::string& path, std::function<void(Api::ITexture*)> callback) {

    }

    void ResrouceManager::LoadRenderMeshAsync(const std::string& path, std::function<void(Api::IRenderMesh*)> callback) {
    }

    void ResrouceManager::DestroyResource(Api::IResource* resource) {

    }
}
