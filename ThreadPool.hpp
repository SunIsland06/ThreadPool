#pragma once

#include <atomic>
#include <vector>
#include <future>

#include "Task/PriorityTask.hpp"
#include "Queue/PriorityTaskQueue.hpp"
#include "Worker/MainWorker.hpp"
#include "Worker/SubWorker.hpp"


namespace System {

    class ThreadPool {
        public:
            ThreadPool(uint32_t mainThread_, uint32_t subThread_);

            ~ThreadPool();

            template<typename FuncType>
            auto addTask(FuncType&& func, uint8_t priority) -> std::future<std::invoke_result_t<FuncType>>;

        private:
            std::atomic<bool> stop; // 线程池是否关闭
            std::atomic<uint32_t> mainThread; // 主线程数
            std::atomic<uint32_t> subThread; // 最大副线程数
            std::atomic<uint32_t> curThread; // 当前线程数

            std::vector<MainWorker> mainWorker; // 主线程池
            std::vector<SubWorker> subWorker; // 副线程池

            PriorityTaskQueue<PriorityTask<void>> mainQueue; // 主任务队列

    };
}

#include "ThreadPool.inl"