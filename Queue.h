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


template <typename T>
class Queue {
private:
    std::mutex mutex_;
    std::queue<T> queue_;
public:
    Queue();
    ~Queue();
    T pop();
    void push(T value);
    bool empty();
    int getSize();
};

#endif /* QUEUE_H_ */
