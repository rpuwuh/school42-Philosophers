/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:28:51 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/27 19:28:28 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t	*philo_createsemaphor(char *name, int num)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT, 0666, num);
	return (sem);
}

void	philo_killsemaphor(sem_t *sem, char *name)
{
	sem_close(sem);
	sem_unlink(name);
}
