#include <philo.h>

static int	erreur(void)
{
	write(2, "Error! invalid arguments\n", 26);
	return (1);
}

int	main(int argc, char *argv[])
{
	int			i;
	t_table		tab;
	pthread_t	*identifiant;

	if ((argc < 5 || argc > 6) || verifier_args(argc, argv, &tab))
		return (erreur());
	identifiant = (pthread_t *)malloc(tab.nombre_de_philos * sizeof(pthread_t));
	tab.t_0 = temps_actuel();
	i = -1;
	while (++i < tab.nombre_de_philos)
	{
		if (pthread_create(&identifiant[i], NULL, &la_vie, &tab.philos[i]))
		{
			write(2, "Error! cannot create thread\n", 28);
			free(tab.philos);
			free(identifiant);
			return (1);
		}
		pthread_mutex_lock(&tab.verifier);
		tab.philos[i].dernier_repas = tab.t_0;
		pthread_mutex_unlock(&tab.verifier);
	}
	verifier_la_mort(&tab);
	la_sortie(&tab, identifiant);
	return (0);
}
