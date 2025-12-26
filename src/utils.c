#include "../includes/header.h"


void	update_window_size(t_win *win, int fd)
{
	struct winsize	w;

	ioctl(fd, TIOCGWINSZ, &w);

	win->rows = w.ws_row;
	win->cols = w.ws_col;
}