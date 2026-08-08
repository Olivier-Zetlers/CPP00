/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <ozetlers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 01:04:38 by ozetlers          #+#    #+#             */
/*   Updated: 2026/08/08 02:35:31 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

#include <iostream>
#include <string>

int main()
{
	PhoneBook phoneBook;
	std::string command;

	while (true)
	{
		std::cout << "Enter a command (ADD, SEARCH, EXIT):" << std::endl;
		if (!std::getline(std::cin, command))
			break;
		if (command == "ADD")
		{
			if (!phoneBook.addContact())
				break;
		}
		else if (command == "SEARCH")
		{
			if (!phoneBook.searchContacts())
				break;
		}
		else if (command == "EXIT")
			break;
	}
	return 0;
}
