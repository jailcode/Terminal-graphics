#include "../includes/header.h"
/*
int	width(void)
int	height(void)

void	put_pixel(char *color, int x, int y)

//*/


t_coord	get_transformed_cords(t_win *win, int x, int y, int z)
{
	t_coord c;

	c.col = (x + win->cols / 2 + 1) % win->cols *z;
	c.row = (y + win->rows / 2 + 1) % win->rows *z;
	return (c);
}

int	main(void)
{
	t_win	win;
	t_coord	c;
	int		i= 0;
	int		j = 0;
	init_win(&win);
	update_window_size(&win, STDOUT_FILENO);
	while(1)
	{
	c = get_transformed_cords(&win, i++, j++, 1);
	printf("\033[%d;%dH", c.row, c.col);
	printf("#");
	fflush(stdout);
	usleep(10000);
	}
	return (0);
}


/*while(i < 100)
	{

		printf("\033[2J");
		printf("\033[0;0H");
		printf("\r# %d", i++);
		fflush(stdout);
		usleep(50000);
	}*/