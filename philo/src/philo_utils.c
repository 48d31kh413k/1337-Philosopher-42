#include <philo.h>

void	verifier_la_mort(t_table *tab)
{
	int	i;

	while (!tab->satiete)
	{
		i = -1;
		while (!tab->mort && ++i < tab->nombre_de_philos)
		{
			pthread_mutex_lock(&tab->verifier);
			if (temps_actuel() - tab->philos[i].dernier_repas > (size_t)tab->temps_de_famine)
			{
				afficher_message(&tab->philos[i], MESSAGE_MORT);
				tab->mort = 1;
			}
			pthread_mutex_unlock(&tab->verifier);
			usleep(100);
		}
		if (tab->mort)
			break ;
		i = 0;
		while (tab->nombre_de_repas != -1 && i < tab->nombre_de_philos
			&& tab->philos[i].nombre_manger >= tab->nombre_de_repas)
			i++;
		if (i == tab->nombre_de_philos)
			tab->satiete = 1;
	}
}

void	la_sortie(t_table *tab, pthread_t *identifiant)
{
	int	i;

	i = -1;
	while (++i < tab->nombre_de_philos)
		pthread_join(identifiant[i], NULL);
	i = -1;
	while (++i < tab->nombre_de_philos)
		pthread_mutex_destroy(&tab->philos[i].fourchette);
	pthread_mutex_destroy(&tab->afficher);
	pthread_mutex_destroy(&tab->verifier);
	free(tab->philos);
	free(identifiant);
}

size_t	temps_actuel(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	passe_temps(t_table *tab, size_t temps)
{
	size_t	t;

	t = temps_actuel();
	while (!(tab->mort))
	{
		if (temps_actuel() - t >= temps)
			break ;
		usleep(100);
	}
}
