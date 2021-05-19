#pragma once
#include <iostream>
#include <cstddef>
#include <utility>
#include <stdexcept>

template<typename T>
class Queue {
	private:
		size_t capacity_;
		size_t size_;
		int first_;
		int last_;
		T* data_;

		//Optional -- koristi se samo u overload-u operator<< na dnu file-a
		void print() const;

		//omoguci operatoru << da pozove print() koji je privatan metod
		template<typename U>
		friend std::ostream& operator<<(std::ostream&, Queue<U>&);

	public:

		//Constructors
		Queue(size_t cap = 100) : capacity_{cap}, size_{0}, first_{0}, last_{0}, data_{new T[cap]} {}
		
		Queue(const Queue& other);
		Queue(Queue&& other);
		~Queue() {delete[] data_;} 

		Queue& operator=(const Queue& other);
		Queue& operator=(Queue&& other);

		//Methods
		template<typename U>
		Queue& push(U&&);
		T pop();
		T& top();
		T& top() const;

		size_t capacity() const {return capacity_;}
		size_t size() const {return size_;}
		bool isEmpty() const {return !size_;}

		//Optional methods
		bool isFull() const {return capacity_==size_;}
		
};

template<typename T>
Queue<T>::Queue(const Queue& other) :
	capacity_{other.capacity_},
	size_{other.size_},
	first_{other.first_},
	last_{other.last_},
	data_{new T[capacity_]} {

		for (size_t i = 0; i < size_; i++) {
			const size_t index = (i+first_) % capacity_;
			data_[index] = other.data_[index];
		}
}

template<typename T>
Queue<T>::Queue(Queue&& other) :
	capacity_{other.capacity_},
	size_{other.size_},
	first_{other.first_},
	last_{other.last_},
	data_{other.data_} {
	
		other.data_ = nullptr;
		other.capacity_ = 0;
		other.size_ = 0;
		other.first_= 0;
		other.last_= 0;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
		
	size_ = other.size_;
	first_ = other.first_;
	last_ = other.last_;

	if (capacity_ < other.capacity_) {
		delete[] data_;
		data_ = new T[other.capacity_];
	}

	capacity_ = other.capacity_;
	
	for (size_t i = 0; i < size_; i++) {
		const size_t index = (i+first_) % capacity_;
		data_[index] = other.data_[index];
	}

	return *this;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) {
		
	capacity_ = other.capacity_;
	size_ = other.size_;
	first_ = other.first_;
	last_ = other.last_;

	delete[] data_;
	data_ = other.data_;

	other.data_ = nullptr;
	return *this;
}

template <typename T>
T Queue<T>::pop() {
	if (isEmpty()) throw std::out_of_range{"The Queue is already empty"};
	
	int temp = first_;	
	first_ = (first_+1) % capacity_;
	size_--;

	return std::move(data_[temp]);
}

template <typename T>
T& Queue<T>::top() {
	if (isEmpty()) throw std::out_of_range{"The queue is empty."};
	return data_[first_];
}

template <typename T>
T& Queue<T>::top() const {
	if (isEmpty()) throw std::out_of_range{"The queue is empty."};
	return data_[first_];
}

template<typename T>
template<typename U>
Queue<T>& Queue<T>::push(U&& el) {
	if (isFull()) throw std::out_of_range{"The Queue has reached it's maximum capacity."};

	if (isEmpty()) data_[first_] = std::forward<U>(el); else {
		last_ = (last_+1) % capacity_;
		data_[last_] = std::forward<U>(el);
	}

	size_++;
	return *this;

}

template <typename T>
void Queue<T>::print() const {

	for (int i = 0; i<size_; i++) {
		const int index = (i+first_) % capacity_;
		std::cout << data_[index] << " ";
	}

	std::cout << std::endl;

}

template<typename T>
std::ostream& operator<<(std::ostream& out, Queue<T>& queue) {

	queue.print();
	return out;
}
