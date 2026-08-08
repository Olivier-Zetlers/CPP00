/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <ozetlers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 01:04:01 by ozetlers          #+#    #+#             */
/*   Updated: 2026/08/08 02:35:19 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

#include <iomanip>
#include <iostream>
#include <string>

// Rendered width of one column of the SEARCH listing, in characters.
const int COLUMN_WIDTH = 10;

// The helpers below read no PhoneBook state, so they are plain
// functions rather than member functions. As in C, static gives them
// internal linkage: they stay local to this file.

// Truncates to COLUMN_WIDTH characters, the last of which becomes a
// dot.
static std::string formatColumn(std::string text)
{
	if (text.length() <= COLUMN_WIDTH)
		return text;
	return text.substr(0, COLUMN_WIDTH - 1) + ".";
}

// The stream's default adjustment is right, so std::setw alone
// renders the cell right-aligned in a COLUMN_WIDTH-character field.
static void printColumn(std::string text)
{
	std::cout << std::setw(COLUMN_WIDTH) << formatColumn(text);
}

// Prints the three name columns of one listing row, each preceded by
// its pipe separator, then ends the line. The caller prints the
// index cell first.
static void printNameColumns(std::string first, std::string second,
	std::string third)
{
	std::cout << "|";
	printColumn(first);
	std::cout << "|";
	printColumn(second);
	std::cout << "|";
	printColumn(third);
	std::cout << std::endl;
}

// Prompts until a non-empty line is entered, and stores it through
// value. Returns false only at end-of-file: the subject requires that
// a saved contact has no empty field, so an empty entry is reported
// and re-prompted here, and is never visible to the caller.
static bool readRequiredField(std::string prompt, std::string *value)
{
	while (true)
	{
		std::cout << prompt << std::endl;
		if (!std::getline(std::cin, *value))
			return false;
		if (!value->empty())
			return true;
		std::cout << "This field cannot be empty." << std::endl;
	}
}

PhoneBook::PhoneBook()
	: contactCount_(0), nextIndex_(0)
{
}

// While the book is filling up, nextIndex_ equals contactCount_ and the
// new contact lands in the first free slot. Once the book is full,
// nextIndex_ cycles through the slots in insertion order, so the slot it
// designates always holds the oldest stored contact, which the new one
// replaces.
void PhoneBook::storeContact(Contact contact)
{
	contacts_[nextIndex_] = contact;
	nextIndex_ = (nextIndex_ + 1) % MAX_CONTACTS;
	if (contactCount_ < MAX_CONTACTS)
		++contactCount_;
}

bool PhoneBook::addContact()
{
	std::string first;
	std::string last;
	std::string nickname;
	std::string phone;
	std::string secret;

	if (!readRequiredField("First name:", &first))
		return false;
	if (!readRequiredField("Last name:", &last))
		return false;
	if (!readRequiredField("Nickname:", &nickname))
		return false;
	if (!readRequiredField("Phone number:", &phone))
		return false;
	if (!readRequiredField("Darkest secret:", &secret))
		return false;
	storeContact(Contact(first, last, nickname, phone, secret));
	std::cout << "Contact added." << std::endl;
	return true;
}

// The index cell is printed directly: the int inserter honors setw, and
// neither an index (0 to 7) nor the "index" caption ever needs
// truncating.
void PhoneBook::displayContactList() const
{
	int index;

	std::cout << std::setw(COLUMN_WIDTH) << "index";
	printNameColumns("first name", "last name", "nickname");
	index = 0;
	while (index < contactCount_)
	{
		std::cout << std::setw(COLUMN_WIDTH) << index;
		printNameColumns(contacts_[index].getFirstName(),
			contacts_[index].getLastName(),
			contacts_[index].getNickname());
		++index;
	}
}

void PhoneBook::displayContact(int index) const
{
	std::cout << "First name: " << contacts_[index].getFirstName()
		<< std::endl;
	std::cout << "Last name: " << contacts_[index].getLastName()
		<< std::endl;
	std::cout << "Nickname: " << contacts_[index].getNickname()
		<< std::endl;
	std::cout << "Phone number: " << contacts_[index].getPhoneNumber()
		<< std::endl;
	std::cout << "Darkest secret: " << contacts_[index].getDarkestSecret()
		<< std::endl;
}

bool PhoneBook::searchContacts() const
{
	if (contactCount_ == 0)
	{
		std::cout << "The phonebook is empty." << std::endl;
		return true;
	}
	displayContactList();

	std::string input;

	std::cout << "Index to display:" << std::endl;
	if (!std::getline(std::cin, input))
		return false;
	// A valid index is exactly one digit below contactCount_:
	// MAX_CONTACTS is 8, so every valid index is a single character
	// '0' to '7'. The parse hardcodes that assumption, which holds
	// while MAX_CONTACTS <= 10.
	if (input.length() == 1 && input[0] >= '0'
		&& input[0] < '0' + contactCount_)
		displayContact(input[0] - '0');
	else
		std::cout << "Invalid index." << std::endl;
	return true;
}
