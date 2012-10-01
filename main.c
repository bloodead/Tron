#include <term.h>

typedef struct  s_env
{
	int	w;
	int	h;
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

int	main()
{
	char*	termtype = getenv("TERM");
	int	success;

	success = tgetent(0, termtype);
	if (success == 0)
		return 0;
	env->w = tgetnum("co");
	env->h = tgetnum("li");
	env->cm = tgetstr("cm", 0);
	env->cl = tgetstr("cl", 0)
	tputs(env->cl, 1, id_put);
	return (0);
}
