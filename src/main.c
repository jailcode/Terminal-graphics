#include "../includes/header.h"
/*
printf("\033[%d;%d#", c.row, c.col);
	printf("\033[31m█");
	fflush(stdout);

//*/

# define CLEAR_SCREEN printf("\033[2J")
# define RESET printf("\033[0m")
t_coord	get_transformed_cords(t_win *win, int x, int y)
{
	t_coord c;

	c.col = x + (win->cols / 2);
	c.row = y + (win->rows / 2);
	return (c);
}

void	color_background(t_win *win)
{
	int	x;
	int y;
	y = -1;
	update_window_size(win, STDOUT_FILENO);
	while(++y < win->rows)
	{
		x = -1;
		while(++x < win->cols)
		{
			//put_pixel(win, x, y, 1, "37m", "█");

			printf("\033[%d;%dH", y, x);
			printf("\033[37m█");
			fflush(stdout);
			RESET;
		}
		usleep(1000);
	}

}

# define FPS 60

void	put_pixel(t_win *win, int x, int y, int z, char *color, char *character)
{
	t_coord c;
	x = x / z;
	y = y / z;
	if (z == 0)
		return ;
	c = get_transformed_cords(win, x, y);
	printf("\033[%d;%dH", c.row, c.col);
	printf("\033[%s%s", color, character);
	RESET;
	fflush(stdout);
}

int	main(void)
{
	t_win	win;
	init_win(&win);
	update_window_size(&win, STDOUT_FILENO);
	color_background(&win);
	while(1)
	{
		put_pixel(&win, 0, 0, 1, "31m", "█");
		usleep(1000000/FPS);
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