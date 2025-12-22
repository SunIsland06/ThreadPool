#include "ThreadPool.hpp"

System::ThreadPool::ThreadPool(uint32_t minThread_ = std::thread::hardware_concurrency(), 
                               uint32_t maxThread_ = std::thread::hardware_concurrency() * 2)
: stop(false), minThread(minThread_), maxThread(maxThread_) {
    for(int i = 0; i < minThread; ++i) {
        mainWorker.emplace_back();
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
