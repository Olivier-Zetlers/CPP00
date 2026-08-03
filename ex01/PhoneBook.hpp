/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <ozetlers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 01:03:42 by ozetlers          #+#    #+#             */
/*   Updated: 2026/08/02 19:15:45 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
public:
	// Outcome of one command. The read-eval-print loop continues on
	// Completed and stops on InputClosed. Rejected reports an unusable
	// user entry; it is produced only by readIndex() and is handled
	// inside the class, so it never reaches main().
	enum Outcome
	{
		Completed,
		Rejected,
		InputClosed
	};

	PhoneBook();

	Outcome addContact();
	Outcome searchContacts() const;

private:
	static const int CAPACITY = 8;

	Contact contacts_[CAPACITY];
	int contactCount_;
	int nextIndex_;

	// Maps a displayed index (0 is the oldest stored contact) to the slot
	// it occupies in the ring buffer.
	// Precondition: 0 <= index < contactCount_.
	int slotOf(int index) const;

	// Inserts contact, evicting the oldest one once the book is full.
	void storeContact(const Contact &contact);

	void displayContactList() const;

	// Precondition: 0 <= index < contactCount_. The caller must validate;
	// this function does not.
	void displayContact(int index) const;

	// Prompts for, reads and validates one index. On Completed the index
	// is written to the parameter; on Rejected and InputClosed the
	// parameter is left untouched.
	Outcome readIndex(int &index) const;
};

#endif
