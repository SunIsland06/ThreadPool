#pragma once

#include <atomic>
#include <vector>
#include <future>
#include "Queue/PriorityTaskQueue.hpp"
#include "Worker/MainWorker.hpp"
#include "Worker/SubWorker.hpp"


namespace System {

    class ThreadPool {
        public:
            ThreadPool(uint32_t, uint32_t);

            ~ThreadPool();

            template<typename F, typename ...Args>
            auto AddTask(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>;

        private:
            std::atomic<bool> stop; // 线程池是否关闭
            std::atomic<uint32_t> minThread; // 最小线程数
            std::atomic<uint32_t> maxThread; // 最大线程数
            std::atomic<uint32_t> curThread; // 当前副线程数

            std::vector<MainWorker> mainWorker; // 主线程池
            std::vector<SubWorker> subWorker; // 副线程池

            PriorityTaskQueue mainQueue; // 主任务队列

    };
}

#include "ThreadPool.inl"