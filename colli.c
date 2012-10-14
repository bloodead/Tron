#include "base.h"

void	check_coll(t_env* env)
{
	t_level*	level;

	level = env->shmaddr;
	if (level->player1.y + level->player1.directy == 5)
	{
		level->player1.directy = 0;
		level->player1.directx = 1;
	}
}
