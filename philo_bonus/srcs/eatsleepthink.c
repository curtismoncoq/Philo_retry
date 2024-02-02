/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eatsleepthink.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:15:01 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/02/01 23:33:48 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_data *d)
{
	sem_wait(d->knife);
	sem_wait(d->forks);
	sem_wait(d->forks);
	sem_post(d->knife);
	if (!r_run(d))
		return ;
	sem_wait(d->action);
	printf("%lld %d has taken a fork\n", ft_time() - d->start, d->id);
	printf("%lld %d has taken a fork\n", ft_time() - d->start, d->id);
	sem_post(d->action);
	sem_wait(d->action);
	printf("%lld %d is eating\n", ft_time() - d->start, d->id);
	sem_post(d->action);
	w_meals(d);
	w_ate(d, ft_time());
	usleep(d->arg->eat * 1000);
	sem_post(d->forks);
	sem_post(d->forks);
}

void	sleep_think(t_data *d)
{
	sem_wait(d->action);
	printf("%lld %d is sleeping\n", ft_time() - d->start, d->id);
	sem_post(d->action);
	usleep(d->arg->sleep * 1000);
	if (!r_run(d))
		return ;
	sem_wait(d->action);
	printf("%lld %d is thinking\n", ft_time() - d->start, d->id);
	sem_post(d->action);
	usleep(TTT);
}
