/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:21:35 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/02/06 17:05:13 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_mutex(t_data *d, pthread_mutex_t *mutex, pthread_t *thread)
{
	int	i;

	i = -1;
	while (++i < d->arg->phi)
	{
		(d + i)->mutex = &mutex[i];
		(d + i)->mutex_next = &mutex[(i + 1) % d->arg->phi];
		if (pthread_mutex_init((d + i)->mutex, NULL) || pthread_mutex_init((d
					+ i)->ate_mutex, NULL))
			return (ft_fail(thread, d, 0, i));
	}
	return (0);
}

int	ft_init_data(t_data *d, t_time *t, t_args *args)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&(t->start_mutex), NULL))
		return (1);
	if (pthread_mutex_init(&(t->end_mutex), NULL))
	{
		pthread_mutex_destroy(&(t->start_mutex));
		return (1);
	}
	while (++i < args->phi)
	{
		(d + i)->arg = args;
		(d + i)->id = i + 1;
		(d + i)->start = &(t->start);
		(d + i)->ate = 0;
		(d + i)->start_lock = &(t->start_lock);
		(d + i)->min_meals = &(t->min_meals);
		(d + i)->ended = &(t->ended);
		(d + i)->end_mutex = &(t->end_mutex);
		(d + i)->start_mutex = &(t->start_mutex);
		(d + i)->meals = 0;
	}
	return (0);
}

int	ft_init_threads(t_data *d, pthread_t *monitor, pthread_t *thread)
{
	int	i;

	*(d->start) = ft_time();
	w_start(d, 1);
	w_min(d, 0);
	if (pthread_create(&monitor[0], NULL, ft_monitor, (void *)d))
		return (ft_fail(thread, d, 0, d->arg->phi));
	if (pthread_create(&monitor[1], NULL, ft_start_all, (void *)d))
		return (pthread_join(monitor[0], NULL) * 0 + ft_fail(thread, d, 0,
				d->arg->phi));
	i = -1;
	while (++i < d->arg->phi)
	{
		if (i != d->arg->phi - 1)
		{
			if (pthread_create(&thread[i], NULL, routine, (void *)(d + i)))
				return (ft_fail(thread, d, i, d->arg->phi));
		}
		else
		{
			if (pthread_create(&thread[i], NULL, routine2, (void *)(d + i)))
				return (ft_fail(thread, d, i, d->arg->phi));
		}
	}
	return (0);
}

int	ft_alloc(pthread_t **threads, pthread_mutex_t **mutex, t_data **d, int phi)
{
	int	i;

	i = 0;
	*threads = (pthread_t *)ft_calloc(sizeof(pthread_t), phi);
	*mutex = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t), phi);
	*d = (t_data *)ft_calloc(sizeof(t_data), phi);
	if (!(*threads) || !*(mutex) || !(*d))
	{
		ft_free_alloc(*threads, *mutex, *d);
		return (1);
	}
	while (i < phi)
	{
		((*d) + i)->ate_mutex
			= (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t), 1);
		if ((*d)[i].ate_mutex == NULL)
		{
			ft_free_alloc((*threads), *(mutex), *d);
			return (1);
		}
		i++;
	}
	return (0);
}
