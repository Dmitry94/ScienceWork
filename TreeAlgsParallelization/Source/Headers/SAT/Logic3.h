#ifndef LOGIC_3_H
#define LOGIC_3_H

#include <iostream>

enum Logic3 { UNDEFINED, FALSE, TRUE };

class Logic3_Operations
{
public:
	static Logic3 getNegative(Logic3 value)
	{
		if (value == TRUE)
			return FALSE;
		else if (value == FALSE)
			return TRUE;
		else
			return UNDEFINED;
	}
	static Logic3 getDisjunction(Logic3 fst, Logic3 snd)
	{
		if (fst == FALSE && snd == FALSE)
			return FALSE;
		else if (fst == TRUE || snd == TRUE)
			return TRUE;
		else
			return UNDEFINED;
	}
	static Logic3 getConjuction(Logic3 fst, Logic3 snd)
	{
		if (fst == TRUE && snd == TRUE)
			return TRUE;
		else if (fst == FALSE || snd == FALSE)
			return FALSE;
		else
			return UNDEFINED;
	}
};

std::ostream& operator<<(std::ostream& os, const Logic3 value);

#endif /* LOGIC_3_H */
