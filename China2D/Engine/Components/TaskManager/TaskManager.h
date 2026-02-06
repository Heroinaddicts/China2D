#ifndef __TaskManager_h__
#define __TaskManager_h__

#include "Header.h"

namespace China2D {
    class TaskManager : public ITaskManager, public SafeThread {
    public:
        virtual ~TaskManager() {}

        static TaskManager* GetInstance();

        // Inherited via iTaskManager
        bool Initialize(Engine* const engine) override;
        bool Launch(Engine* const engine) override;
        void Release(Engine* const engine) override;
        void EarlyUpdate(Engine* const engine) override;
        void Update(Engine* const engine) override;
        void FixedUpdate(Engine* const engine) override;
        void LaterUpdate(Engine* const engine) override;


        void PushTask(const Api::eTaskProcessorType processorType, Api::fTask task, Api::fTaskCompleted callback, const Int64 mask) override;
        Api::ITaskGroup* CreateTaskGroup() override;

        // Inherited via SafeThread
        void Run(void* context) override;

    private:
        int _NumberOfCpuCore;
        SafeQueue::SpscQueue<TaskInfo*> * _TaskReqMaskQueue;
    };
}

#endif //__TaskManager_h__
