/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 02:07:56 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/27 21:04:17 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	i;

	res = malloc (count * size);
	if (res == 0)
		return (0);
	i = 0;
	while (i < count * size)
	{
		*((char *) res + i) = '\0';
		i++;
	}
	return (res);
}

static size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static void	ft_reverse(char *s)
{
	size_t	i;
	char	temp;

	i = 0;
	while (i < ft_strlen(s) / 2)
	{
		temp = s[i];
		s[i] = s[ft_strlen(s) - i - 1];
		s[ft_strlen(s) - i - 1] = temp;
		i++;
	}
}

static int	ft_countnums(int n)
{
	int	res;

	res = 0;
	if (n < 0)
		res++;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			i;
	long int	x;

	res = (char *) ft_calloc (ft_countnums(n) + 1, sizeof(char));
	if (res == 0)
		return (0);
	i = 0;
	x = (int) n;
	if (n < 0)
		x = -x;
	if (n == 0)
	{
		*res = '0';
		i++;
	}
	while (x)
	{
		res [i++] = x % 10 + '0';
		x /= 10;
	}
	if (n < 0)
		res [i++] = '-';
	ft_reverse(res);
	return (res);
}
