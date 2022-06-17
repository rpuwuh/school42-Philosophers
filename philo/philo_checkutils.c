/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checkutils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 03:41:13 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/17 00:46:33 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	philo_gettimeinms(t_time time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static void	philo_stop(t_global *glb)
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

static void	philo_deadguys(t_global *glb)
{
	int			i;
	t_time		timenow;

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
			philo_print(glb, "died\n", i);
			philo_stop(glb);
		}
		pthread_mutex_unlock(&(glb->guys[i].mutexforlasttime));
		i++;
	}
}

void	*philo_checker(void *data)
{
	t_global	*glb;
	int			status;
	int			i;

	glb = data;
	while (!philo_checkstop(glb))
	{
		philo_deadguys(glb);
		i = 0;
		status = 1;
		while (status && glb->numoftimes && !philo_checkstop(glb)
			&& i < glb->count)
		{
			pthread_mutex_lock(&(glb->guys[i].mutexforcounteats));
			if (glb->guys[i].counteats < glb->numoftimes)
				status = 0;
			pthread_mutex_unlock(&(glb->guys[i].mutexforcounteats));
			i++;
		}
		if (glb->numoftimes && status)
			philo_stop(glb);
	}
	return (0);
}
