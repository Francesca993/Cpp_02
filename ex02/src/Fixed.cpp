/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:38:13 by francesca         #+#    #+#             */
/*   Updated: 2026/01/09 11:44:58 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int Fixed::_fractionalBits = 8;

//Constructor Default
Fixed::Fixed() : _rawBits(0) {
}

// Copy constructor
Fixed::Fixed(const Fixed& other) : _rawBits(other._rawBits) {
}

//Copy assignment operator
Fixed& Fixed::operator=(const Fixed& other)
{
    if (this != &other)
    {
        this->_rawBits = other._rawBits;
    }
    return (*this);
}

// Destructor
Fixed::~Fixed(){
}

// A constructor that takes a constant integer as a parameter
Fixed::Fixed(const int _value) : _rawBits(_value << _fractionalBits) {
}

// A constructor that takes a constant floating-point number
Fixed::Fixed (const float value): _rawBits(static_cast<int>(roundf(value * (1 << _fractionalBits)))){
}

// getRawBits returns the raw value of the fixed-point value.
int Fixed::getRawBits( void ) const{
    return(this->_rawBits);
}

void Fixed::setRawBits( int const raw ){
    this->_rawBits = raw;
}

// Converts the fixed-point value to a floating-point value.
float Fixed::toFloat( void ) const{
    return static_cast<float>(this->_rawBits) / (1 << _fractionalBits);
}

// Converts the fixed-point value to an integer value.
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


// ----- aritmetica (ritornano Fixed per valore) -------
Fixed Fixed::operator+(Fixed const& other) const
{
    Fixed res;
    res.setRawBits(this->_rawBits + other._rawBits);
    return(res);
}

Fixed Fixed::operator-(Fixed const& other) const
{
    Fixed res;
    res.setRawBits(this->_rawBits - other._rawBits);
    return(res);
}

Fixed Fixed::operator*(Fixed const& other) const
{
    long long val;
    Fixed res;
    
    val = (static_cast<long long>(this->_rawBits) * static_cast<long long>(other._rawBits)) >> _fractionalBits;
    res.setRawBits(static_cast<int>(val));
    return(res);
}

Fixed Fixed::operator/(Fixed const& other) const
{
    long long val;
    Fixed res;
    val = ((long long)this->_rawBits << _fractionalBits) / other._rawBits;
    res.setRawBits(static_cast<int>(val));
    return(res);
}

// ------- pre/post increment/decrement --------
/*
++a	incrementa → usa	Fixed&
a++	usa → incrementa	Fixed
--a	decrementa → usa	Fixed&
a--	usa → decrementa	Fixed
In un fixed-point, l’operatore ++ incrementa il valore di epsilon,
cioè della minima quantità rappresentabile, non di 1.0.
*/

Fixed& Fixed::operator++()
{
    this->_rawBits += 1;
    return *this;
}

Fixed& Fixed::operator--()
{
    this->_rawBits -= 1;
    return *this;
}

Fixed  Fixed::operator++(int)
{
    Fixed temp(*this);
    this->_rawBits += 1;
    return (temp);
}

Fixed  Fixed::operator--(int)
{
    Fixed temp(*this);
    this->_rawBits -= 1;
    return (temp);
}

// ------ Confronti --------
bool Fixed::operator>(const Fixed& other) const
{
    if (this->_rawBits > other._rawBits)
        return(true);
    else
        return(false);
}

bool Fixed::operator<(const Fixed& other) const
{
    return this->_rawBits < other._rawBits;
}

bool Fixed::operator!=(const Fixed& other) const
{
    if (this->_rawBits != other._rawBits)
        return(true);
    else
        return(false);
}

bool Fixed::operator>=(const Fixed& other) const
{
    return this->_rawBits >= other._rawBits;
}

bool Fixed::operator<=(const Fixed& other) const
{
    return this->_rawBits <= other._rawBits;
}
    
bool Fixed::operator==(const Fixed& other) const
{
    return this->_rawBits == other._rawBits;
}

// ------ min/max (4 overload) -------
Fixed& Fixed::min(Fixed& a, Fixed& b)
{
    if (a < b)
        return(a);
    else
        return (b);
}
Fixed& Fixed::max(Fixed& a, Fixed& b)
{
    if (a > b)
        return(a);
    else
        return (b);
}

Fixed const& Fixed::min(Fixed const& a, Fixed const& b)
{
    if (a < b)
        return(a);
    else
        return (b);
}

Fixed const& Fixed::max(Fixed const& a, Fixed const& b)
{
    if (a > b)
        return(a);
    else
        return (b);
}
