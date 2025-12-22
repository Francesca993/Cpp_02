/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:32:11 by francesca         #+#    #+#             */
/*   Updated: 2025/12/18 12:38:53 by francesca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

//–––––––––––––––––––––––––––––
// Colors for Output
// –––––––––––––––––––––––––––––
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RED "\033[31m"
# define RESET "\033[0m"
# define BLUE "\033[0;34m"
#include <cmath>
#include <iostream>

class Fixed{
    private:
    int _rawBits;
    static const int _fractionalBits;
    
    public:
    Fixed(); // Default
    Fixed(const int _value); // A constructor that takes a constant integer as a parameter
    Fixed(const float _value); // A constructor that takes a constant floating-point number as a parameter.
    Fixed(const Fixed& other);      // copy ctor
    Fixed& operator=(const Fixed& other); // copy assign
    ~Fixed();
    int getRawBits( void ) const; // returns the raw value of the fixed-point value.
    void setRawBits( int const raw ); // sets the raw value of the fixed-point number.
    float toFloat( void ) const; // Converts the fixed-point value to a floating-point value.
    int toInt( void ) const; // Converts the fixed-point value to an integer value.
};

std::ostream& operator<<(std::ostream& os, Fixed const& fx);

#endif