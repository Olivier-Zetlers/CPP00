/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <ozetlers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 01:03:42 by ozetlers          #+#    #+#             */
/*   Updated: 2026/08/05 04:42:31 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
public:
	PhoneBook();

	// Runs one ADD command: reads the five fields, then stores the
	// contact. Returns false only when standard input closes; an
	// unacceptable field value is re-prompted internally.
	bool addContact();

	// Runs one SEARCH command: lists the contacts, then displays the
	// one whose index the user enters. Returns false only when standard
	// input closes; an invalid index is reported, not re-prompted.
	bool searchContacts() const;

private:
	static const int CAPACITY = 8;

	Contact contacts_[CAPACITY];
	int contactCount_;
	int nextIndex_;

	// Inserts contact, evicting the oldest one once the book is full.
	// A stored contact keeps its displayed index until it is evicted.
	void storeContact(const Contact &contact);

	void displayContactList() const;

	// Precondition: 0 <= index < contactCount_. The caller must validate;
	// this function does not.
	void displayContact(int index) const;
};

#endif
