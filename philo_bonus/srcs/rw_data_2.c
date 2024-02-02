/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rw_data_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:19:25 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/02/02 01:41:53 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	r_run(t_data *d)
{
	int	res;

	sem_wait(d->mutex_run);
	res = d->running;
	sem_post(d->mutex_run);
	return (res);
}

void	w_run(t_data *d)
{
	sem_wait(d->mutex_run);
	d->running = 0;
	sem_post(d->mutex_run);
}

int	r_max(t_data *d)
{
	int	res;

	sem_wait(d->mutex_run);
	res = d->arg->max_eat;
	sem_post(d->mutex_run);
	return (res);
}

void	w_max(t_data *d, int value)
{
	sem_wait(d->mutex_run);
	d->arg->max_eat = value;
	sem_post(d->mutex_run);
}
