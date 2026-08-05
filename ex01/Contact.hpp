/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <ozetlers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 01:02:53 by ozetlers          #+#    #+#             */
/*   Updated: 2026/08/02 01:03:03 by ozetlers         ###   ########.fr       */
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
	// no half-populated Contact can exist.
	Contact(const std::string &firstName, const std::string &lastName,
		const std::string &nickname, const std::string &phoneNumber,
		const std::string &darkestSecret);

	const std::string &getFirstName() const;
	const std::string &getLastName() const;
	const std::string &getNickname() const;
	const std::string &getPhoneNumber() const;
	const std::string &getDarkestSecret() const;

private:
	std::string firstName_;
	std::string lastName_;
	std::string nickname_;
	std::string phoneNumber_;
	std::string darkestSecret_;
};

#endif
