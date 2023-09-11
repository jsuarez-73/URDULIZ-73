REGISTERED NOTES FROM PRINFT MANUAL.

1.	Format of the format String :
		%[$][flags][width][.precision][length modifier]conversion
		
	1.1.	The arguments must correspond properly (!!AFTER TYPE PROMOTION!!)
			with the conversion specifier.

	1.2.	By default, the arguments are used in the order given, it means,
			every single token (%<format sintax><conv>) match each argument
			from the variadic function at the order they appear.

	1.3.	The first $ at the syntax format is to specify the argument which
			the conversion specificer must take.
	
	1.4.	The metacharacter * it is used to ask for the next argument or in
			this *m$ to specify the argument which must take. Only applicable to
			Field width and precision. The conversion specifiers asks for the next
			argument too, remember the arguments are indexed as 1, 2 ,3... etc.
	
	1.5.	BNF :

			<format>	::=	%[<modifiers>]<conv>
			<conv>		::=	c | s | p | u | d | i | x | X | %
			<modifiers> ::= [<var_arg>][<flags>][<width>][<precision>]
			<var_arg>	::= <number>$
			<flags>		::= (0 | -| # | +| space)<flags>
			<width>		::= [<number>] | [* | *<number>$]
			<precision>	::= .[<number>] | [* | *<number>$]
			<number>	::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 <number>


2.	Flags to Bonus :
	
	2.1 "0-."
		
		2.1.1  "0" : The value should be zero padded (so the value
			must be fulled with zeros). For d, i, x, X, u, the converted value
			is padded on the left with zeros rather than blanks.

			if 0 and - appears, the 0 flag is ignored.

			If a precision is given with an integer conversion (d, i, u, x X), the
			flag 0 is ignored.

			For other conversions the behaviour is undefined.

			Note: This modifier doesn't affect the memory size.
		
		2.1.2 "-" : The converted value is to be left adjusted on the field boundary.
			(the default is rigth justification). Field boundary references to the
			Field Width. EJ: %-10d, 15 -> means the padding is placed on left not on rigth.
			0000000015 (Default) vs 1500000000 (Left placed)

			The converted value is padded on the right with blanks, rather than on
			the left with blanks or zeros.

			Note: This modifier doesn't affect the memory size.

		2.1.3 "." (Precision) : If the precision is given as just '.', the precision
			is taken to be zero.

			!Important : A negative precision is taken as if the precision were omitted.
				EJ: When you give an argument negative to the precision.

			The precision gives the minimum number of digits to appear for d, i, u, x,
			X conversions, the number of digits to appear after the radix character for
			a, A, e, E, f, F conversions, the maximum number of characters to be printed
			from a string for s and S conversions.

			The precision could be followed by an optional decimal string "*" or "*m$"
			(field width) to specify that the preicsion is given in the next argument.

			!Important: If the field width < precision then field width is ignored.
	
	2.2 "# +" :

		2.2.1 "#" : The value should be converted to an "alternate form".
			For x and X conversions, a nonzero result hast the string 0x or 0X prepended
			to it.

			For others conversions, the result is undefined. Excepting (a, A, e, E, f, F,
			g, G, m, o).

			Note: this modifier can modify the memory size.
		
		2.2.2 "+" : A sign (+ or -) should always be placed before a number produced by
		a signed conversion. By default, a sign is just used only for negative numbers.

			Note: this modifier can modify the memory size.
		
		A + overrides a space if both are used.

		2.2.3 " " : A blank should be left before a positive number (or empty string) 
			produced by a signed conversion.
			
			Note: this modifier can modify the memory size.

3.	Mandatories conversion specifiers :

	3.1. "c, s, p, d, i, u, x, X, %"

		3.1.1 Mapped : Each conversion specifiers match a type like following:
			c -> int (converted to unsigned char, the resulting character is written).
			s -> const char * (characters from the array must have null terminating byte).
			p -> void * (print hexadecimal)
			(d, i) -> int (converted to signed decimal notation)
			(u, x, X) -> unsigned int (converted to unsigned decimal (u), unsigned hexadecimal).
			% -> A '%' is written. No argument is converted.