/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:09:40 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/14 06:15:05 by bpoetess         ###   ########.fr       */
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
		pthread_mutex_destroy(&(((glb->guys)[i++]).mutexforlasttime));
	pthread_mutex_destroy(&(glb->print_mutex));
	free(glb->forks);
	free(glb->guys);
	free(glb);
}

int	philo_takefork(t_global *glb, t_guy *guy, t_fork *fork)
{
	if (philo_checkstop(glb))
		return (0);
	pthread_mutex_lock(&(fork->mutex));
	philo_print(glb, " has taken a fork\n", guy->num);
	return (1);
}

void	philo_updateeattime(t_guy *guy)
{
	pthread_mutex_lock(&(guy->mutexforlasttime));
	gettimeofday(&(guy->lasttimeeat), 0);
	pthread_mutex_unlock(&(guy->mutexforlasttime));
}

int	philo_eat(t_guy *guy)
{
	if (!philo_takefork(guy->glb, guy, guy->l_fork)
		|| !philo_takefork(guy->glb, guy, guy->r_fork))
		return (0);
	philo_updateeattime(guy);
	if (philo_checkstop(guy->glb))
		return (0);
	philo_print(guy->glb, " is eating\n", guy->num);
	usleep(guy->glb->tte * 1000);
	philo_updateeattime(guy);
	pthread_mutex_unlock(&(guy->l_fork->mutex));
	pthread_mutex_unlock(&(guy->r_fork->mutex));
	return (1);
}

void	*test1(void *data)
{
	t_guy	*guy;

	guy = (t_guy *) data;
	philo_print(guy->glb, " thread is running\n", guy->num);
	while (!philo_checkstop(guy->glb))
	{
		if (!philo_eat(guy) || philo_checkstop(guy->glb))
			return (0);
		philo_print(guy->glb, " is sleeping\n", guy->num);
		usleep(guy->glb->tts * 1000);
		if (philo_checkstop(guy->glb))
			return (0);
		philo_print(guy->glb, " is thinking\n", guy->num);
	}
	return (0);
}

void	philo_createthreads(t_global *glb)
{
	int	i;
	int	status;

	i = 0;
	gettimeofday(&(glb->starttime), 0);
	while (i < glb->count)
	{
		status = pthread_create(&glb->guys[i].id, 0, test1, &glb->guys[i]);
		i++;
	}
	pthread_create(&(glb->checkerid), 0, philo_checker, glb);
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
	printf("Number of arguments is %d\n\n", argc);
	philo_createthreads(glb);
	philo_end(glb);
	return (0);
}
