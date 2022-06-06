/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:09:49 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/06 19:25:00 by bpoetess         ###   ########.fr       */
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

typedef struct s_fork
{
	int				num;
	pthread_mutex_t	mutex;
	int				state;
}	t_fork;

typedef struct s_guy
{
	int				num;
	int				state;
	struct s_fork	*l_fork;
	struct s_fork	*r_fork;
}	t_guy;

typedef struct s_global
{
	int		count;
	int		ttd;
	int		tte;
	int		tts;
	int		numoftimes;
	t_fork	*forks;
	t_guy	*guys;
}	t_global;

int		ft_atoi(const char *str);
int		philo_usageerror(int arc, char **argv);

#endif