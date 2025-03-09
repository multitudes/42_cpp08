/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:13:22 by lbrusa            #+#    #+#             */
/*   Updated: 2024/10/29 17:11:59 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "easyfind.hpp"
#include <list>
#include <vector>
#include <deque>
#include <set>


/**
 * The subject mention we dont need to handle associative containers.
 * These are for the record the key value pairs.    
 * std::map ,std::set, std::multimap, std::multiset, std::unordered_map, 
 * std::unordered_set, std::unordered_multimap, std::unordered_multiset
 * 
*/
int main() {
	
	std::vector<int> vec;
	for (int i = 0; i < 10; i++) {
		vec.push_back(i);
	}
	
	std::vector<int>::const_iterator it = easyfind(vec, 5);
	if (it != vec.end()) {
		std::cout << "Found: " << *it << std::endl;
	} else {
		std::cout << "Not found" << std::endl;
	}
	
	// btw: Dereferencing vec.end() is undefined behavior.
	// we just compare to it. cannot print it to console either
	// it is one past the last value of the vector
	// can only compare 
	std::vector<int>::const_iterator it2 = easyfind(vec, 42);
	if (it2 != vec.end()) {
		std::cout << "Found: " << *it2 << std::endl;
	} else {
		std::cout << "Not found" << std::endl;
	}
	
     //with differnent containers
	std::list<int> lst;
	for (int i = 0; i < 10; i++) {
		lst.push_back(i);
	}
    std::list<int>::const_iterator it3 = easyfind(lst, 3);
    if (it3 != lst.end()) {
        std::cout << "Found: " << *it3 << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }


    std::deque<int> deq;
	for (int i = 0; i < 10; i++) {
		deq.push_back(i);
	}
    std::deque<int>::const_iterator it4 = easyfind(deq, 3);
    if (it4 != deq.end()) {
        std::cout << "Found: " << *it4 << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

	std::set<int> s;
	for (int i = 0; i < 10; i++) {
		s.insert(i);
	}
    std::set<int>::const_iterator it6 = easyfind(s, 3);
    if (it6 != s.end()) {
        std::cout << "Found: " << *it6 << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

	// unordered set not avail in cpp98
	// std::unordered_set<int> us = {1, 2, 3, 4, 5};
    // std::unordered_set<int>::const_iterator it7 = easyfind(us, 3);
    // if (it7 != us.end()) {
    //     std::cout << "Found: " << *it7 << std::endl;
    // } else {
    //     std::cout << "Not found" << std::endl;
    // }
	

	return 0;
};


/*
why this gives an error when i have a non-const reference in the easyfind function
template <typename T>
typename std::vector<T>::const_iterator easyfind(const std::vector<T>& container, T& value) {
    return std::find(container.begin(), container.end(), value);
}

std::vector<double>::const_iterator it3 = easyfind(vec2, 5);

lvalues vs rvalues.
In C++, an lvalue (locator value) refers to an object that occupies some identifiable 
location in memory (i.e., it has an address). 
An rvalue (read value) is a temporary object that does not have a persistent memory location.

When you pass an argument to a function, you can pass it by value, by reference, 
or by const reference. Passing by value makes a copy of the argument, passing by 
reference allows the function to modify the original argument, and passing by 
const reference allows the function to read the original argument without modifying it.

In your original easyfind function, the second parameter was a non-const reference (T&). 
This means the function could only accept lvalues (objects with a persistent memory location). However, when you pass a literal or a temporary object (like 5), it is an rvalue, which cannot be bound to a non-const reference.
*/