/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:16:43 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/01/17 18:29:20 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_data	*d;

	d = data;
	w_ate(d, 1);
	while (r_start(d))
	{
		if (r_start(d) == -1)
			return (data);
		usleep(10);
	}
	w_ate(d, *(d->start));
	if (d->id % 2)
		usleep(d->arg->eat * 500);
	while (!r_ended(d))
	{
		take_forks_1(d);
		eat(d);
		pthread_mutex_unlock(d->mutex);
		pthread_mutex_unlock(d->mutex_next);
		if (r_ended(d))
			break ;
		sleep_think(d);
	}
	return (data);
}

void	*routine2(void *data)
{
	t_data	*d;

	d = data;
	w_ate(d, 1);
	while (r_start(d))
	{
		if (r_start(d) == -1)
			return (data);
		usleep(10);
	}
	w_ate(d, *(d->start));
	if (d->id % 2)
		usleep(d->arg->eat * 500);
	while (!r_ended(d))
	{
		take_forks_2(d);
		eat(d);
		pthread_mutex_unlock(d->mutex_next);
		pthread_mutex_unlock(d->mutex);
		if (r_ended(d))
			break ;
		sleep_think(d);
	}
	return (data);
}

void	*ft_start_all(void *data)
{
	t_data	*d;
	int		i;
	int		inits;

	d = data;
	while (r_start(d))
	{
		i = -1;
		inits = 1;
		while (++i < d->arg->phi)
		{
			if (r_ate(d + i) == 0)
				inits = 0;
			if (r_ate(d + i) == 0)
				break ;
		}
		if (inits)
			*(d->start) = ft_time();
		if (inits)
			w_start(d, 0);
		usleep(1);
		if (r_start(d) == -1)
			return (data);
	}
	return (data);
}

void	ft_while_monitor(t_data *d, int i, int finito)
{
	while (!r_ended(d))
	{
		i = -1;
		finito = 1;
		while (++i < d->arg->phi)
		{
			if (d->arg->max_eat < 0 || r_meals(d + i) < d->arg->max_eat)
				finito = 0;
			if (r_ate(d + i) != 1 && ft_time() - r_ate(d + i) > d->arg->die
				&& !r_ended(d))
			{
				w_ended(d, -1);
				usleep(100);
				pthread_mutex_lock(d->start_mutex);
				printf("%lld %d died\n", ft_time() - *(d->start), (d + i)->id);
				pthread_mutex_unlock(d->start_mutex);
			}
		}
		if (finito && !r_ended(d))
			w_ended(d, 1);
		usleep(1);
	}
}

void	*ft_monitor(void *data)
{
	t_data	*d;

	d = data;
	while (r_start(d))
	{
		if (r_start(d) == -1)
			return (data);
		usleep(10);
	}
	ft_while_monitor(d, -1, 1);
	return (data);
}
