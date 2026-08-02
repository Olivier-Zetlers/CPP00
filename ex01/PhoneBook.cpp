/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <ozetlers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 01:04:01 by ozetlers          #+#    #+#             */
/*   Updated: 2026/08/02 03:57:11 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

const int PhoneBook::CAPACITY;

// Rendering and input-validation helpers. They read no member state, so
// they are free functions with internal linkage rather than members: the
// unnamed namespace is the C++98 replacement for file-scope static.
namespace
{
	// Rendered width of one column of the SEARCH listing, in characters.
	const int COLUMN_WIDTH = 10;

	const int FIELD_COUNT = 5;

	const char *const FIELD_PROMPTS[FIELD_COUNT] =
	{
		"First name:",
		"Last name:",
		"Nickname:",
		"Phone number:",
		"Darkest secret:"
	};

	// Counts encoded characters rather than bytes. In UTF-8 a continuation
	// byte matches 10xxxxxx; every other byte starts a new character. For
	// pure ASCII this returns the same value as std::string::length().
	std::string::size_type characterCount(const std::string &text)
	{
		std::string::size_type count = 0;

		for (std::string::size_type i = 0; i < text.length(); ++i)
		{
			if ((static_cast<unsigned char>(text[i]) & 0xC0) != 0x80)
				++count;
		}
		return count;
	}

	// Byte offset at which character number wanted begins, or the length of
	// text when it holds fewer than wanted characters. Cutting the string
	// here can never split a multi-byte sequence.
	std::string::size_type byteOffsetOf(const std::string &text,
		std::string::size_type wanted)
	{
		std::string::size_type seen = 0;

		for (std::string::size_type i = 0; i < text.length(); ++i)
		{
			if ((static_cast<unsigned char>(text[i]) & 0xC0) != 0x80)
			{
				if (seen == wanted)
					return i;
				++seen;
			}
		}
		return text.length();
	}

	// Truncates to COLUMN_WIDTH characters, the last of which becomes a dot.
	std::string formatColumn(const std::string &text)
	{
		std::string::size_type width;

		width = static_cast<std::string::size_type>(COLUMN_WIDTH);
		if (characterCount(text) <= width)
			return text;
		return text.substr(0, byteOffsetOf(text, width - 1)) + ".";
	}

	// std::setw pads to a number of bytes, so a cell holding multi-byte
	// characters needs a correspondingly larger field width for the
	// rendered column to come out COLUMN_WIDTH characters wide.
	void printColumn(const std::string &text)
	{
		std::string cell = formatColumn(text);
		std::string::size_type extra = cell.length() - characterCount(cell);

		std::cout << std::setw(COLUMN_WIDTH + static_cast<int>(extra)) << cell;
	}

	void printRow(const std::string &first, const std::string &second,
		const std::string &third, const std::string &fourth)
	{
		printColumn(first);
		std::cout << "|";
		printColumn(second);
		std::cout << "|";
		printColumn(third);
		std::cout << "|";
		printColumn(fourth);
		std::cout << std::endl;
	}

	// Byte-level filter, not a decoded-character filter: a field is
	// acceptable when no byte is a C0 control (below 0x20) or DEL (0x7F)
	// -- the ASCII bytes that would break the fixed-width layout -- and
	// at least one byte differs from the ASCII space, which also rejects
	// the empty string. Every byte of a multi-byte UTF-8 sequence is
	// 0x80 or above and passes the first test, so non-ASCII code points
	// that render blank or disturb the layout (NBSP, encoded C1
	// controls, zero-width and bidirectional characters) are accepted:
	// the guarantee is ASCII-scoped.
	bool isAcceptableField(const std::string &text)
	{
		bool hasVisible = false;

		for (std::string::size_type i = 0; i < text.length(); ++i)
		{
			unsigned char byte = static_cast<unsigned char>(text[i]);

			if (byte < 0x20 || byte == 0x7F)
				return false;
			if (byte != ' ')
				hasVisible = true;
		}
		return hasVisible;
	}

	// Prompts until an acceptable value is entered. Returns false only at
	// end-of-file; an unacceptable entry is reported and re-prompted here
	// and is never visible to the caller.
	bool readField(const std::string &prompt, std::string &value)
	{
		while (true)
		{
			std::cout << prompt << std::endl;
			if (!std::getline(std::cin, value))
				return false;
			if (isAcceptableField(value))
				return true;
			std::cout << "A field needs at least one character other than a "
				"space, and no control characters." << std::endl;
		}
	}
}

PhoneBook::PhoneBook()
	: contacts_(), contactCount_(0), nextIndex_(0)
{
}

int PhoneBook::slotOf(int index) const
{
	return (nextIndex_ + CAPACITY - contactCount_ + index) % CAPACITY;
}

void PhoneBook::storeContact(const Contact &contact)
{
	contacts_[nextIndex_] = contact;
	nextIndex_ = (nextIndex_ + 1) % CAPACITY;
	if (contactCount_ < CAPACITY)
		++contactCount_;
}

PhoneBook::Outcome PhoneBook::addContact()
{
	std::string fields[FIELD_COUNT];
	Contact newContact;

	for (int i = 0; i < FIELD_COUNT; ++i)
	{
		if (!readField(FIELD_PROMPTS[i], fields[i]))
			return InputClosed;
	}
	newContact.setFirstName(fields[0]);
	newContact.setLastName(fields[1]);
	newContact.setNickname(fields[2]);
	newContact.setPhoneNumber(fields[3]);
	newContact.setDarkestSecret(fields[4]);
	storeContact(newContact);
	std::cout << "Contact added." << std::endl;
	return Completed;
}

void PhoneBook::displayContactList() const
{
	printRow("index", "first name", "last name", "nickname");
	for (int index = 0; index < contactCount_; ++index)
	{
		const Contact &contact = contacts_[slotOf(index)];
		std::ostringstream label;

		label << index;
		printRow(label.str(), contact.getFirstName(), contact.getLastName(),
			contact.getNickname());
	}
}

void PhoneBook::displayContact(int index) const
{
	const Contact &contact = contacts_[slotOf(index)];

	std::cout << "First name: " << contact.getFirstName() << std::endl;
	std::cout << "Last name: " << contact.getLastName() << std::endl;
	std::cout << "Nickname: " << contact.getNickname() << std::endl;
	std::cout << "Phone number: " << contact.getPhoneNumber() << std::endl;
	std::cout << "Darkest secret: " << contact.getDarkestSecret() << std::endl;
}

PhoneBook::Outcome PhoneBook::readIndex(int &index) const
{
	std::string input;
	std::istringstream parser;
	int parsed = 0;
	char extra = 0;

	std::cout << "Index to display:" << std::endl;
	if (!std::getline(std::cin, input))
		return InputClosed;
	parser.str(input);
	if (!(parser >> parsed) || (parser >> extra))
		return Rejected;
	if (parsed < 0 || parsed >= contactCount_)
		return Rejected;
	index = parsed;
	return Completed;
}

PhoneBook::Outcome PhoneBook::searchContacts() const
{
	if (contactCount_ == 0)
	{
		std::cout << "The phonebook is empty." << std::endl;
		return Completed;
	}
	displayContactList();

	int index = 0;
	Outcome outcome = readIndex(index);

	if (outcome == InputClosed)
		return InputClosed;
	if (outcome == Rejected)
		std::cout << "Invalid index." << std::endl;
	else
		displayContact(index);
	return Completed;
}
