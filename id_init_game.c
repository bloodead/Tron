#include <term.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "base.h"

int	init_shm(t_env* env)
{
	env->shmid = shmget(4224, sizeof(t_player),
				   IPC_CREAT | 0700);
	env->shmaddr = shmat(env->shmid, 0, 0);
	env->status = env->shmaddr;
	env->bord = env->shmaddr + sizeof(int);
	env->status = 0;
	return (0);
}

void	init_struct_position(t_env* env, t_position* pos)
{
	t_position*	begin;
	int		x;
	int		y;

	begin = pos;
	x = 2;
	y = 2;
	while (x != env->w - 1 && y != env->h - 1)
	{
		while (x != env->w - 1);
		{
			pos->x = x;
			pos->y = y;
			pos->next = (t_position*)malloc(sizeof(*pos));
			pos = pos->next;
			x = x + 1;
			pos->value = 0;
		}
		x = 2;
		y = y + 1;
	}
	pos->next = 0;
	pos = begin;
}

void	init_position(t_env* env, t_level* level)
{
	level->player1.x = env->w / 3;
	level->player1.y = env->h / 2;
	tputs(tgoto(env->cm, level->player1.x, level->player1.y), 1, id_put);
	id_print_str("\033[01;46m ");
	level->player2.x = (env->w / 3) * 2;
	level->player2.y = env->h / 2;
	tputs(tgoto(env->cm, level->player2.x, level->player2.y), 1, id_put);
	id_print_str("\033[01;46m ");
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
