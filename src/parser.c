/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:21:13 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/05 14:31:59 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static inline bool	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/* static const char	*print_and_null(const char *s)
{
	print_and_return((char *)s, 0);
	return (NULL);
} */

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (NULL);
	if (!is_digit(*str))
		return (NULL);
	number = str;
	while (is_digit(*str))
	{
		++len;
		++str;
	}
	while (is_space(*str))
		++str;
	if (*str != '\0')
		return (NULL);
	if (len > 10)
		return (NULL);
	return (number);
}

/**
 * @brief Converts a string to an integer (ASCII to Integer)
 * 
 * @param nptr Pointer to the null-terminated string to be interpreted
 * @return int The converted integral number as an int value
 */
int	ft_atoi(const char *nptr)
{
	const char	*num;
	long		result;

	result = 0;
	num = valid_input(nptr);
	if (!num)
		return (0);
	while (*num && is_digit(*num))
	{
		result = (result * 10) + (*num - '0');
		if (result > INT_MAX)
			return (0);
		num++;
	}
	return ((int)result);
}
