#include <unistd.h>

int	check_pos(

int	id_put(int c)
{
	char	d;

	d = c;
	write(1, &d, 1);
	return 0;
}
