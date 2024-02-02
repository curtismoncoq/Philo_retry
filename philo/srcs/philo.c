/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:40:56 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/01/24 19:23:33 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	pthread_t		*thread;
	pthread_t		monitor[2];
	pthread_mutex_t	*mutex;
	t_data			*d;
	t_both			b;

	(b.t).ended = 0;
	thread = NULL;
	mutex = NULL;
	d = NULL;
	if (ft_parsing(ac, av, &(b.args)))
		return (0);
	if (ft_alloc(&thread, &mutex, &d, (b.args.phi)))
		return (perror("allocation failed"), 1);
	if (ft_init_data(d, &(b.t), &(b.args)))
		return (ft_free_alloc(thread, mutex, d), 1);
	if (ft_init_mutex(d, mutex, thread))
		return (ft_free_alloc(thread, mutex, d), 1);
	if (ft_init_threads(d, monitor, thread))
		return (ft_free_alloc(thread, mutex, d), 1);
	ft_join(thread, d, &(b.t), monitor);
	ft_free_alloc(thread, mutex, d);
}
