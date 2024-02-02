/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rw_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:19:25 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/02/01 22:46:01 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	r_ate(t_data *d)
{
	long long	res;

	sem_wait(d->mutex_eat);
	res = d->ate;
	sem_post(d->mutex_eat);
	return (res);
}

void	w_ate(t_data *d, long long value)
{
	sem_wait(d->mutex_eat);
	d->ate = value;
	sem_post(d->mutex_eat);
}

long long	r_meals(t_data *d)
{
	long long	res;

	sem_wait(d->mutex_meals);
	res = d->meals;
	sem_post(d->mutex_meals);
	return (res);
}

void	w_meals(t_data *d)
{
	sem_wait(d->mutex_meals);
	d->meals++;
	sem_post(d->mutex_meals);
}

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