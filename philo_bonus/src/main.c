#include <philo_bonus.h>

static int	erreur(void)
{
	write(2, "Error! invalid arguments\n", 26);
	return (1);
}

int	main(int argc, char *argv[])
{
	int			i;
	t_table		tab;

	if ((argc < 5 || argc > 6) || verifier_args(argc, argv, &tab))
		return (erreur());
	tab.t_0 = temps_actuel();
	i = -1;
	while (++i < tab.nombre_de_philos)
	{
		tab.philos[i].pid = fork();
		if (tab.philos[i].pid == -1)
		{
			write(2, "Error! fork failed\n", 19);
			exit(1);
		}
		if (tab.philos[i].pid == 0)
			la_vie((void *)&tab.philos[i]);
	}
	la_sortie(&tab);
	return (0);
}
