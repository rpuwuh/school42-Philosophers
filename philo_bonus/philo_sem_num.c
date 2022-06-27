/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:03:10 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/27 22:10:19 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	t;

	res = (char *) malloc (ft_strlen (s1) + ft_strlen (s2) + 1);
	if (res == 0)
		return (res);
	i = 0;
	while (s1 [i])
	{
		res [i] = s1 [i];
		i++;
	}
	i = 0;
	t = ft_strlen(s1);
	while (s2 [i])
	{
		res [t + i] = s2 [i];
		i++;
	}
	res [ft_strlen (s1) + ft_strlen (s2)] = '\0';
	free (s1);
	free (s2);
	return (res);
}

static char	*ft_strdup(char *s1)
{
	size_t	len;
	size_t	i;
	char	*res;

	len = ft_strlen(s1);
	res = (char *) malloc (len + 1);
	if (res == 0)
		return (0);
	i = 0;
	while (s1[i])
	{
		res [i] = s1 [i];
		i++;
	}
	res [len] = 0;
	return (res);
}

sem_t	*philo_createsemaphor_num(int max, pid_t id, int num)
{
	char	*s1;
	sem_t	*res;

	s1 = ft_strjoin (ft_strdup ("/philo_id"), ft_itoa((int) id));
	s1 = ft_strjoin (s1, ft_strdup("_sem"));
	s1 = ft_strjoin (s1, ft_itoa(num));
	res = philo_createsemaphor(s1, max);
	free (s1);
	return (res);
}
