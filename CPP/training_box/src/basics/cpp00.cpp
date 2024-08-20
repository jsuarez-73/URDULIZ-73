/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp00.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:44:32 by jsuarez-          #+#    #+#             */
/*   Updated: 2024/08/16 22:45:02 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpp00.hpp"

namespace cpp00 {

	namespace ex00 {
//		This way is the same as actually defined.
//		We dereference the address from s at return statement.
//		to come back to object and send the reference.
//		std::string&	UpperCase(std::string *s)
//		{
//			size_t	slen = s->length();
//			while (slen--)
//				if ((*s)[slen] >= 'a' && (*s)[slen] <= 'z')
//					(*s)[slen] -= ('a' - 'A');
//			return (*s);
//		}
		void	Megaphone::UpperCase(std::string &s)
		{
			size_t	slen = s.length();
			while (slen--)
				if (s[slen] >= 'a' && s[slen] <= 'z')
					s[slen] -= ('a' - 'A');
		}

		Megaphone::Megaphone () : msg ("* LOUD AND UNBEREABLE"
									"FEEDBACK NOISE *") {};

		Megaphone::Megaphone (int args, char **s) : msg( "* LOUD AND UNBEREABLE"
														"FEEDBACK NOISE *")
		{ 
			int	cn;
			
			cn = 0;
			if (args-- > 1)
				msg = "";
			while (cn++ < args)
				msg += *(s + cn);
			Megaphone::UpperCase(msg);
		}

		void	Megaphone::yell() 
		{
			std::cout << msg + '\n';
		}

		int		Main(int argc, char **argv)
		{
			Megaphone megaphone = Megaphone(argc, argv);
			megaphone.yell();
			return (0);
		}
	}

	namespace ex01 {
		PhoneBook::PhoneBook() : index(0), is_loop(true) {};
		void	PhoneBook::addContact(Contact &contact)
		{
			if (index < MAX_CONTACTS)
				phonebook[index++] = contact;
			else if (index == MAX_CONTACTS)
			{
				index = 0;
				phonebook[index] = contact;
			}
		}
		
		Contact&	PhoneBook::searchContact(int index) throw (std::range_error)
		{
			if (index >= 0 && index < MAX_CONTACTS)
				return (phonebook[index]);
			throw std::range_error("Out of range");
		}

		std::string	&Contact::operator[](int index) throw (std::range_error)
		{
			if (index == 0)
				return (first_name);
			else if (index == 1)
				return (last_name);
			else if (index == 2)
				return (nickname);
			else if (index == 3)
				return (phone_number);
			else if (index == 4)
				return (darkest_secret);
			else
				throw std::range_error("Range error\n");
		}

		void	PhoneBook::searchOption()
		{
			int	i = -1;
			int	j = -1;

			while (++i < MAX_CONTACTS)
			{
				while (++j < 5)
					std::cout << phonebook[i][j] + " ";
				std::cout << "\n";
				j = -1;
			}
		}

		void	PhoneBook::displayMainMenu()
		{
			std::string	in;
			std::cout << "Select which operation do on PhoneBook\n"
				"1. ADD\n2. SEARCH\n3. EXIT\n";
			std::getline(std::cin, in);
			if (!in.compare("1"))
				addOption();
			else if (!in.compare("2"))
				searchOption();
			else if (!in.compare("3"))
				is_loop = false;
			else
				displayMainMenu();
		}
		
		void	PhoneBook::addOption()
		{
			int	cn = 0;
			Contact	contact;
			std::string fields[] = {"first name", "last name", "nickname",
								"phone number", "dark secret"};
			while (cn < 5)
			{
				std::cout << "Insert " + fields[cn] << std::endl;
				std::getline(std::cin, contact[cn]);
				if (contact[cn].length() == 0)
					continue ;
				cn++;
			}
			addContact(contact);
			std::cout << "Added contact successfully" << std::endl;
		}

		int	Main(int argc, char **argv)
		{
			(void)	argc;
			(void)	argv;
			
			PhoneBook	phonebook;
			while (phonebook.is_loop)
				phonebook.displayMainMenu();
			return (0);
		}
	}
}
