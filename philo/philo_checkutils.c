/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checkutils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 03:41:13 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/27 19:04:16 by bpoetess         ###   ########.fr       */
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
	t_time		lasttime;

	gettimeofday(&timenow, 0);
	while ((int)(philo_gettimeinms(timenow)
		- philo_gettimeinms(glb->starttime)) <= glb->ttd)
	{
		gettimeofday(&timenow, 0);
		usleep(70);
	}
	i = 0;
	while (!philo_checkstop(glb) && i < glb->count)
	{
		gettimeofday(&timenow, 0);
		pthread_mutex_lock(&(glb->guys[i].mutexforlasttime));
		lasttime = glb->guys[i].lasttimeeat;
		pthread_mutex_unlock(&(glb->guys[i].mutexforlasttime));
		if (philo_gettimeinms(timenow) - philo_gettimeinms(lasttime) > glb->ttd)
		{
			philo_stop(glb);
			philo_print(glb, "died\n", i);
		}
		i++;
	}
}

void	*philo_checker(void *data)
{
	t_global	*glb;
	int			status;
	int			i;
	int			count;

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
			count = glb->guys[i].counteats;
			pthread_mutex_unlock(&(glb->guys[i].mutexforcounteats));
			if (count < glb->numoftimes)
				status = 0;
			i++;
		}
		if (glb->numoftimes && status)
			philo_stop(glb);
	}
	return (0);
}
