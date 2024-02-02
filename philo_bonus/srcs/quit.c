/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:19:27 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/02/02 01:38:15 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_everyone(int *pids, int dead, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (i != dead)
			kill(pids[i], SIGTERM);
		i++;
	}
}

void	unlock_everyone(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->arg->phi)
	{
		sem_post(d->end[i]);
		i++;
	}
}

int	check_threads(int *pids, t_data *d)
{
	int	i;
	int	fail;

	i = 0;
	fail = 0;
	while (i < d->arg->phi)
	{
		if (pids[i] == -1)
			fail = 1;
		i++;
	}
	i = 0;
	while (fail && i < d->arg->phi)
	{
		if (pids[i] != -1)
			kill(pids[i], SIGTERM);
		i++;
	}
	return (fail);
}

void	exit_cleanly(int *pids, t_data *d, int return_value)
{
	sem_close(d->action);
	sem_unlink("actions");
	sem_close(d->knife);
	sem_unlink("knife");
	sem_close(d->first_dead);
	sem_unlink("first_dead");
	sem_close(d->forks);
	sem_unlink("forks");
	sem_close(d->mutex_run);
	sem_unlink("mutex_run");
	sem_close(d->mutex_eat);
	sem_unlink("mutex_eat");
	sem_close(d->mutex_meals);
	sem_unlink("mutex_meals");
	sem_close(d->mutex_max);
	sem_unlink("mutex_max");
	end_semas_close(d, d->arg->phi, 1);
	free(pids);
	exit(return_value);
}
