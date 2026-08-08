/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <ozetlers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 01:04:01 by ozetlers          #+#    #+#             */
/*   Updated: 2026/08/03 05:51:29 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

#include <iomanip>
#include <iostream>
#include <string>

const int PhoneBook::CAPACITY;

// Rendering and input-validation helpers. They read no member state, so
// they are free functions with internal linkage rather than members: the
// unnamed namespace is the C++98 replacement for file-scope static.
namespace
{
	// Rendered width of one column of the SEARCH listing, in characters.
	const int COLUMN_WIDTH = 10;

	const char *const GENERIC_COMPLAINT =
		"A field needs at least one character other than a "
		"space, and only printable ASCII characters.";

	const char *const PHONE_COMPLAINT =
		"A phone number needs at least one digit "
		"and no characters other than digits.";

	// Truncates to COLUMN_WIDTH characters, the last of which becomes a
	// dot. Every cell is ASCII by construction -- stored fields pass
	// isAcceptableField, and the header and index cells are ASCII
	// literals and digits -- so byte counts and character counts
	// coincide.
	std::string formatColumn(const std::string &text)
	{
		std::string::size_type width;

		width = static_cast<std::string::size_type>(COLUMN_WIDTH);
		if (text.length() <= width)
			return text;
		return text.substr(0, width - 1) + ".";
	}

	// The stream's default adjustment is right, so std::setw alone
	// renders the cell right-aligned in a COLUMN_WIDTH-character field.
	void printColumn(const std::string &text)
	{
		std::cout << std::setw(COLUMN_WIDTH) << formatColumn(text);
	}

	// Prints the three name columns of one listing row, each preceded by
	// its pipe separator, then ends the line. The caller prints the
	// index cell first.
	void printNameColumns(const std::string &first, const std::string &second,
		const std::string &third)
	{
		std::cout << "|";
		printColumn(first);
		std::cout << "|";
		printColumn(second);
		std::cout << "|";
		printColumn(third);
		std::cout << std::endl;
	}

	// Byte-level filter: a field is acceptable when every byte is
	// printable ASCII -- 0x20 (space) through 0x7E (tilde) -- and at
	// least one byte differs from the space, which also rejects the
	// empty string. The range test excludes the C0 controls and DEL,
	// which would break the fixed-width layout, and every byte at or
	// above 0x80. Each byte of a multi-byte UTF-8 sequence is 0x80 or
	// above, so non-ASCII input is rejected as a whole: only ASCII text
	// can enter the phonebook.
	bool isAcceptableField(const std::string &text)
	{
		bool hasVisible = false;
		std::string::size_type i = 0;

		while (i < text.length())
		{
			unsigned char byte = static_cast<unsigned char>(text[i]);

			if (byte < 0x20 || byte > 0x7E)
				return false;
			if (byte != ' ')
				hasVisible = true;
			++i;
		}
		return hasVisible;
	}

	// Digits-only filter for the phone-number field: acceptable when the
	// text is non-empty and every byte is a decimal digit. '0'..'9' are
	// contiguous and ascending in every conforming character set, and
	// every byte of a multi-byte UTF-8 sequence is 0x80 or above, so it
	// fails the range test whatever the signedness of plain char.
	bool isAcceptablePhoneNumber(const std::string &text)
	{
		std::string::size_type i = 0;

		if (text.empty())
			return false;
		while (i < text.length())
		{
			if (text[i] < '0' || text[i] > '9')
				return false;
			++i;
		}
		return true;
	}

	// Prompts until a value passing isAcceptable is entered. Returns false
	// only at end-of-file; an unacceptable entry is reported with
	// complaint and re-prompted here and is never visible to the caller.
	bool readField(const std::string &prompt, std::string &value,
		bool (*isAcceptable)(const std::string &), const char *complaint)
	{
		while (true)
		{
			std::cout << prompt << std::endl;
			if (!std::getline(std::cin, value))
				return false;
			if (isAcceptable(value))
				return true;
			std::cout << complaint << std::endl;
		}
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
void PhoneBook::storeContact(const Contact &contact)
{
	contacts_[nextIndex_] = contact;
	nextIndex_ = (nextIndex_ + 1) % CAPACITY;
	if (contactCount_ < CAPACITY)
		++contactCount_;
}

bool PhoneBook::addContact()
{
	std::string first;
	std::string last;
	std::string nickname;
	std::string phone;
	std::string secret;

	if (!readField("First name:", first, isAcceptableField, GENERIC_COMPLAINT))
		return false;
	if (!readField("Last name:", last, isAcceptableField, GENERIC_COMPLAINT))
		return false;
	if (!readField("Nickname:", nickname, isAcceptableField,
			GENERIC_COMPLAINT))
		return false;
	if (!readField("Phone number:", phone, isAcceptablePhoneNumber,
			PHONE_COMPLAINT))
		return false;
	if (!readField("Darkest secret:", secret, isAcceptableField,
			GENERIC_COMPLAINT))
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
	int index = 0;

	std::cout << std::setw(COLUMN_WIDTH) << "index";
	printNameColumns("first name", "last name", "nickname");
	while (index < contactCount_)
	{
		const Contact &contact = contacts_[index];

		std::cout << std::setw(COLUMN_WIDTH) << index;
		printNameColumns(contact.getFirstName(), contact.getLastName(),
			contact.getNickname());
		++index;
	}
}

void PhoneBook::displayContact(int index) const
{
	const Contact &contact = contacts_[index];

	std::cout << "First name: " << contact.getFirstName() << std::endl;
	std::cout << "Last name: " << contact.getLastName() << std::endl;
	std::cout << "Nickname: " << contact.getNickname() << std::endl;
	std::cout << "Phone number: " << contact.getPhoneNumber() << std::endl;
	std::cout << "Darkest secret: " << contact.getDarkestSecret() << std::endl;
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
	// A valid index is exactly one digit below contactCount_: CAPACITY
	// is 8, so every valid index is a single character '0' to '7'. The
	// parse hardcodes that assumption, which holds while CAPACITY <= 10.
	if (input.length() == 1 && input[0] >= '0'
		&& input[0] < '0' + contactCount_)
		displayContact(input[0] - '0');
	else
		std::cout << "Invalid index." << std::endl;
	return true;
}
