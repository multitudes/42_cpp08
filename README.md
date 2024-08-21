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
