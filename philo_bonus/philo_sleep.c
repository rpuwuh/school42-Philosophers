/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:02:29 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/27 19:27:39 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	philo_gettimeinms(t_time time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	philo_sleep(int time)
{
	t_time	start;
	t_time	now;

	gettimeofday(&start, 0);
	gettimeofday(&now, 0);
	usleep(time * 900);
	while (philo_gettimeinms(now) - philo_gettimeinms(start) < time)
	{
		gettimeofday(&now, 0);
		usleep (127);
	}
}

void	philo_setstart(t_time *start, int delay)
{
	gettimeofday(start, 0);
	start->tv_sec += delay / 1000;
}

void	philo_waitstart(t_time start, int delay)
{
	t_time	now;

	(void) delay;
	gettimeofday(&now, 0);
	while (philo_gettimeinms(now) - philo_gettimeinms(start) < 0)
	{
		gettimeofday(&now, 0);
		usleep (127);
	}
}

void	philo_print(t_global *glb, char *s, int n)
{
	t_time	timenow;

	gettimeofday(&timenow, 0);
	sem_wait(glb->sem_printf);
	printf("%d %d %s", (int)(philo_gettimeinms(timenow)
			- philo_gettimeinms(glb->starttime)), n + 1, s);
	sem_post(glb->sem_printf);
}
