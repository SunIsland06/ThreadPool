#pragma once

#include "ThreadPool.hpp"

namespace System {

    template<typename FuncType>
    auto ThreadPool::addTask(FuncType&& func, uint8_t priority = 128) 
    -> std::future<std::invoke_result_t<FuncType>> {
        // 推导返回值
        using ReturnType = std::invoke_result_t<FuncType>;

        // 封装函数
        std::packaged_task<ReturnType()> packagedTask(std::forward(func));
        std::future<ReturnType> result(packagedTask.get_future());

        // 推入主任务队列
        PriorityTask priorityTask(std::move(packagedTask), priority);
        mainQueue.emplace(std::move(priorityTask));

        return result;
    }

}