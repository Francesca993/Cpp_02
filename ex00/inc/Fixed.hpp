/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:06:17 by francesca         #+#    #+#             */
/*   Updated: 2025/12/18 10:24:20 by francesca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef FIXED_HPP
# define FIXED_HPP

//–––––––––––––––––––––––––––––
// Colors for Output
// –––––––––––––––––––––––––––––
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RED "\033[31m"
# define RESET "\033[0m"
# define BLUE "\033[0;34m"

class Fixed{
    private:
    int _rawBits;
    static const int _fractionalBits;
    
    public:
    Fixed(); // Default
    Fixed(const Fixed& other);      // copy ctor
    Fixed& operator=(const Fixed& other); // copy assign
    ~Fixed();
    int getRawBits( void ) const; // returns the raw value of the fixed-point value.
    void setRawBits( int const raw ); // sets the raw value of the fixed-point number.
};

#endif