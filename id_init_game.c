#include <term.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "base.h"

int	init_shm(t_env* env)
{
	env->shmid = shmget(4224, (env->w * env->h * sizeof(char)) + sizeof(int),
				   IPC_CREAT | 0700);
	env->shmaddr = shmat(env->shmid, 0, 0);
	env->status = env->shmaddr;
	env->bord = env->shmaddr + sizeof(int);
	env->status = 0;
	return (0);
}

void	init_cadre(t_env* env)
{
	int	x;
	int	y;

	x = 0;
	while (x < env->w)
	{
		tputs(tgoto(env->cm, x, 4), 1, id_put);
		write(1, ".", 1);
		tputs(tgoto(env->cm, x, env->h - 1), 1, id_put);
		write(1, ".", 1);
		x = x + 1;
	}
	y = 5;
	while (y < env->h - 1)
	{
		tputs(tgoto(env->cm, 0, y), 1, id_put);
		write(1, "#", 1);
		tputs(tgoto(env->cm, env->w, y), 1, id_put);
		write(1, "#", 1);
		y = y + 1;
	}
}

int	init_env(t_env* env)
{
	char*	termtype;

	termtype = getenv("TERM");
	tgetent (0, termtype);
	env->w = tgetnum("co");
	env->h = tgetnum("li");
	env->cm = tgetstr("cm", 0);
	env->cl = tgetstr("cl", 0);
	return (0);
}
