/*
 * Queue.h
 *
 *  Created on: Feb 20, 2015
 *      Author: rmin
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <mutex>
#include <queue>
#include <condition_variable>

template <typename T>
class Queue {
private:
    std::mutex mutex_;
    std::queue<T> queue_;
    std::condition_variable cv;
public:
    Queue() {}
    ~Queue() {}
    T pop() {
		std::unique_lock<std::mutex> lock(mutex_);
		cv.wait(lock, [&]() {return !queue_.empty();});
		T value = queue_.front();
		queue_.pop();
		return value;
    }
    void push(T value) {
    	std::unique_lock<std::mutex> lock(mutex_);
    	queue_.push(value);
    	cv.notify_one();
    }
};

#endif /* QUEUE_H_ */
