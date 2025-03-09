/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:47:21 by lbrusa            #+#    #+#             */
/*   Updated: 2024/10/29 17:30:20 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>

class SpanFullException: public std::exception {
	public:
		virtual const char* what() const throw() {
			return "Error: class Span is full ";
		}
};

class SpanEmptyException: public std::exception {
	public:
		virtual const char* what() const throw() {
			return "Error: class Span has not enough elements";
		}
};

class Span {
	public:
		Span(unsigned int N);
		~Span();
		Span(const Span& copy);
		Span& operator=(const Span& assign);

		void addNumber(int number);
		void addSequence(const std::vector<int>& other);
		int shortestSpan() const;
		int longestSpan() const;

	private:
		const unsigned int N;
		std::vector<int> numbers;
};

#endif