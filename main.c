#include <term.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "base.h"

int	init(t_env* env)
{
	init_env(env);
	tputs(env->cl, 1, id_put);
	init_shm(env);
	init_cadre(env);
	return (0);
}

int	run(t_env* env)
{
	int	i;
	int	ret;

	i = 0;
	while (i < 2)
	{
		ret = fork();
		if (ret == 0)
		{
			return 0;
		}
		i = i + 1;
	}
	return (0);
}
int	main(void)
{
	t_env env;

	init(&env);
	run(&env);
	
	return (0);
}
