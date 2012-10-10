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
	int	ret;
	int	i;
	t_player	*test;
	t_player	*shm;
	ret = 0;
	i = 0;

		ret = fork();
		
		env->shmid = shmget(4224, sizeof(t_player), 0700);
		shm = shmat(env->shmid, NULL, 0);
		test = shm;
		test->x = 10;
		test->y = 11;
	if (ret != 0)
	{
		while (i != 20)
		{
		test = shm;
		test->x = test->x + 1;
		test->y = test->y + 1;
		i = i + 1;
		}
	}
		printf("ALORS %d %d\n",test->x,test->y);

	return (0);
}
int	main(void)
{
	t_env env;

	init(&env);
	run(&env);
	
	return (0);
}
