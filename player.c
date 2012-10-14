#include "base.h"
#include <term.h>
#include <stdlib.h>
#include <stdio.h>

void	init_player(t_env* env)
{
	t_level*	level;

	level = env->shmaddr;
	level->player1.x = env->w / 3;
	level->player1.y = env->h / 2;
	level->player1.directy = -1;
	level->player1.directx = 0;
	tputs(tgoto(env->cm, level->player1.x, level->player1.y), 1, id_put);
	id_print_str("\033[01;46m ");
	level->player2.x = (env->w / 3) * 2;
	level->player2.y = env->h / 2;
	level->player2.directy = -1;
	level->player2.directx = 0;
	tputs(tgoto(env->cm, level->player2.x, level->player2.y), 1, id_put);
	id_print_str("\033[01;46m ");
}

void	move_player(t_env* env, int i)
{
	t_level*	level;

	level = env->shmaddr;
	if (i == 0)
	{
		level->player1.x = level->player1.x + level->player1.directx;
		level->player1.y = level->player1.y + level->player1.directy;
	}
	if (i == 1)
	{
		level->player2.y = level->player2.y + level->player2.directy;
		level->player2.x = level->player2.x + level->player2.directx;
	}
}

void	refresh_pos(t_env* env)
{
	t_level*	level;

	level = env->shmaddr;
	tputs(tgoto(env->cm, level->player1.x, level->player1.y), 1, id_put);
	id_print_str("\033[01;46m ");
	tputs(tgoto(env->cm, level->player2.x, level->player2.y), 1, id_put);
	id_print_str("\033[01;46m ");
}
