#ifndef __ITaskManagerApi_h__
#define __ITaskManagerApi_h__

#include "MultiSys.h"
#include "SafeSystem.h"
#include <functional>

namespace China2D {
    namespace Api {
        class ITaskContext;
        typedef std::function<Int64(ITaskContext &)> fTask;
        typedef std::function<void(const Int64, const ITaskContext &)> fTaskCompleted;
        typedef std::function<void()> fTasksAllCompleted;


        enum class eTaskProcessorType {
            OrderedQueue = 0,  //丢入队列里排队等待线程池处理执行
            SeparateThread = 1 //立即启动新线程处理
        };

        class ITaskContext {
        public:
            virtual ~ITaskContext() {}

            template<typename T>
            T* Get() const {
                return (T*)this->GetContext();
            }

            template<typename T>
            void Set(T* const context) {
                this->SetContext(context);
            }

            virtual void* GetContext() const = 0;
            virtual void SetContext(void* const context) = 0;
        };

        class ITaskGroup {
        public:
            virtual ~ITaskGroup() {}

            virtual void AddTask(fTask task, fTaskCompleted callback) = 0;
            virtual void SetTasksAllCompletedCallback(fTasksAllCompleted callback) = 0;
            virtual void Start(const eTaskProcessorType type) = 0;
        };

        class ITaskManagerApi {
        public:
            virtual ~ITaskManagerApi() {}

            #define NOT_USE_MASK -1

            virtual void PushTask(const eTaskProcessorType processorType, fTask task, fTaskCompleted callback, const Int64 mask = NOT_USE_MASK) = 0;

            virtual ITaskGroup* CreateTaskGroup() = 0;
        };
    }
}

#endif //__ITaskManagerApi_h__
