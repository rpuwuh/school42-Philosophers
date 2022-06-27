/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:09:49 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/27 22:35:20 by bpoetess         ###   ########.fr       */
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

typedef struct s_global	t_global;

typedef struct s_checker
{
	t_global	*glb;
	t_time		checkedtime;
	t_time		eatentime;
	t_time		timenow;
	int			eatencount;
}	t_checker;

struct s_global
{
	int			count;
	int			ttd;
	int			tte;
	int			tts;
	int			numoftimes;
	int			eatenstatus;
	int			eatencount;
	t_time		eatentime;
	t_time		eatentimecheck;
	sem_t		*philo_sem;
	sem_t		*death_sem;
	pid_t		philo_id;
	pthread_t	id_hungerchecker;
	pthread_t	id_eatenchecker;
	t_time		starttime;
	pid_t		*guys;
	sem_t		*sem_eaten;
	sem_t		*sem_eatentime;
	sem_t		*sem_forks;
	sem_t		*sem_forks_access;
	sem_t		*sem_printf;
};

int			ft_atoi(const char *str);

int			philo_usageerror(int arc, char **argv);

sem_t		*philo_createsemaphor(char *name, int num);
void		philo_killsemaphor(sem_t *sem, char *name);

long int	philo_gettimeinms(t_time time);
void		philo_sleep(int time);
void		philo_waitstart(t_time start, int delay);
void		philo_setstart(t_time *start, int delay);
void		philo_print(t_global *glb, char *s, int n);

t_global	*philo_setglb(int argc, char **argv);
void		philo_end(t_global *glb);

void		philo_action(t_global *glb, char *s, pid_t id);
void		philo_actions(t_global *glb, pid_t id);
void		philo_b_process(t_global *glb, pid_t id);
void		philo_set_process(t_global *glb);

void		*philo_hungerchecker(void *data);
void		*philo_eatenchecksem(void *data);

char		*ft_itoa(int n);

sem_t		*philo_createsemaphor_num(int max, pid_t id, int num);

#endif
