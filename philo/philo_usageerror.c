/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_usageerror.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:24:30 by bpoetess          #+#    #+#             */
/*   Updated: 2022/06/06 18:53:34 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_usageerror_text(void)
{
	printf("%s%s\n\n%s%s\n%s%s%s%s\n%s%s%s\n%s%s\n%s%s%s%s%s%s\n",
		"Usage: number_of_philosophers time_to_die time_to_eat ",
		"time_to_sleep [number_of_times_each_philosopher_must_eat]",
		"\tnumber_of_philosophers: The number of philosophers",
		" and also the number of forks.",
		"\ttime_to_die (in milliseconds): If a philosopher didn’t",
		" start eating time_to_die",
		"milliseconds since the beginning of their last meal or the",
		"beginning of the simulation, they die.",
		"\ttime_to_eat (in milliseconds): The time it takes for a ",
		"philosopher to eat.",
		"During that time, they will need to hold two forks.",
		"\ttime_to_sleep (in milliseconds): The time a philosopher ",
		"will spend sleeping.",
		"\tnumber_of_times_each_philosopher_must_eat (optional ",
		"argument): If all",
		"philosophers have eaten at least ",
		"number_of_times_each_philosopher_must_eat",
		"times, the simulation stops. If not specified, the ",
		"simulation stops when a philosopher dies.");
}

int	philo_usageerror(int arc, char **arv)
{
	if (arc <= 4 || arc >= 7 || ft_atoi(arv[1]) <= 1 || ft_atoi(arv[2]) <= 0
		|| ft_atoi(arv[3]) <= 0)
	{
		philo_usageerror_text();
		return (1);
	}
	return (0);
}
