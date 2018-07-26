This is a research project on numbers that has simular structure in different bases.


This algorithm:

I manage to find ranges between bases where existing answers exist.
By generating these ranges on different bases i stop at ranges
that collapse each other. After if the bases collapse i can use the same algorithm
to scan for detail with a collapsed range. Eventually recursively the range collapse on itself
and find valid solutions.


Results:

	I manage to scan numbers with 32 milion digits for base 3, 4, 5 and 6.


Requirement:

	GMP: https://gmplib.org/


Compile:

	cd check_ranges
	./compile


Run:

	./main -n <start range> -base <base numbers>

Default: (starts at position 0 and scan with base 3, 4 and 5)

	./main -n 0 -base 3 4 5
	
Example: (starts at numbers with 32 mil digits and scan with base 4, 5, 6)

	./main -n 32000000 -base 4 5 6

Future:

	This project could potentially been runned on different machiens.
	It only needs a manager that every machine scan there own ranges.


Original i been inspired by Numberphile:

	https://www.youtube.com/watch?v=LNS1fabDkeA


The person that started is "Richard Green":

	https://plus.google.com/101584889282878921052/posts/Fni6x2TTeaS
	

You can contact me on Twitch:
		
		https://www.twitch.tv/lupo1989
		
