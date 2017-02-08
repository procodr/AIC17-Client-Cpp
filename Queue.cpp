/*
 * Queue.cpp
 *
 *  Created on: Feb 20, 2015
 *      Author: rmin
 */

#include "Queue.h"

template<typename T>
Queue<T>::Queue() {
	// TODO Auto-generated constructor stub

}

template<typename T>
Queue<T>::~Queue() {
	// TODO Auto-generated destructor stub
}

template<typename T>
T Queue<T>::pop() {
	std::unique_lock<std::mutex> lock(mutex_);
	cv.wait(lock, [&](){ return !queue_.empty(); });
	T value = queue_.front();
	queue_.pop();
	return value;
}

template<typename T>
void Queue<T>::push(T value) {
	std::unique_lock<std::mutex> lock(mutex_);
	queue_.push(value);
	cv.notify_one();
}

