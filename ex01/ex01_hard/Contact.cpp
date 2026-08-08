/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <ozetlers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 01:03:19 by ozetlers          #+#    #+#             */
/*   Updated: 2026/08/02 01:03:29 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

// The std::string members need no explicit initializers: a member of
// class type is default-constructed when the initialization list omits
// it.
Contact::Contact()
{
}

Contact::Contact(const std::string &firstName, const std::string &lastName,
	const std::string &nickname, const std::string &phoneNumber,
	const std::string &darkestSecret)
	: firstName_(firstName),
	  lastName_(lastName),
	  nickname_(nickname),
	  phoneNumber_(phoneNumber),
	  darkestSecret_(darkestSecret)
{
}

const std::string &Contact::getFirstName() const
{
	return firstName_;
}

const std::string &Contact::getLastName() const
{
	return lastName_;
}

const std::string &Contact::getNickname() const
{
	return nickname_;
}

const std::string &Contact::getPhoneNumber() const
{
	return phoneNumber_;
}

const std::string &Contact::getDarkestSecret() const
{
	return darkestSecret_;
}
