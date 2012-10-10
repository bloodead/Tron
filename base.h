#ifndef _base_h_
#define _base_h_

typedef struct	s_player
{
	int	x;
	int	y;
}		t_player;

typedef struct	s_position
{
	int			x;
	int			y;
	struct	s_position*	next
}		t_position

typedef struct	s_level
{
	t_player	player1;
	t_player	player2;
}		t_level;

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
