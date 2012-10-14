#include <term.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "base.h"

int	init(t_env* env)
{
	init_env(env);
	tputs(env->cl, 1, id_put);
	init_shm(env);
	init_cadre(env);
	init_player(env);
	return (0);
}

int	run(t_env* env)
{
	int	ret;
	int	status;
	int	i;
	t_player	save;

	i = 0;
	while (i < 2)
	{
	ret = fork();
	if (ret == 0)
	{
		move_player(env, i);
		return 10;
	}
		i = i + 1;
	}
	waitpid(ret, &status, 0);
	usleep(50000);
	refresh_pos(env);
	save_pos(&save);
	check_coll(env);

	return (0);
}
int	main(void)
{
	t_env env;

	init(&env);
	while (1)
	{
	if (run(&env) == 10)
		return 0;
	}
	shmctl(env.shmid, IPC_RMID, 0);
	return (0);
}
