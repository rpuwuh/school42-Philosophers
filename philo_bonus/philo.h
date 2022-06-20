/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:09:49 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/20 16:49:53 by bpoetess         ###   ########.fr       */
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

struct s_global
{
	int				count;
	int				ttd;
	int				tte;
	int				tts;
	int				numoftimes;
	// t_time			starttime;
	sem_t			*forks;
	pid_t			*guys;
};

int			ft_atoi(const char *str);

int			philo_usageerror(int arc, char **argv);

#endif