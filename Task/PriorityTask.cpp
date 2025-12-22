#include "PriorityTask.hpp"

namespace System {

    template<typename Task>
    bool PriorityTask<Task>::operator < (const PriorityTask& other) {
        if(priority == other.priority) [[likely]]{
            return sequence < other.sequence;
        }
        else [[unlikely]]{
            return priority < other.priority;    
        }
    }
    
}