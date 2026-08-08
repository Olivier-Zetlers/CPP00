/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <ozetlers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 01:02:53 by ozetlers          #+#    #+#             */
/*   Updated: 2026/08/08 02:33:06 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact
{
public:
	// PhoneBook stores contacts in an array, whose elements are
	// default-constructed, so an empty placeholder must be
	// constructible; it is only ever read after being overwritten by a
	// fully-fielded contact.
	Contact();

	// A contact acquires its five fields atomically, at construction:
	// no half-populated Contact can exist. The parameters are taken by
	// value: the constructor works on its own copies.
	Contact(std::string firstName, std::string lastName,
		std::string nickname, std::string phoneNumber,
		std::string darkestSecret);

	// The getters return copies, so the caller can do whatever it
	// wants with the returned value without affecting the stored
	// contact.
	std::string getFirstName() const;
	std::string getLastName() const;
	std::string getNickname() const;
	std::string getPhoneNumber() const;
	std::string getDarkestSecret() const;

private:
	std::string firstName_;
	std::string lastName_;
	std::string nickname_;
	std::string phoneNumber_;
	std::string darkestSecret_;
};

#endif
