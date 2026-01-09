/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:38:13 by francesca         #+#    #+#             */
/*   Updated: 2025/12/18 12:40:27 by francesca        ###   ########.fr       */
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

// A constructor that takes a constant integer as a parameter
Fixed::Fixed(const int _value) : _rawBits(_value << _fractionalBits) {
    std::cout << GREEN << "Integer constructor called" << RESET << std::endl;
}

// A constructor that takes a constant floating-point number
Fixed::Fixed (const float value): _rawBits(static_cast<int>(roundf(value * (1 << _fractionalBits))))
{
    std::cout << GREEN << "Float constructor called" << RESET << std::endl;
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

// Converts the fixed-point value to a floating-point value.
float Fixed::toFloat( void ) const{
    return static_cast<float>(this->_rawBits) / (1 << _fractionalBits);
}

int Fixed::toInt( void ) const{
    return (this->_rawBits >> _fractionalBits);
}

// serve per poter scrivere:
// Fixed a(42.42f);
// std::cout << a << std::endl;
// e far sì che a venga stampato in modo “sensato”  come float.
// Senza questo overload, il compilatore non sa cosa vuol dire << a per un oggetto di tipo Fixed.
std::ostream& operator<<(std::ostream& os, Fixed const& fx)
{
    os << fx.toFloat();
    return os;
}


