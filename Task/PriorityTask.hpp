#pragma once

#include <future>

namespace System {

    template<typename FuncType>
    class PriorityTask {

        public:
            PriorityTask(FuncType&& func, uint8_t priority_);

            bool operator < (const PriorityTask& other);
            
        private:
            std::packaged_task<FuncType()> task; // 封装好的任务

            uint8_t priority; // 优先级
            uint64_t sequence; // 入队顺序
            inline std::atomic<uint64_t> counter{0} // 计数器
    };

}

#include "PriorityTask.inl"