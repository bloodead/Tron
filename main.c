#include <term.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct  s_env
{
	int	w;
	int	h;
	void*	shmaddr;
	int	shmid;
	int* 	status;
	char* 	bord;
	char*	cm;
	char*	cl;
}       t_env;

int	id_put(int c)
{
	char	d;

	d = c;
	write(1, &d, 1);
	return 0;
}

typedef struct s_buf
{

}	t_buf;

int	init_shm(t_env* env)
{
	env->shmid = shmget(4224, (env->w * env->h * sizeof(char)) + sizeof(int), IPC_CREAT | 0700);
	env->shmaddr = shmat(env->shmid, 0, 0);
	env->status = env->shmaddr;
	env->bord = env->shmaddr + sizeof(int);
	env->status = 0;
}

void	init_cadre(t_env* env)
{
	int	x;
	int	y;
	int	count;

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
	char* termtype;
	int	success;

	success = tgetent (0, termtype);
	termtype = getenv("TERM");
	tgetent(0, termtype);
	env->w = tgetnum("co");
	env->h = tgetnum("li");
	env->cm = tgetstr("cm", 0);
	env->cl = tgetstr("cl", 0);
	
}
int	init(t_env* env)
{
	if (init_env(env))
		return (1);
	tputs(env->cl, 1, id_put);
	init_shm(env);
	init_cadre(env);
	
}

void	run_child(t_env* env, int i)
{
	printf("%c Ready\n", i + 'A');
}

void	run_referee(t_env* env)
{
	printf("Server Ready\n");
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
			run_child(env, i);
			return 0;
		}
		i = i + 1;
	}
	run_referee(env);
}
int	main(void)
{
	t_env env;

	init(&env);
	run(&env);
	
	return (0);
}
