/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:13:13 by francesca         #+#    #+#             */
/*   Updated: 2025/12/18 12:40:12 by francesca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int Fixed::_fractionalBits = 8;

Fixed::Fixed() : _rawBits(0) {
    std::cout << GREEN << "Default constructor called" << RESET << std::endl;
}

Fixed::Fixed(const Fixed& other) : _rawBits(other._rawBits) {
    std::cout << YELLOW << "Copy constructor called" << RESET << std::endl;
}

Fixed& Fixed::operator=(const Fixed& other)
{
    std::cout << BLUE << "Copy assignment operator called" << RESET << std::endl;
    if (this != &other)
    {
        this->_rawBits = other._rawBits;
    }
    return (*this);
}

Fixed::~Fixed(){
    std::cout << RED << "Destructor called" << RESET << std::endl;
}

// returns the raw value of the fixed-point value.
int Fixed::getRawBits( void ) const{
    std::cout << YELLOW << "getRawBits member function called" << RESET << std::endl;
    return(this->_rawBits);
}

void Fixed::setRawBits( int const raw ){
    std::cout << YELLOW << "setRawBits member function called" << RESET << std::endl;
    this->_rawBits = raw;
}
