/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:47:30 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/27 22:49:38 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	checker_getinfo(t_checker *checker)
{
	sem_wait(checker->glb->philo_sem);
	checker->eatentime = checker->glb->eatentime;
	sem_post(checker->glb->philo_sem);
	sem_wait(checker->glb->sem_eatentime);
	checker->checkedtime = checker->glb->eatentimecheck;
	sem_post(checker->glb->sem_eatentime);
	gettimeofday(&checker->timenow, 0);
}

static void	checker_checkstatus(t_checker *checker)
{
	if (philo_gettimeinms(checker->timenow)
		- philo_gettimeinms(checker->eatentime) > checker->glb->ttd)
	{
		sem_wait(checker->glb->death_sem);
		philo_print(checker->glb, "died\n", checker->glb->philo_id);
		exit (0);
	}
	if (philo_gettimeinms(checker->timenow)
		- philo_gettimeinms(checker->checkedtime) > 1500)
		exit(0);
}

void	*philo_hungerchecker(void *data)
{
	t_checker	checker;

	checker.glb = (t_global *) data;
	philo_waitstart(checker.glb->starttime, 0);
	while (1)
	{
		checker_getinfo(&checker);
		checker_checkstatus(&checker);
		usleep(100);
	}
}

void	*philo_eatenchecksem(void *data)
{
	t_global	*glb;

	glb = (t_global *) data;
	sem_wait(glb->sem_eatentime);
	gettimeofday(&glb->eatentimecheck, 0);
	sem_post(glb->sem_eatentime);
	philo_waitstart(glb->starttime, 0);
	while (1)
	{
		sem_wait(glb->sem_eatentime);
		gettimeofday(&glb->eatentimecheck, 0);
		sem_post(glb->sem_eatentime);
		sem_wait(glb->sem_eaten);
		sem_post(glb->sem_eaten);
		usleep(5000);
	}
}
