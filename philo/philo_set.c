/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 00:31:55 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/19 12:32:04 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_fork	*philo_createforks(t_global *glb)
{
	t_fork	*forks;
	int		i;

	if (!glb)
		return (0);
	forks = (t_fork *) malloc (glb->count * sizeof(t_fork));
	if (!forks)
		return (0);
	i = 0;
	while (i < glb->count)
	{
		forks[i].num = i;
		pthread_mutex_init(&(forks[i].mutex), 0);
		i++;
	}
	return (forks);
}

static t_guy	*philo_createguys(t_global *glb)
{
	t_guy	*guys;
	int		i;

	if (!glb)
		return (0);
	guys = (t_guy *) malloc (sizeof(t_guy) * glb->count);
	if (!guys)
		return (0);
	i = 0;
	while (i < glb->count)
	{
		guys[i].num = i;
		guys[i].counteats = 0;
		guys[i].glb = glb;
		guys[i].r_fork = glb->forks + i;
		pthread_mutex_init(&(guys[i].mutexforlasttime), 0);
		pthread_mutex_init(&(guys[i].mutexforcounteats), 0);
		if (i == glb->count - 1)
			guys[i].l_fork = glb->forks;
		else
			guys[i].l_fork = glb->forks + i + 1;
		i++;
	}
	return (guys);
}

static t_global	*philo_createguysandforks(t_global *glb)
{
	if (!glb)
		return (0);
	glb->forks = philo_createforks(glb);
	if (!glb->forks)
	{
		free (glb);
		return (0);
	}
	glb->guys = philo_createguys(glb);
	if (!glb->guys)
	{
		free (glb->forks);
		free (glb);
		return (0);
	}
	return (glb);
}

t_global	*philo_setglb(int argc, char **argv)
{
	t_global	*glb;

	glb = (t_global *) malloc(sizeof(t_global));
	if (!glb)
		return (0);
	pthread_mutex_init(&(glb->print_mutex), 0);
	pthread_mutex_init(&(glb->start_mutex), 0);
	pthread_mutex_init(&(glb->stop_mutex), 0);
	glb->start = 0;
	glb->stop = 0;
	glb->count = ft_atoi(argv[1]);
	glb->ttd = ft_atoi(argv[2]);
	glb->tte = ft_atoi(argv[3]);
	glb->tts = ft_atoi(argv[4]);
	if (argc == 6)
		glb->numoftimes = ft_atoi(argv[5]);
	else
		glb->numoftimes = 0;
	if (!philo_createguysandforks(glb))
		return (0);
	return (glb);
}
