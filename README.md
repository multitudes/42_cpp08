# 42_cpp08

Templated containers, iterators, algorithms.

In this module we are allowed to use Containers (vector/list/map/and so forth) and the Algorithms (defined in header <algorithm>).

## ex00 - easyfind
>Write a function template easyfind that accepts a type T. It takes two parameters.  
The first one has type T and the second one is an integer.
Assuming T is a container of integers,

### what is a container of integers?
In C++98, std::vector<int> is a container that represents a dynamic array of integers. It's part of the C++ Standard Template Library (STL).
- It can automatically resize itself
- Elements can be accessed directly using their index.
- Provides operations like push_back, pop_back, insert, erase, and size.

### implementation

How would we code this function without templates? we would use the vector container and the `find` algorithm from the <algorithm> header.  
```cpp
#include <vector>
#include <algorithm>

std::vector<int>::const_iterator easyfind(const std::vector<int>& container, int value) {
	return std::find(container.begin(), container.end(), value);
}

```
`std::find` iterates over the range specified by the iterators and returns an iterator to the first element that matches the value. If the value is not found, it returns `container.end()`.

or using an iterator... but I think the previous example is more concise: 
```cpp
std::vector<int>::const_iterator easyfind_int(const std::vector<int>& container, int value) {
    for (std::vector<int>::const_iterator it = container.begin(); it != container.end(); ++it) {
        if (*it == value) {
            return it;
        }
    }
    return container.end();
}
```
#### Using templates
So now we can use templates to make this function work with any type.  Using find:
```cpp
template <typename T>
typename std::vector<T>::const_iterator easyfind(const std::vector<T>& container, const T& value) {
    return std::find(container.begin(), container.end(), value);
}
```
or using an iterator... :
```cpp
template <typename T>
typename std::vector<T>::const_iterator easyfind(const std::vector<T>& container, const T& value) {
    for (typename std::vector<T>::const_iterator it = container.begin(); it != container.end(); ++it) {
        if (*it == value) {
            return it;
        }
    }
    return container.end();
}
```

breaking it down:
`typename std::vector<T>::const_iterator` is the return type. It's an iterator that points to an element within the std::vector<T> container

Parameters:
- `const std::vector<T>& container`: A reference to a constant `std::vector` of type `T`. This allows the function to work with different `std::vector` instances without copying them.
- `const T& value`: The value to search for within the container.



### what is `container.end()`?
`container.end()` returns an iterator pointing to the element one past the last element in the container. It cannot be dereferenced. It is commonly used to indicate the end of a range when searching for elements in a container. You can check if a container is empty by comparing container.begin() to container.end(). If they are equal, the container is empty.  

### what are associative containers
Associative containers in C++ are data structures that store elements in a specific order, typically based on a key. This allows for efficient searching, insertion, and deletion of elements based on their keys.

Here are the main types of associative containers in C++:  
- std::map: Stores key-value pairs, where the keys are unique and must be comparable. The elements are sorted based on the keys.  
- std::unordered_map: Similar to std::map, but elements are not sorted. Instead, they are stored using a hash table for efficient lookup.  
- std::set: Stores unique elements, sorted based on their values.  
- std::unordered_set: Similar to std::set, but elements are not sorted and are stored using a hash table.  

## and what is a vector behind the scenes?
In C++98, std::vector is a template class that represents a dynamic array. The template parameters are:

T: The type of elements stored in the vector.
Allocator: The allocator type used for memory management, which defaults to std::allocator<T>.
The following declaration:


Example:
```cpp
  std::vector<int, std::allocator<int> > numbers = std::vector<int, 

```
is equivalent to:

