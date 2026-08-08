/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <ozetlers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 01:03:42 by ozetlers          #+#    #+#             */
/*   Updated: 2026/08/08 02:34:54 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

// The subject caps the phonebook at 8 contacts. In C++, a const int
// initialized with a literal is a compile-time constant, so it can
// size the array below; this replaces the #define habit from C.
const int MAX_CONTACTS = 8;

class PhoneBook
{
public:
	PhoneBook();

	// Runs one ADD command: reads the five fields, then stores the
	// contact. Returns false only when standard input closes; an
	// empty field value is re-prompted internally.
	bool addContact();

	// Runs one SEARCH command: lists the contacts, then displays the
	// one whose index the user enters. Returns false only when standard
	// input closes; an invalid index is reported, not re-prompted.
	bool searchContacts() const;

private:
	Contact contacts_[MAX_CONTACTS];
	int contactCount_;
	int nextIndex_;

	// Inserts contact, evicting the oldest one once the book is full.
	// A stored contact keeps its displayed index until it is evicted.
	void storeContact(Contact contact);

	void displayContactList() const;

	// Precondition: 0 <= index < contactCount_. The caller must validate;
	// this function does not.
	void displayContact(int index) const;
};

#endif
