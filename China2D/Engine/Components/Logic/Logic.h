#ifndef __Logic_h__
#define __Logic_h__

#include "Header.h"
namespace China2D {
    class Logic : public ILogic {
    public:
        virtual ~Logic() {}

        static Logic* GetInstance();

        Api::IModule* FindModule(const std::string& name) override;
        // 通过 ILogic 继承
		bool Initialize(Engine* const engine) override;
		bool Launch(Engine* const engine) override;

		void EarlyUpdate(Engine* const engine) override;
		void Update(Engine* const engine) override;
		void LaterUpdate(Engine* const engine) override;

		void FixedUpdate(Engine* const engine) override;

		void Release(Engine* const engine) override;
    private:
        Logic() {}

    private:
        std::string _ModulePath;
        std::map<std::string, Api::IModule*> _ModuleMap;
    };
}

#endif //__Logic_h__
