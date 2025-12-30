#include "../includes/header.h"


# define CLEAR_SCREEN printf("\033[2J")
# define RESET printf("\033[0m")
# define FPS 60
# define FOCAL_LENGTH 50  // Increase this to reduce FOV (zoom in), decrease to increase FOV
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
void    project_pixel_2d(t_win *win, int row, int col, char *settings)
{
    if (!win)
        return ;
    transform_coord(win, &row, &col);
    if (row < 0 || row >= win->rows || col < 0 || col >= win->cols)
        return ;
    (win->screen + row * win->cols + col)->settings = settings;
}

void    project_pixel_3d(t_win *win, int x, int y, int z, char *settings)
{
    int py, px;
    if (!win)
        return ;
    if (z <= 0.1f)
        return ;
    py = (y * FOCAL_LENGTH) / z;
    px = (x * FOCAL_LENGTH) / z;
    project_pixel_2d(win, py, px, settings);
}

void    reset_screen(t_win *win)
{
    int i, j;
    t_screen *screen;
    
    if (!win)
        return ;
    update_window_size(win);
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

void    rotate_xz(float *x, float *y, float *z, float angle)
{
    float   old_x = *x;
    float   old_z = *z;

    float c = cos(angle);
    float s = sin(angle);
    *x = old_x * c - old_z * s;
    *z = old_x * s + old_z * c;
    (void)y;
}

void    translate_cube(int v[8][3])
{
    int i;

    i = 0;
    while(i < 8)
    {
        v[i][1] += 2;
        i++;
    }
}

float cube[8][3] = {
    {5, 5, 5},
    {-5, 5, 5},
    {5, -5, 5},
    {-5, -5, 5},
    {5, 5, -5},
    {-5, 5, -5},
    {5, -5, -5},
    {-5, -5, -5}
    };
void    project_cube(t_win *win, float cube[8][3])
{
    int i;
    static float angle = 0.0f;
    float v[8][3];
    float x, y, z;
    i = -1;

    memcpy(v, cube, sizeof(v));
    angle += 0.1;
    if (angle >= 2 * 3.148)
        angle = 0;
//    translate_cube(v);
    while(++i < 8)
    {
        x = v[i][0];
        y = v[i][1];
        z = v[i][2];
         // Increased from 0.1f
        rotate_xz(&x, &y, &z, angle);
        z += 50.0f;
        project_pixel_3d(win,x, y, z, "32m$");
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
        project_cube(win, cube);
        render_screen(win);
        usleep(1000000/FPS);
    }

    clean_memory_list(&win->memory);
}
