#pragma once

#include <queue>

namespace System {

    template<typename Task>
    class PriorityTaskQueue {
        public:
            
            void emplace();

        private:
            std::priority_queue<PriorityTask<Task>> taskQueue;

    };

}