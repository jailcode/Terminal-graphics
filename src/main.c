#include "../includes/header.h"


# define CLEAR_SCREEN printf("\033[2J")
# define RESET printf("\033[0m")
# define FPS 60
/*
printf("\033[%d;%dH", i, j);
printf("\033[37;41m█");
*/

void    print_to_terminal(int row, int col, char* msg)
{
    printf("\033[%d;%dH", row, col);
    if (!msg)
        printf("\033[37;41m█");
    else
        printf("\033[%s", msg);
    fflush(stdout);
    RESET;
}
void    render_screen(t_win *win)
{
    int i;
    int j;

    t_screen *screen;
    t_screen *current;
    screen = win->screen;
    if (!win)
        return ;
    i = -1;
    while(++i < win->rows)
    {
        j = -1;
        while(++j < win->cols)
        {
            current = screen + i * win->cols + j;
            print_to_terminal(current->row, current->col, current->settings);
        }
    }
}

void  transform_coord(t_win *win, int *row, int *col)  
{
    *row = win->rows/2 - *row;
    *col = *col + win->cols/2;
}
void    project_pixel(t_win *win, int row, int col)
{
    if (!win)
        return ;
    transform_coord(win, &row, &col);
    (win->screen + row * win->cols + col)->settings = ft_strdup(win, "34m█");
}

void    reset_screen(t_win *win)
{
    int i, j;
    t_screen *screen;
    
    if (!win)
        return ;
    screen = win->screen;
    i = -1;
    while(++i < win->rows)
    {
        j = -1;
        while(++j < win->cols)
        {
            screen[(i * win->cols) + j].col = j;
            screen[i * win->cols + j].row = i;
            screen[i * win->cols + j].settings = "3m█";
        }
    }
}

int main(void)
{
    t_win   *win;
    t_mem_list *memory;

    if(init_memory_list(&memory) == FAILURE)
        return (1);
    win = x_malloc(&memory, sizeof(*win));
    init_win(win, &memory);
    update_window_size(win);

    while(1)
    {
        reset_screen(win);

        project_pixel(win, 0, 1);
        render_screen(win);
        usleep(1000/FPS);
    }

    clean_memory_list(&win->memory);
}
