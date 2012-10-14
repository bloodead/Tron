#ifndef _base_h_
#define _base_h_

typedef struct	s_player
{
	int	x;
	int	y;
	int	directx;
	int	directy;
	struct s_player	*next;
}	t_player;

typedef struct	s_level
{
	t_player	player1;
	t_player	player2;
}	t_level;

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

void	check_coll(t_env* env);
void	refresh_pos(t_env* env);
void	move_player(t_env* env, int i);
void	init_player(t_env* env);
int	id_put(int c);
int	init_shm(t_env* env);
void	init_cadre(t_env* env);
int	init_env(t_env* env);
void	id_print_str(char* str); 
#endif
