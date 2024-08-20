/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp00.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:45:34 by jsuarez-          #+#    #+#             */
/*   Updated: 2024/08/16 22:46:51 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CPP00
# define CPP00

# include <iostream>
# include <iomanip>
# include <string>

namespace cpp00{
	namespace ex00 {

			class Megaphone 
			{
					private :
				std::string	msg;
				static const int num = 1;
				
				void	UpperCase(std::string &s);

					public :
				Megaphone ();
				Megaphone (int args, char **s);
				void	yell();
			};
			int		Main(int argc, char **argv);
	}

	namespace ex01 {
		struct Contact {
			std::string first_name;
			std::string	last_name;
			std::string	nickname;
			std::string	phone_number;
			std::string	darkest_secret;
			std::string	&operator[](int index) throw (std::range_error);
		};

		class PhoneBook {
			private:

			const static int MAX_CONTACTS = 8;
			Contact phonebook[MAX_CONTACTS];
			int	index;
			
			public:
			bool		is_loop;
			PhoneBook ();
			void		addContact(Contact &contact);
			Contact&	searchContact(int index) throw (std::range_error);
			void		displayMainMenu();
			void		addOption();
			void		searchOption();
		};
		int	Main(int argc, char **argv);
	}
}
#endif
