#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap 
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  // data member to store # children/parent 
	size_t m_ary_;
  // data member to store comparing functor 
	PComparator compare_;
  // data member to store elements of heap in a vector 
	std::vector<T> items_;
  // helper function for push function 
	void trickleUp_(size_t idx);
  // helper function for pop function 
	void heapify_(size_t idx = 0);
};


template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
{
  // initializing data members 
	m_ary_ = m;
	compare_ = c;
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() 
{

}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
  // push item to end of vector 
	items_.push_back(item);
  // while size of heap is greater than 1, call 
  // push helper function 
	if (items_.size() > 1) {
 		trickleUp_(items_.size() - 1);
	}
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty!");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return items_[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()) {
    // ================================
    // throw the appropriate exception
    // ================================
		throw std::underflow_error("Heap is empty!");
  }

  // swap first and last elements in heap 
	T temp = items_[0];
	items_[0] = items_[items_.size() - 1];
	items_[items_.size() - 1] = temp;
	// pop last element which was previously on top 
  items_.pop_back();
  // call pop helper function for top element 
  // while size of heap is greater than 1 
	if (items_.size() != 1) {
		heapify_(0);
	}
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const
{
  // check if heap size is equal to 0 using vector class "size" function 
	if (items_.size() == 0) {
		return true;
	}
  
  // if size != 0, return false because heap is not empty 
	return false;
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const
{
  // returns size of heap using vector class "size" function 
	return items_.size();
}

// push helper function
template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleUp_(size_t idx)
{
  // initialize index parent node using formula 
	size_t parent = (idx - 1) / m_ary_;
  // enter loop while parent is in bounds and should be switched with idx
	while (parent >= 0 && parent < items_.size() && compare_(items_[idx], items_[parent])) {
    // swap parent and current index 
    T temp = items_[idx];
	 	items_[idx] = items_[parent];
	 	items_[parent] = temp;
     // update idx and parent variables
		idx = parent;
    parent = (idx - 1) / m_ary_;
	}
}

// pop helper function 
template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify_(size_t idx)
{
	// calculate idx's first child 
  // initialize extremeChild (aka the best child) to first child as well
  size_t firstChild = idx * m_ary_ + 1;
	size_t extremeChild = idx * m_ary_ + 1;
  // return if idx does not have children 
  if (firstChild >= items_.size()) {
    return;
  }
  // runs to check each existing child of idx Node 
	for (size_t i = 0; i < m_ary_; i++) {
		// checks if child exists 
    if (firstChild + i < items_.size()) {
			// variable holds current child idx 
      size_t currChild = firstChild + i;
      // if current child is better than current best child, switch 
      if (compare_(items_[currChild], items_[extremeChild])) {
				extremeChild = currChild;
			}
		}
	}
  // return if item at idx and extremeChild indices are the same 
  // thus no swapping necessary 
  if (items_[idx] == items_[extremeChild]) {
    return;
  }
  // runs if current idx should be swapped with best child 
	if (compare_(items_[extremeChild], items_[idx])) {
		// swap best child and current idx value 
    T temp = items_[idx];
		items_[idx] = items_[extremeChild];
		items_[extremeChild] = temp;
    // recursive call for index where idx value is now located
		heapify_(extremeChild);
	}
}

#endif