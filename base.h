#ifndef _base_h_
#define _base_h_

typedef struct	s_env
{
	int	w;
	int	h;
	void*	shmaddr;
	int	shmid;
	int*	status;
	char*	bord;
	char*	cm;
	char*	cl;
}	t_env;

int	id_put(int c);
int	init_shm(t_env* env);
void	init_cadre(t_env* env);
int	init_env(t_env* env);
#endif
