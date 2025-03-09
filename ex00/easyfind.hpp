/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:36:56 by lbrusa            #+#    #+#             */
/*   Updated: 2024/10/29 16:46:24 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <vector>
#include <algorithm> 

/**
 * Iterators in c++
 * 
 * An iterator is a generalized pointer, allowing to move through 
 * the container's elements one by one. They can be incrementes like pointers with ++ and --
 *  
 * Returning a const_iterator aligns with the principle of immutability, 
 * where data is treated as read-only to enhance code safety 
 * and avoid accidental modifications
 * 
 * We use typename again here to indicate that T::const_iterator is a type within T.
 * typename T::const_iterator
 * This part specifies the return type of the function. Here, 
 * typename is used to indicate that T::const_iterator is a type. 
 * This is necessary because T is a template parameter, 
 * and the compiler needs to know that const_iterator is a type within T.
 * 
 */ 
template <typename T>
typename T::const_iterator easyfind(const T& container, int value) {
    return std::find(container.begin(), container.end(), value);
}



#endif