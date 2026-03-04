#pragma once

#include <queue>

#include "../Task/PriorityTask.hpp"

namespace System {

    template<typename FuncType>
    class PriorityTaskQueue {
        public:
            PriorityTaskQueue();
            
            void emplace(PriorityTask<FuncType>&& task);

        private:
            std::priority_queue<PriorityTask<FuncType>> taskQueue;

    };

}