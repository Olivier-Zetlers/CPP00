/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <ozetlers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 01:03:19 by ozetlers          #+#    #+#             */
/*   Updated: 2026/08/08 02:44:18 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

// The std::string members need no explicit initializers: a member of
// class type is default-constructed when the initialization list omits
// it.
Contact::Contact()
{
}

Contact::Contact(std::string firstName, std::string lastName,
	std::string nickname, std::string phoneNumber,
	std::string darkestSecret)
	: firstName_(firstName),
	  lastName_(lastName),
	  nickname_(nickname),
	  phoneNumber_(phoneNumber),
	  darkestSecret_(darkestSecret)
{
}

std::string Contact::getFirstName() const
{
	return firstName_;
}

std::string Contact::getLastName() const
{
	return lastName_;
}

std::string Contact::getNickname() const
{
	return nickname_;
}

std::string Contact::getPhoneNumber() const
{
	return phoneNumber_;
}

std::string Contact::getDarkestSecret() const
{
	return darkestSecret_;
}
