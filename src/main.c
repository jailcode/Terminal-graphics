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
    *col = (*col * 2) + win->cols/2;  // Multiply by 2 to account for aspect ratio
}
void    cvt_3d_to_2d(float *x, float *y, float *z)
{
    *x = *x / *z;
    *y = *y / *z;
}
void    project_pixel(t_win *win, int row, int col, char *settings)
{
    if (!win)
        return ;
    transform_coord(win, &row, &col);
    if (row < 0 || row >= win->rows || col < 0 || col >= win->cols)
        return ;
    (win->screen + row * win->cols + col)->settings = settings;
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
            //screen[i * win->cols + j].settings = "3m█";
            screen[i * win->cols + j].settings = "39m.";
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

    double dz = 0;
    double dt = 1.0/FPS;
    while(1)
    {
        dz += 1*dt;
        reset_screen(win);
        // Draw points with larger Z values (closer to camera
        render_screen(win);
        usleep(1000000/FPS);
    }

    clean_memory_list(&win->memory);
}
