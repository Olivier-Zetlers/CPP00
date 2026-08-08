/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <ozetlers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 01:03:42 by ozetlers          #+#    #+#             */
/*   Updated: 2026/08/08 16:17:55 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"

#define MAX_CONTACTS 8

class PhoneBook
{
public:
	PhoneBook();

	bool addContact();
	bool searchContacts() const;

private:
	Contact contacts_[MAX_CONTACTS];
	int contactCount_;
	int nextIndex_;

	void storeContact(Contact contact);
	void displayContactList() const;
	void displayContact(int index) const;
};

#endif
