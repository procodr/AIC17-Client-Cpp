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
	this->mutex_.lock();
	T value;
	if (!this->queue_.empty()) {
		value = this->queue_.front();  // undefined behavior if queue_ is empty
									   // may segfault, may throw, etc.
		this->queue_.pop();
	}
	this->mutex_.unlock();
	return value;
}

template<typename T>
void Queue<T>::push(T value) {
	this->mutex_.lock();
	this->queue_.push(value);
	this->mutex_.unlock();
}

template<typename T>
bool Queue<T>::empty() {
	this->mutex_.lock();
	bool check = this->queue_.empty();
	this->mutex_.unlock();
	return check;
}

template<typename T>
int Queue<T>::getSize() {
	return queue_.size();
}
