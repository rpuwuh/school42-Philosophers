/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:09:49 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/17 09:44:34 by bpoetess         ###   ########.fr       */
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

struct					s_global;
typedef struct s_global	t_global;

struct					s_fork;
typedef struct s_fork	t_fork;

struct					s_guy;
typedef struct s_guy	t_guy;

typedef struct timeval	t_time;

struct s_fork
{
	int				num;
	pthread_mutex_t	mutex;
};

struct s_guy
{
	int				num;
	int				counteats;
	pthread_mutex_t	mutexforcounteats;
	t_time			lasttimeeat;
	pthread_mutex_t	mutexforlasttime;
	t_fork			*l_fork;
	t_fork			*r_fork;
	pthread_t		id;
	t_global		*glb;
};

struct s_global
{
	int				count;
	int				ttd;
	int				tte;
	int				tts;
	int				numoftimes;
	pthread_t		checkerid;
	t_time			starttime;
	t_fork			*forks;
	t_guy			*guys;
	int				stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
};

int			ft_atoi(const char *str);

int			philo_usageerror(int arc, char **argv);

t_global	*philo_setglb(int argc, char **argv);

void		philo_print(t_global *glb, char *s, int n);

long int	philo_gettimeinms(t_time time);
int			philo_checkstop(t_global *glb);
void		*philo_checker(void *data);

void		*philo_thread(void *data);

void		philo_sleep(int time);

#endif