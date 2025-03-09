/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:13:22 by lbrusa            #+#    #+#             */
/*   Updated: 2024/10/29 17:32:22 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Span.hpp"
#include <cstdlib>
#include <ctime>


int main() {
	Span span = Span(5);
	span.addNumber(5);
	span.addNumber(9);
	span.addNumber(17);
	span.addNumber(3);
	span.addNumber(11);

	try {
		span.addNumber(11);
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << span.longestSpan() << std::endl;
	int shortest = span.shortestSpan();
	std::cout << "shortest "<< shortest << std::endl;

	Span span2 = Span(0);
	try {
		shortest = span2.shortestSpan();
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	try {
		shortest = span2.shortestSpan();
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "--------- from the subject -------" << std::endl;
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
		
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	

	std::cout << "--------- test 10000 -------" << std::endl;

	// Seed the random number generator
	srand(static_cast<unsigned int>(time(NULL)));

	Span sp2 = Span(100000);
	std::vector<int> v(100000, 0);
	for (std::vector<int>::size_type i = 0; i < v.size(); ++i) {
		// this random function will return a random int between 0  and rand_max
		v[i] = rand() % 100000 ; // Generate a random number between 0 and 99999
		// std::cout << v[i] << std::endl;
	}

	// here I add a whole vector to the span
	sp2.addSequence(v);

	// it is easier to get a shortest span of 0 because it is likely
	// that i get at least two numbers which are the same
	// to change this i need to take fewer numbers over a bigger number
	std::cout << "shortest : " << sp2.shortestSpan() << std::endl;
	std::cout << "longest : "<< sp2.longestSpan() << std::endl;
	
	return 0;
};