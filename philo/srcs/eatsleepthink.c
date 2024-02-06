/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eatsleepthink.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:15:01 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/02/06 17:26:44 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_others(t_data *d)
{
	if (!d)
		return ;
	while (!r_ended(d) && r_meals(d) > r_min(d))
	{
		usleep(10);
	}
}

void	eat(t_data *d)
{
	if (!r_ended(d) && ft_time() - r_ate(d) > d->arg->die)
	{
		w_ended(d, -1);
		usleep(10);
		pthread_mutex_lock(d->start_mutex);
		printf("%lld %d died\n", ft_time() - *(d->start), d->id);
		pthread_mutex_unlock(d->start_mutex);
	}
	if (!r_ended(d) && ft_time() - r_ate(d) <= d->arg->die)
	{
		pthread_mutex_lock(d->start_mutex);
		printf("%lld %d is eating\n", ft_time() - *(d->start), d->id);
		pthread_mutex_unlock(d->start_mutex);
		w_meals(d);
		w_ate(d, ft_time());
	}
	usleep(d->arg->eat * 1000);
}

void	sleep_think(t_data *d)
{
	if (!r_ended(d))
	{
		pthread_mutex_lock(d->start_mutex);
		printf("%lld %d is sleeping\n", ft_time() - *(d->start), d->id);
		pthread_mutex_unlock(d->start_mutex);
	}
	usleep(d->arg->sleep * 1000);
	if (r_meals(d) >= d->arg->max_eat && d->arg->max_eat >= 0)
		while (!r_ended(d))
			(usleep(1000));
	if (!r_ended(d))
	{
		pthread_mutex_lock(d->start_mutex);
		printf("%lld %d is thinking\n", ft_time() - *(d->start), d->id);
		pthread_mutex_unlock(d->start_mutex);
	}
	usleep(TTT);
}

void	take_forks_1(t_data *d)
{
	pthread_mutex_lock(d->mutex);
	if (!r_ended(d))
	{
		pthread_mutex_lock(d->start_mutex);
		printf("%lld %d has taken a fork\n", ft_time() - *(d->start), d->id);
		pthread_mutex_unlock(d->start_mutex);
	}
	pthread_mutex_lock(d->mutex_next);
	if (!r_ended(d))
	{
		pthread_mutex_lock(d->start_mutex);
		printf("%lld %d has taken a fork\n", ft_time() - *(d->start), d->id);
		pthread_mutex_unlock(d->start_mutex);
	}
}

void	take_forks_2(t_data *d)
{
	pthread_mutex_lock(d->mutex_next);
	if (!r_ended(d))
	{
		pthread_mutex_lock(d->start_mutex);
		printf("%lld %d has taken a fork\n", ft_time() - *(d->start), d->id);
		pthread_mutex_unlock(d->start_mutex);
	}
	pthread_mutex_lock(d->mutex);
	if (!r_ended(d))
	{
		pthread_mutex_lock(d->start_mutex);
		printf("%lld %d has taken a fork\n", ft_time() - *(d->start), d->id);
		pthread_mutex_unlock(d->start_mutex);
	}
}
