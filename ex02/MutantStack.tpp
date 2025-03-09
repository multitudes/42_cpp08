/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:44:43 by lbrusa            #+#    #+#             */
/*   Updated: 2024/10/30 11:22:03 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

template <typename T>
MutantStack<T>::MutantStack() : std::stack<T>() {}

template <typename T>
MutantStack<T>::~MutantStack() {}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack& copy) : std::stack<T>(copy) {}

template <typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack& assign) {
	if (this != &assign) {
		std::stack<T>::operator=(assign);
	}
	return *this;
}

/**
 * Iterator functions
 * 
 * The iterator functions are used to iterate through the container.
 * I have const and non-const versions of the functions to cover both cases.
 */
template <typename T>
typename std::stack<T>::container_type::iterator MutantStack<T>::begin() {
    return this->c.begin();
}

template <typename T>
typename std::stack<T>::container_type::iterator MutantStack<T>::end() {
    return this->c.end();
}

template <typename T>
typename std::stack<T>::container_type::const_iterator MutantStack<T>::begin() const {
    return this->c.begin();
}

template <typename T>
typename std::stack<T>::container_type::const_iterator MutantStack<T>::end() const {
    return this->c.end();
}

/**
 * Helper function to get a reference to the container
 */
template <typename T>
typename std::stack<T>::container_type& MutantStack<T>::c_ref() {
    return this->c;
}

/**
 * Reverse iterators
 * 
 * The reverse iterators are used to iterate through the container in reverse order.
 * I include them here for completeness
 */
template <typename T>
typename std::stack<T>::container_type::reverse_iterator MutantStack<T>::rbegin() {
	return this->c.rbegin();
}

template <typename T>
typename std::stack<T>::container_type::reverse_iterator MutantStack<T>::rend() {
	return this->c.rend();
}

template <typename T>
typename std::stack<T>::container_type::const_reverse_iterator MutantStack<T>::rbegin() const {
	return this->c.rbegin();
}

template <typename T>
typename std::stack<T>::container_type::const_reverse_iterator MutantStack<T>::rend() const {
	return this->c.rend();
}
// // Explicit template instantiation
// template class MutantStack<int>; // Add other types as needed