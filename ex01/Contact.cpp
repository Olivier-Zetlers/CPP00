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

Contact::Contact()
	: firstName_(),
	  lastName_(),
	  nickname_(),
	  phoneNumber_(),
	  darkestSecret_()
{
}

void Contact::setFirstName(const std::string &firstName)
{
	firstName_ = firstName;
}

void Contact::setLastName(const std::string &lastName)
{
	lastName_ = lastName;
}

void Contact::setNickname(const std::string &nickname)
{
	nickname_ = nickname;
}

void Contact::setPhoneNumber(const std::string &phoneNumber)
{
	phoneNumber_ = phoneNumber;
}

void Contact::setDarkestSecret(const std::string &darkestSecret)
{
	darkestSecret_ = darkestSecret;
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