```cpp
  std::allocator<int> >();
```
The first one shows the template arguments explicitly.
because `std::allocator<int>` is the default allocator for `std::vector<int>`.` The explicit form is rarely used unless you need to specify a custom allocator.

### Common Methods and Properties of std::vector

#### Capacity and Size:

- size(): Returns the number of elements in the vector.
-capacity(): Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
-empty(): Checks whether the container is empty.
-resize(n): Resizes the container so that it contains n elements.
-reserve(n): Requests that the vector capacity be at least enough to contain n elements.

#### Element Access:

- operator[](index): Accesses the element at the specified position.
- at(index): Accesses the element at the specified position with bounds checking.
- front(): Returns a reference to the first element.
- back(): Returns a reference to the last element.
- data(): Returns a direct pointer to the memory array used internally by the vector.

#### Modifiers:

- push_back(value): Adds an element to the end.
- pop_back(): Removes the last element.
- insert(position, value): Inserts elements at the specified position.
- erase(position): Removes elements from the specified position.
- clear(): Removes all elements.
- swap(other): Swaps the contents with another vector.

#### Concept of Iterators
Iterators are objects that point to elements within a container and allow traversal of the container. They are similar to pointers and provide a way to access and manipulate elements.

#### Types of Iterators:
- begin(): Returns an iterator to the first element.
- end(): Returns an iterator to the element following the last element.
- rbegin(): Returns a reverse iterator to the last element.
- rend(): Returns a reverse iterator to the element preceding the first element.

#### Adjacent Values
Adjacent values refer to elements that are next to each other in a container. Iterators can be used to access and manipulate these values. For example, you can use iterators to find adjacent elements that satisfy a certain condition.

Example:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Accessing elements
    std::cout << "First element: " << numbers.front() << std::endl;
    std::cout << "Last element: " << numbers.back() << std::endl;

    // Iterating over elements
    std::cout << "Elements: ";
    for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Finding adjacent values
    std::vector<int>::iterator it = std::adjacent_find(numbers.begin(), numbers.end());
    if (it != numbers.end()) {
        std::cout << "Found adjacent values: " << *it << " and " << *(it + 1) << std::endl;
    } else {
        std::cout << "No adjacent values found" << std::endl;
    }

	//sort
	std::sort(numbers.begin(), numbers.end());
    return 0;
}
```

A cool thing is to look for adjacent distances in one vector and store them in another vector.
```cpp
std::vector<int> find_adjacent_differences(const std::vector<int>& numbers) {
    std::vector<int> differences;

    std::vector<int>::const_iterator it = std::adjacent_find(numbers.begin(), numbers.end());
    while (it != numbers.end()) {
        differences.push_back(std::abs(*it - *(it - 1)));
        it = std::adjacent_find(it + 1, numbers.end());
    }

    return differences;
}
```

The same thing can be done with adjacent_difference algorithm:
```cpp
std::vector<int> find_adjacent_differences(const std::vector<int>& numbers) {
	std::vector<int> differences(numbers.size());

	std::adjacent_difference(numbers.begin(), numbers.end(), differences.begin());
	differences.erase(differences.begin());

	return differences;
}
```

## Ex01 - span

We can use the properties of the vector to create a span class which will contains an array of ints and return the largest and shortest spans between any value of the array.

## Ex02 - Mutantstack

### what is a stack container?
The `std::stack` container in C++ is a simple data structure that follows the Last-In-First-Out (LIFO) principle. This means that the last element added to the stack is the first one to be removed. It's often used to implement functions like undo/redo, backtracking algorithms, or expression evaluation.  
### Key characteristics of std::stack:
- LIFO order: Elements are added and removed in a LIFO manner.
- Template-based: std::stack is a template container, so you can use it with different data types.
- Adapter: It's an adapter container, meaning it is built on top of another container (usually `std::deque` or `std::vector`) to provide the stack interface.

Operations:
- push(value): Adds an element to the top of the stack.
- top(): Returns a reference to the top element of the stack without removing it.
- pop(): Removes the top element from the stack.
- empty(): Returns true if the stack is empty, false otherwise.
- size(): Returns the number of elements in the stack.

Example:
```cpp
#include <stack>
#include <iostream>

int main() {
    std::stack<int> myStack;

    // Push elements onto the stack
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    // Access the top element
    std::cout << "Top element: " << myStack.top() << std::endl;

    // Pop elements from the stack
    myStack.pop();
    myStack.pop();

    // Check if the stack is empty
    if (myStack.empty()) {
        std::cout << "Stack is empty." << std::endl;
    } else {
        std::cout << "Stack is not empty." << std::endl;
    }

    return 0;  
}
```
### The `std::stack` member functions
Constructors:
- std::stack(): Constructs an empty stack.
- std::stack(const Container& c): Constructs a stack from a container (e.g., std::vector, std::deque).
- std::stack(Container&& c): Constructs a stack from a movable container.

