#include "../includes/header.h"


void    init_win(t_win *win, t_mem_list **memory)
{
    update_window_size(win);
    win->color = NULL;
    win->opacity = NULL;
    win->memory = *memory;
    win->screen = init_screen(win);
    // Initialize camera position
    win->cam_x = 0.0f;
    win->cam_y = 0.0f;
    win->cam_z = 0.0f;
    win->cam_distance = 50.0f;  // Distance from object
}

t_screen    *init_screen(t_win *win)
{
    int i, j;
    t_screen *screen;

    screen = x_malloc(&win->memory, sizeof(*screen) * win->rows * win->cols);
    if (!screen)
        return (NULL);
    i = -1;
    while(++i < win->rows)
    {
        j = -1;
        while(++j < win->cols)
        {
            screen[(i * win->cols) + j].col = j;
            screen[i * win->cols + j].row = i;
            screen[i * win->cols + j].settings = ft_strdup(win, "35m█");
        }
    }
    return (screen);
}