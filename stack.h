#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// class inherits from vector publicly 
template <typename T>
class Stack : public std::vector<T> {
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
private:
	std::vector<T> list;
    int top_; 
};

#endif


template <typename T>
Stack<T>::Stack() 
{
	// initialize top_ index to -1 so that each time a new 
	// element is added, it increments
	// (note that indexing begins at 0 not 1)
	top_ = -1;
}

template <typename T>
Stack<T>::~Stack()
{

}

template <typename T>
bool Stack<T>::empty() const
{
	// returns TRUE if top_ is equal to -1 
	// (note that top_ is essentially index of last element and if it is -1,
	// no elements are currently in the stack)
	if (top_ == -1) {
		return true;
	}
	
	return false;
}

template <typename T>
size_t Stack<T>::size() const
{
	// returns size of Stack by returning top_ data member incremented by 1
	// (note that top_ is essentially index of last element)
	return top_ + 1;
}

template <typename T>
void Stack<T>::push(const T& item)
{
	// push new Item to end of list 
	list.std::vector<T>::push_back(item);
	
	// increment top_ data member by 1
	top_++;
}

template <typename T>
void Stack<T>::pop()
{
	// throw error if nothing in list to pop
	if (size() == 0) {
		throw std::underflow_error("underflow error");
	}
	
	// pop last element in vector 
	list.std::vector<T>::pop_back();

	// decrement top_ data member by 1 (removing element from list)
	top_--;
}

template <typename T>
const T& Stack<T>::top() const
{
	// throw error if nothing in list 
	if (size() == 0) {
		throw std::underflow_error("underflow error");
	}
	
	// return last element in list (aka top_ data member index of vector)
	return list[top_];
}