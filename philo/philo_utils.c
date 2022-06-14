/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 03:41:13 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/14 06:13:52 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	philo_gettimeinms(t_time time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	philo_print(t_global *glb, char *s, int n)
{
	t_time	timenow;

	gettimeofday(&timenow, 0);
	pthread_mutex_lock(&(glb->print_mutex));
	printf("%d %d %s", (int)(philo_gettimeinms(timenow)
			- philo_gettimeinms(glb->starttime)), n, s);
	pthread_mutex_unlock(&(glb->print_mutex));
}

void	philo_stop(t_global *glb)
{
	pthread_mutex_lock(&(glb->stop_mutex));
	glb->stop = 1;
	pthread_mutex_unlock(&(glb->stop_mutex));
}

int	philo_checkstop(t_global *glb)
{
	int	res;

	pthread_mutex_lock(&(glb->stop_mutex));
	res = glb->stop;
	pthread_mutex_unlock(&(glb->stop_mutex));
	return (res);
}

void	*philo_checker(void *data)
{
	t_global	*glb;
	t_time		timenow;
	int			i;

	glb = data;
	while (!philo_checkstop(glb))
	{
		i = 0;
		while (!philo_checkstop(glb) && i < glb->count)
		{
			gettimeofday(&timenow, 0);
			pthread_mutex_lock(&(glb->guys[i].mutexforlasttime));
			if ((int)(philo_gettimeinms(timenow)
				- philo_gettimeinms(glb->starttime)) > glb->ttd
				&& (int)(philo_gettimeinms(timenow)
				- philo_gettimeinms(glb->guys[i].lasttimeeat)) > glb->ttd)
			{
				philo_print(glb, " is dead\n ", i);
				philo_stop(glb);
			}
			pthread_mutex_unlock(&(glb->guys[i].mutexforlasttime));
			i++;
		}
	}
	return (0);
}
