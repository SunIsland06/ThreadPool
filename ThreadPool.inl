#pragma once

#include "ThreadPool.hpp"

namespace System {

    template<typename FuncType>
    auto ThreadPool::addTask(FuncType&& func, uint8_t priority = 128) 
    -> std::future<std::invoke_result_t<FuncType>> {
        // 推导返回值
        using ReturnType = std::invoke_result_t<FuncType>;

        // 封装函数
        std::packaged_task<ReturnType()> task(std::forward(func));
        std::future<ReturnType> result(task.get_future());

        // 
        mainQueue.emplace(std::move(task), priority);

    }

}