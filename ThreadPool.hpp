#pragma once

#include <atomic>
#include <vector>
#include <future>
#include "PriorityTaskQueue.hpp"
#include "MainWorker.hpp"
#include "SubWorker.hpp"


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
            std::atomic<uint32_t> curThread; // 当前线程数

            std::vector<MainWorker> mainWorker; // 主线程池
            std::vector<SubWorker> subWorker; // 副线程池

            PriorityTaskQueue mainQueue; // 主任务队列

    };
}

namespace System {

    template<typename F, typename ...Args>
    auto ThreadPool::AddTask(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
        using returnType = std::invoke_result_t<F, Args...>;
    
    //封装函数
    auto task_ptr = std::make_shared<std::packaged_task<returnType()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<returnType> result = task_ptr->get_future();

    if(stop == true) throw std::runtime_error("Add task on stopped ThreadPool!");

    mainQueue.emplace([task_ptr]{
        std::invoke(*task_ptr);
    });

    return result;
    }

}