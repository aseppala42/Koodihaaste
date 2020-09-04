#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

/*
*	Author:			Akseli Seppala
*	Program:		Converts a Roman Numeral (combination of I, V, X, L, C, D and/or M) into Arabic Number. Case insensitive. Error checking checks if same symbol is placed more than three (3) times in a row or if the user tries to subtract a number from one that is more than 10 times greater.	
*/

void	strupr(char *str)
{
	while (*str)
	{
		*str = toupper((unsigned char) *str);
		str++;
	}
}

char	*strnrev(char *str, size_t start, size_t end)
{
	char	tmp;

	if (!str || *str == 0)
		return (0);
	if (start >= end)
		return (str);
	tmp = *(str + start);
	*(str + start) = *(str + end);
	*(str + end) = tmp;
	strnrev(str, ++start, --end);
	return (str);
}

int		get_val(char c)
{
/*
*	Would be much easier with dictionaries for example rom['x'] = 10
*/
	int	i;

	i = strcspn("IVXLCDM", &c);
	if (i == 7)
		return (0);
	return (pow(10, i / 2) * (i % 2 ? 5 : 1));
}

int		err_check(char *str)
{
	static int	x = 0;
	int			val;

	if (!str || !*str)
		return (0);
	val = get_val(*str);
	if (!val || x > 3 || get_val(*(str + 1)) / val > 10)
		return 1;
	x = (*str == *str + 1 ? x + 1: 0);
	return (err_check(++str));
}

int		roman_num(char *str, int n)
{
	int	val;

	if (!*str)
		return (n);
	val = get_val(*str);
	if (val < get_val(*(str - 1)))
		return (roman_num(str + 1, n - val));
	return (roman_num(str + 1, n + val));
}

int		main(int ac, char *av[])
{
	char	*str;
	int		n;

	if (ac != 2)
	{
		printf("Please run again with one Roman Numeral (combination of I, V, X, L, C, D and/or M) as argument.\n");
		return (0);
	}
	str = *++av;
	strupr(str);
	if (err_check(str))
	{
		printf("Error: %s is not a Roman Numeral.\n", str);
		return (0);
	}
	printf("Roman Numeral %s is ", str);
	str = strnrev(str, 0, strlen(str) - 1);
	n = roman_num(str + 1, get_val(*str));
	printf("%d in Arabic Numbers.\n", n);
	return (0);
}
