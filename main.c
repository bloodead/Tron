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

int	init_term(t_env* env)
{
	char* termtype;

	termtype = getenv("TERM");
	tgetent(0, termtype);
	env->w = tgetnum("co");
	env->h = tgetnum("li");
	env->cm = tgetstr("cm", 0);
	env->cl = tgetstr("cl", 0);
	
}
int	init(t_env* env)
{
	init_term(env);
	tputs(env->cl, 1, id_put);
	init_shm(env);
	
}

void	run_child(t_env* env, int i)
{
	printf("%c Ready\n",i + 'A');
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
