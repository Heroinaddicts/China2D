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

    void ResrouceManager::SetAssetPath(const std::string& path) {
    }

    Api::ITexture* ResrouceManager::LoadTexture(const std::string& filePath) {
        return nullptr;
    }

    Api::IRenderMesh* ResrouceManager::LoadMesh(const std::string& filePath) {
        return nullptr;
    }

    void ResrouceManager::LoadTextureAsync(const std::string& filePath, std::function<void(Api::ITexture*)> callback) {
    }

    void ResrouceManager::LoadRenderMeshAsync(const std::string& filePath, std::function<void(Api::IRenderMesh*)> callback) {
    }

    void ResrouceManager::DestroyResource(Api::IResource* resource) {
    }
}