Modifiers:
- void push(const T& value): Pushes an element onto the top of the stack.
- void pop(): Removes the top element from the stack.
- void top(): Returns a reference to the top element of the stack without removing it.
- void swap(std::stack& other): Exchanges the contents of two stacks.

Capacity:
- bool empty(): Returns true if the stack is empty, false otherwise.
- size_type size(): Returns the number of elements in the stack.


### The `std::stack` container adapter

The `std::stack` container adapter is a simple wrapper around a container that provides a stack interface. The underlying container can be specified as a template parameter, but the default is `std::deque`. In the same way we can inherit from the stack class and create a new class that will have the same properties as the stack but with some additional methods. In particular we will add the `begin()` and `end()` methods that will return the iterators to the beginning and end of the stack.
The begin() and end() functions in the MutantStack class provide iterators that allow you to traverse the elements of the stack. These iterators are essentially pointers that point to the current element in the stack.

- begin(): Returns an iterator pointing to the first element (top) of the stack.
- end(): Returns an iterator pointing to one past the last element of the stack.

You can use these iterators in a loop to access and manipulate the elements of the stack
The c_ref() function is used by the 	begin() and end() functions to access the underlying container and retrieve its iterators. By returning a reference to the container, the MutantStack class avoids making a copy of the container, which can be more efficient.

This is the class definition in canonical form. Note that I have access to all stack methods and I can add new methods to the class. Also it is a template class so I can use it with any type of data.

```cpp
template <typename T>
class MutantStack: public std::stack<T> {
	public:
		MutantStack();
		~MutantStack();
		MutantStack(const MutantStack& copy);
		MutantStack& operator=(const MutantStack& assign);

		typedef typename std::stack<T>::container_type::iterator iterator;
		iterator begin();
		iterator end();

	private:
		typename std::stack<T>::container_type& c_ref();
};
```

We use `typedef` in our class. 
typedef - creates an alias that can be used anywhere in place of a (possibly complex) type name. Example:
```cpp
typedef int myInt;
myInt x = 5;

// the following two objects have the same type
unsigned long l1;
ulong l2;
```	
Structs with and without typedef

```cpp
typedef struct Node
{
    struct listNode* next; // declares a new (incomplete) struct type named listNode
} listNode;
```
Here typedef struct Node { ... } listNode; creates an alias listNode for struct Node.  
Node is the name of the structure type.  
listNode is now an alias for struct Node.
```cpp
struct Node n1;
listNode n2;
```
but without typedef it looks almost the same but:
```cpp
struct Node
{
	struct listNode* next; // declares a new (incomplete) struct type named listNode
} listNode;
```
struct Node { ... } listNode; declares a structure type named Node and also declares a variable listNode of type struct Node.  
Node is the name of the structure type.  
listNode is a variable of type struct Node.  
```cpp
struct Node n1;
struct Node n2;
```
Also you can use typedef to create an alias for an unnamed (anonymous) struct. 
```cpp
typedef struct
{
	int x;
	int y;
} Point;
```
Here typedef struct { ... } Point; creates an alias Point for an unnamed struct.

## typedef typename
I use `typedef typename`  to create an alias for a nested type within a template. It instructs the compiler that the following name is a type, not a value. Since I am using an alias for 
`std::stack<T>::container_type::iterator` and my alias is `iterator`.
This nested type path refers to the iterator type used within the `std::stack<T>::container`. 
You will be surprised that actually the underlying container of the stack is a deque. 

You can customize the container used by `std::stack` by providing a different container type as a template argument. For example, to use a `std::vector` instead of a `std::deque`:
```cpp
std::stack<int, std::vector<int>> myStack;
```

