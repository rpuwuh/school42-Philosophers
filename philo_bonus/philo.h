/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:09:49 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/21 19:02:04 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <signal.h>
# include <semaphore.h>

typedef struct timeval	t_time;

typedef struct s_guy
{
	int		num;
	t_time	starttime;
	sem_t	*sem_start;
	sem_t	*sem_forks;
	sem_t	*sem_forks_permission;
	sem_t	*sem_printf;
}	t_guy;

typedef struct s_global
{
	int		count;
	int		ttd;
	int		tte;
	int		tts;
	int		numoftimes;
	pid_t	*guys;
	sem_t	*sem_start;
	sem_t	*sem_forks;
	sem_t	*sem_forks_access;
	sem_t	*sem_printf;
}	t_global;

int			ft_atoi(const char *str);

int			philo_usageerror(int arc, char **argv);

sem_t		*philo_createsemaphor(char *name, int num);
void		philo_killsemaphor(sem_t *sem, char *name);

void		philo_sleep(int time);

#endif