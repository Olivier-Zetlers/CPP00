/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <ozetlers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 01:04:01 by ozetlers          #+#    #+#             */
/*   Updated: 2026/08/08 16:47:24 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

#include <iomanip>
#include <iostream>
#include <string>

#define COLUMN_WIDTH 10

static std::string formatColumn(std::string text)
{
	if (text.length() <= COLUMN_WIDTH)
		return (text);
	else
		return (text.substr(0, COLUMN_WIDTH - 1) + ".");
}

static void printColumn(std::string text)
{
	std::cout << std::setw(COLUMN_WIDTH) << formatColumn(text);
}

static void printNameColumns(std::string first, std::string second, std::string third)
{
	std::cout << "|";
	printColumn(first);
	std::cout << "|";
	printColumn(second);
	std::cout << "|";
	printColumn(third);
	std::cout << std::endl;
}

static bool readField(std::string prompt, std::string *value)
{
	while (true)
	{
		std::cout << prompt << std::endl;
		if (!std::getline(std::cin, *value))
			return (false);
		if (!value->empty())
			return (true);
		std::cout << "This field cannot be empty." << std::endl;
	}
}

PhoneBook::PhoneBook()
	: contactCount_(0), nextIndex_(0)
{
}

void PhoneBook::storeContact(Contact contact)
{
	contacts_[nextIndex_] = contact;
	nextIndex_ = (nextIndex_ + 1) % MAX_CONTACTS;
	if (contactCount_ < MAX_CONTACTS)
		contactCount_++;
}

bool PhoneBook::addContact()
{
	std::string first;
	std::string last;
	std::string nickname;
	std::string phone;
	std::string secret;

	if (!readField("First name:", &first))
		return (false);
	if (!readField("Last name:", &last))
		return (false);
	if (!readField("Nickname:", &nickname))
		return (false);
	if (!readField("Phone number:", &phone))
		return (false);
	if (!readField("Darkest secret:", &secret))
		return (false);
	storeContact(Contact(first, last, nickname, phone, secret));
	std::cout << "Contact added." << std::endl;
	return (true);
}

void PhoneBook::displayContactList() const
{
	int index;

	std::cout << std::setw(COLUMN_WIDTH) << "index";
	printNameColumns("first name", "last name", "nickname");
	index = 0;
	while (index < contactCount_)
	{
		std::cout << std::setw(COLUMN_WIDTH) << index;
		printNameColumns(contacts_[index].getFirstName(), contacts_[index].getLastName(), contacts_[index].getNickname());
		index++;
	}
}

void PhoneBook::displayContact(int index) const
{
	std::cout << "First name: " << contacts_[index].getFirstName() << std::endl;
	std::cout << "Last name: " << contacts_[index].getLastName() << std::endl;
	std::cout << "Nickname: " << contacts_[index].getNickname() << std::endl;
	std::cout << "Phone number: " << contacts_[index].getPhoneNumber() << std::endl;
	std::cout << "Darkest secret: " << contacts_[index].getDarkestSecret() << std::endl;
}

bool PhoneBook::searchContacts() const
{
	std::string input;

	if (contactCount_ == 0)
	{
		std::cout << "The phonebook is empty." << std::endl;
		return (true);
	}
	displayContactList();
	std::cout << "Index to display:" << std::endl;
	if (!std::getline(std::cin, input))
		return (false);
	if (input.length() == 1 && input[0] >= '0' && input[0] < '0' + contactCount_)
		displayContact(input[0] - '0');
	else
		std::cout << "Invalid index." << std::endl;
	return (true);
}
