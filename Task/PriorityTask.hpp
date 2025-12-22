#pragma once

#include <future>

namespace System {

    template<typename Task>
    class PriorityTask {

        public:
            template<typename FuncType>
            PriorityTask(FuncType&& func, uint8_t priority_);

            bool operator < (const PriorityTask& other);
        private:
            std::packaged_task<Task()> task; // 封装好的任务

            uint8_t priority; // 优先级
            uint64_t sequence; // 入队顺序

    };

}

#include "PriorityTask.inl"