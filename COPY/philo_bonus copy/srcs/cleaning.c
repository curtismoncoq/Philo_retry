/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:54:36 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/02/02 01:34:59 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_close_semas(t_data *d)
{
	sem_close(d->forks);
	end_semas_close(d, d->arg->phi, 0);
	sem_close(d->action);
	sem_close(d->knife);
	sem_close(d->first_dead);
	sem_close(d->mutex_eat);
	sem_close(d->mutex_meals);
	sem_close(d->mutex_run);
	sem_close(d->mutex_max);
}

void	ft_error_named(t_data *d)
{
	if (d->forks)
		sem_unlink("forks");
	if (d->forks)
		sem_close(d->forks);
	if (d->action)
		sem_unlink("actions");
	if (d->action)
		sem_close(d->action);
	if (d->knife)
		sem_unlink("knife");
	if (d->knife)
		sem_close(d->knife);
	if (d->first_dead)
		sem_unlink("first_dead");
	if (d->first_dead)
		sem_close(d->first_dead);
}

void	ft_init_named(t_data *d, t_args args)
{
	sem_unlink("forks");
	sem_unlink("actions");
	sem_unlink("knife");
	sem_unlink("first_dead");
	d->knife = NULL;
	d->first_dead = NULL;
	d->forks = NULL;
	d->action = NULL;
	d->knife = init_sem("knife", 1);
	d->first_dead = init_sem("first_dead", 1);
	d->forks = init_sem("forks", args.phi);
	d->action = init_sem("actions", 1);
}

void	ft_error_mutex(t_data *d)
{
	if (d->mutex_run)
		sem_unlink("mutex_run");
	if (d->mutex_run)
		sem_close(d->mutex_run);
	if (d->mutex_eat)
		sem_unlink("mutex_eat");
	if (d->mutex_eat)
		sem_close(d->mutex_eat);
	if (d->mutex_meals)
		sem_unlink("mutex_meals");
	if (d->mutex_meals)
		sem_close(d->mutex_meals);
	if (d->mutex_max)
		sem_unlink("mutex_max");
	if (d->mutex_max)
		sem_close(d->mutex_max);
}

void	ft_init_mutex(t_data *d, t_args args)
{
	sem_unlink("mutex_run");
	sem_unlink("mutex_eat");
	sem_unlink("mutex_meals");
	sem_unlink("mutex_max");
	d->mutex_run = NULL;
	d->mutex_eat = NULL;
	d->mutex_meals = NULL;
	d->mutex_max = NULL;
	d->mutex_run = init_sem("mutex_run", 1);
	d->mutex_eat = init_sem("mutex_eat", 1);
	d->mutex_meals = init_sem("mutex_meals", args.phi);
	d->mutex_max = init_sem("mutex_max", args.phi);
}
