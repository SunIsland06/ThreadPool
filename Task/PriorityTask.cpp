#include "PriorityTask.hpp"

namespace System {

    template<typename FuncType>
    PriorityTask<FuncType>::PriorityTask(FuncType&& func_, uint8_t priority_) 
    : task(std::move(func_)), priority(priority_), sequence(++counter) {

    }

    template<typename FuncType>
    bool PriorityTask<FuncType>::operator < (const PriorityTask& other) {
        if(priority == other.priority) [[likely]]{
            return sequence < other.sequence;
        }
        else [[unlikely]]{
            return priority < other.priority;    
        }
    }

}