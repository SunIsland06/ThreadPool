#include "ThreadPool.hpp"

System::ThreadPool::ThreadPool(uint32_t mainThread_ = std::thread::hardware_concurrency(), 
                               uint32_t subThread_ = std::thread::hardware_concurrency() * 2)
: stop(false), mainThread(mainThread_), subThread(subThread_) {

    for(int i = 0; i < mainThread; ++i) {
        mainWorker.emplace_back();
        ++curThread;
    }
}

System::ThreadPool::~ThreadPool() {
    stop = true;

    // 销毁主线程池
    for(auto it : mainWorker) {

    }

    // 销毁副线程池
    for(auto it : subWorker) {

    }

}