### The `std::stack` container adapter
The `std::stack` container adapter is a simple wrapper around a container that provides a stack interface. The underlying container can be specified as a template parameter, but the default is `std::deque`.
An example with both:
```cpp
#include <stack>
#include <vector>
#include <deque>
#include <iostream>

int main() {
    // Default declaration using std::deque
    std::stack<int> defaultStack;
    defaultStack.push(1);
    defaultStack.push(2);
    defaultStack.push(3);

    std::cout << "Default stack (using std::deque): ";
    while (!defaultStack.empty()) {
        std::cout << defaultStack.top() << " ";
        defaultStack.pop();
    }
    std::cout << std::endl;

    // Custom container declaration using std::vector
    std::stack<int, std::vector<int>> vectorStack;
    vectorStack.push(4);
    vectorStack.push(5);
    vectorStack.push(6);

    std::cout << "Custom stack (using std::vector): ";
    while (!vectorStack.empty()) {
        std::cout << vectorStack.top() << " ";
        vectorStack.pop();
    }
    std::cout << std::endl;

    return 0;
}
```

### Look into the stack class in the STL
Here we can see the stack class in the STL. It is a template class that provides a simple interface for the stack data structure. The stack class is an adapter that wraps an underlying container (by default, std::deque) to provide stack functionality. The stack class does not define any iterators, as it is a simple container adapter that enforces the LIFO (Last-In-First-Out) behavior of a stack.

```cpp

  /**
   *  @brief  A standard container giving FILO behavior.
   *
   *  @ingroup sequences
   *
   *  @tparam _Tp  Type of element.
   *  @tparam _Sequence  Type of underlying sequence, defaults to deque<_Tp>.
   *
   *  Meets many of the requirements of a
   *  <a href="tables.html#65">container</a>,
   *  but does not define anything to do with iterators.  Very few of the
   *  other standard container interfaces are defined.
   *
   *  This is not a true container, but an @e adaptor.  It holds
   *  another container, and provides a wrapper interface to that
   *  container.  The wrapper is what enforces strict
   *  first-in-last-out %stack behavior.
   *
   *  The second template parameter defines the type of the underlying
   *  sequence/container.  It defaults to std::deque, but it can be
   *  any type that supports @c back, @c push_back, and @c pop_back,
   *  such as std::list, std::vector, or an appropriate user-defined
   *  type.
   *
   *  Members not found in @a normal containers are @c container_type,
   *  which is a typedef for the second Sequence parameter, and @c
   *  push, @c pop, and @c top, which are standard %stack/FILO
   *  operations.
  */
  template<typename _Tp, typename _Sequence = deque<_Tp> >
    class stack
    {
		...
	}
```

### how many containers in the STL?
Since we are talking about containers, let's see how many containers are in the STL.
#### Sequence Containers:  
std::vector  - A dynamic array that provides fast random access to elements.
std::deque  - A double-ended queue that supports fast insertion and deletion at both ends.
std::list  - A doubly linked list that supports fast insertion and deletion at any position.
std::array  - A fixed-size array that provides fast random access to elements.
std::string (specialized container for characters)  
#### Associative Containers  
std::set - An ordered associative container that stores unique elements.
std::multiset -  allows multiple elements to have the same value. It is similar to std::set, but unlike std::set, it allows for duplicate elements and they are sorted.
std::map - stores key-value pairs in a sorted order based on the keys. The sorting is typically done using a binary search tree, such as a Red-Black Tree, which provides logarithmic time complexity for most operations.
std::multimap - like map but allows for duplicate keys. Per key you access the values with dot notation.
#### Unordered Associative Containers
std::unordered_set - stores unique elements using a hash table.
std::unordered_multiset - allows for duplicate elements and uses a hash table for storage.
std::unordered_map - stores key-value pairs using a hash table.
std::unordered_multimap - allows for duplicate keys and uses a hash table for storage.
#### Container Adapters
std::stack - provides a LIFO (Last-In-First-Out) stack interface.
std::queue - provides a FIFO (First-In-First-Out) queue interface.
std::priority_queue - provides a priority queue interface.

##### A priority_queue 
is a container adapter in the C++ Standard Template Library (STL) that provides constant time lookup of the largest (by default) element. It is typically implemented as a binary heap. The priority_queue is a type of container adapter that provides a restricted subset of the functionality of a queue. It is similar to a queue, but elements are popped based on their priority. The priority_queue is typically implemented as a binary heap, which allows for efficient insertion and removal of elements based on their priority.
##### Common Operations:
push: Adds an element to the priority queue.
pop: Removes the highest priority element.
top: Accesses the highest priority element.
empty: Checks if the priority queue is empty.
size: Returns the number of elements in the priority queue.
