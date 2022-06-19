/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:09:40 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/19 14:37:55 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_end(t_global *glb)
{
	int	i;

	i = 0;
	while (i < glb->count)
		pthread_mutex_destroy(&(((glb->forks)[i++]).mutex));
	i = 0;
	while (i < glb->count)
	{
		pthread_mutex_destroy(&(((glb->guys)[i++]).mutexforlasttime));
		pthread_mutex_destroy(&(((glb->guys)[i++]).mutexforcounteats));
	}
	pthread_mutex_destroy(&(glb->print_mutex));
	pthread_mutex_destroy(&(glb->stop_mutex));
	pthread_mutex_destroy(&(glb->start_mutex));
	free(glb->forks);
	free(glb->guys);
	free(glb);
}

void	philo_sleep(int time)
{
	t_time	start;
	t_time	now;

	gettimeofday(&start, 0);
	gettimeofday(&now, 0);
	while (philo_gettimeinms(now) - philo_gettimeinms(start) < time)
	{
		gettimeofday(&now, 0);
		usleep (127);
	}
}

void	philo_createthreads(t_global *glb)
{
	int	i;

	i = 0;
	while (i < glb->count)
	{
		pthread_create(&glb->guys[i].id, 0, philo_thread, &glb->guys[i]);
		i++;
	}
	gettimeofday(&(glb->starttime), 0);
	philo_start(glb);
	pthread_create(&(glb->checkerid), 0, philo_checker, glb);
	pthread_join(glb->checkerid, 0);
	i = 0;
	while (i < glb->count)
	{
		pthread_join(glb->guys[i].id, 0);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_global	*glb;

	if (philo_usageerror(argc, argv))
		return (22);
	glb = philo_setglb(argc, argv);
	if (!glb)
		return (12);
	philo_createthreads(glb);
	philo_end(glb);
	return (0);
}
