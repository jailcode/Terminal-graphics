#include "../includes/header.h"



void	init_win(t_win *win)
{
    if (!win)
        return ;
    win->memory = NULL;
    if (init_memory_list(&win->memory) == FAILURE)
        return ;
    win = x_malloc(&win->memory, sizeof(*win));
    if (!win)
        return ;
    win->color = NULL;
    win->rows = 0;
    win->cols = 0;
    win->opacity = NULL;

}