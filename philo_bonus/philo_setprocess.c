/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setprocess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 22:41:44 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/24 23:13:58 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	checker_getinfo(t_checker *checker)
{
	sem_wait(checker->glb->sem_eatentime);
	checker->checkedtime = checker->glb->eatentimecheck;
	sem_post(checker->glb->sem_eatentime);
	gettimeofday(&checker->timenow, 0);
	sem_wait(checker->glb->philo_sem);
	checker->eatentime = checker->glb->eatentime;
	checker->eatencount = checker->glb->eatencount;
	sem_post(checker->glb->philo_sem);
}

static void	checker_checkstatus(t_checker *checker)
{
	if (philo_gettimeinms(checker->timenow)
		- philo_gettimeinms(checker->eatentime) > checker->glb->ttd)
	{
		philo_print(checker->glb, "died\n", checker->glb->philo_id);
		exit (0);
	}
	if (checker->glb->numoftimes && !checker->eatenstatus
		&& checker->glb->eatencount >= checker->glb->numoftimes)
	{
		sem_wait (checker->glb->sem_eaten);
		checker->eatenstatus ++;
	}
	if (philo_gettimeinms(checker->timenow)
		- philo_gettimeinms(checker->checkedtime) > 3000)
		exit(0);
}

void	*philo_hungerchecker(void *data)
{
	t_checker	checker;

	checker.glb = (t_global *) data;
	checker.eatenstatus = 0;
	sem_wait(checker.glb->philo_sem);
	sem_post(checker.glb->philo_sem);
	while (1)
	{
		checker_getinfo(&checker);
		checker_checkstatus(&checker);
	}
}

void	*philo_eatenchecksem(void *data)
{
	t_global	*glb;

	glb = (t_global *) data;
	sem_wait(glb->sem_eatentime);
	gettimeofday(&glb->eatentimecheck, 0);
	sem_post(glb->sem_eatentime);
	while (1)
	{
		sem_wait(glb->sem_eatentime);
		gettimeofday(&glb->eatentimecheck, 0);
		sem_post(glb->sem_eatentime);
		sem_wait(glb->sem_eaten);
		sem_post(glb->sem_eaten);
	}
}

void	philo_set_process(t_global *glb)
{
	glb->eatencount = 0;
	glb->philo_sem = sem_open(0, 1);
	glb->sem_eatentime = sem_open(0, 1);
	sem_wait(glb->philo_sem);
	pthread_create(&(glb->id_eatenchecker), 0, philo_eatenchecksem, glb);
	pthread_detach(glb->id_eatenchecker);
	gettimeofday(&glb->eatentimecheck, 0);
	pthread_create(&(glb->id_hungerchecker), 0, philo_hungerchecker, glb);
	pthread_detach(glb->id_hungerchecker);
	philo_waitstart(&glb->starttime, (1000 + glb->count / 100 * 1000));
	gettimeofday(&glb->eatentime, 0);
	sem_post(glb->philo_sem);
}
