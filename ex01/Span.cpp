/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:47:18 by lbrusa            #+#    #+#             */
/*   Updated: 2024/10/29 17:28:00 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>

/**
 * constructor
 * 
 * @param N the number of elements
 * I initialize N which is my max number of elements and
 * numbers which is my vector of numbers but still empty
 */
Span::Span(unsigned int N) : N(N) {
	numbers.reserve(N);
}

/**
 * desstructor
 * 
 * There is no delete for vectors, so we can just clear the vector
 */
Span::~Span() {
	numbers.clear();
}

/**
 * copy constructor
 * 
 * @param copy the object to copy
 * the statement numbers = copy.numbers; performs a deep copy of the numbers vector. 
 * In C++, the assignment operator for std::vector copies all the elements from the 
 * source vector to the destination vector. This means that each element 
 * in the copy.numbers vector is copied to the numbers vector, 
 * resulting in two independent vectors with the same elements.
 */
Span::Span(const Span& copy) : N(copy.N) {
	numbers.reserve(N);
	numbers = copy.numbers;
}

/**
 * assignment operator
 * 
 * @param assign the object to assign
 * @return Span& the assigned object
 */
Span& Span::operator=(const Span& assign) {
	if (this != &assign) {
		numbers.reserve(assign.N);
        numbers = assign.numbers;
	}
	return *this;
}

/**
 * add a number to the list
 * 
 * @param number the number to add
 */
void Span::addNumber(int number) {
	if (numbers.size() < N) {
		numbers.push_back(number);
	} else {
		throw SpanFullException();
	}
}

/**
 * add a range of numbers to the list
 * 
 * @param begin the beginning of the range
 * @param end the end of the range
 */
void Span::addSequence(const std::vector<int>& other) {
    if (numbers.size() + other.size() <= N) {
        numbers.insert(numbers.end(), other.begin(), other.end());
    } else {
        throw SpanFullException();
    }
}

/**
 * get the shortest span
 * 
 * @return unsigned int the shortest span
 * in an array of numbers. the logic is i check the span between each number and all others
 * and return the smallest - ex 5 9 17 3 11 will give 2
 */
int Span::shortestSpan() const {
	if (numbers.size() < 2) {
		throw SpanEmptyException();
	}
	std::vector<int> sorted_numbers = numbers;
	std::sort(sorted_numbers.begin(), sorted_numbers.end());
	std::vector<int> differences(sorted_numbers.size());
	std::adjacent_difference(sorted_numbers.begin(), sorted_numbers.end(), differences.begin()); 
	differences.erase(differences.begin());
	return *std::min_element(differences.begin() , differences.end());
}

/**
 * get the longest span
 */
int Span::longestSpan() const {
	if (numbers.size() < 2) {
		throw SpanEmptyException();
	}
	int max =  *std::max_element(numbers.begin(), numbers.end());
	int min =  *std::min_element(numbers.begin(), numbers.end());
	return max - min;
}