#include "../includes/header.h"

extern t_mesh cube;
extern t_mesh cuby;
t_win *win;

 // Increase this to reduce FOV (zoom in), decrease to increase FOV
/*
printf("\033[%d;%dH", i, j);
printf("\033[37;41m█");
*/

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

void    rotate_yz(float *x, float *y, float *z, float angle)
{
    float   old_y = *y;
    float   old_z = *z;

    float c = cos(angle);
    float s = sin(angle);
    *y = old_y * c - old_z * s;
    *z = old_y * s + old_z * c;
    (void)x;
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
/*
float cube[8][3] = {
    {5, 5, 5},
    {-5, 5, 5},
    {5, -5, 5},
    {-5, -5, 5},
    {5, 5, -5},
    {-5, 5, -5},
    {5, -5, -5},
    {-5, -5, -5}
    };*/
void    project_cube(t_win *win, float cube[8][3])
{
    int i;
    static float angle = 0.0f;
    float v[8][3];
    float x, y, z;
    i = -1;

    memcpy(v, cube, sizeof(v));
    angle += 0.05;
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
        project_pixel_3d(win,x, y, z, "32m█");
    }
}

void    enter_raw_mode(t_win *win)
{
    struct termios new_tio;

    tcgetattr(STDIN_FILENO, &win->old_tio);
    new_tio = win->old_tio;
    new_tio.c_lflag &=(~ICANON & ~ECHOE);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}
void    exit_raw_mode(t_win *win)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &win->old_tio);
}

void    spin_model(t_mesh *cube)
{

    float   angle = 0.05f;
    int i = -1;

    t_vertex *vertex;

    while(++i < cube->VertexCount)
    {
        vertex = cube->Vbuffer + i;
        rotate_xz(&vertex->x, &vertex->y, &vertex->z, angle);
        rotate_yz(&vertex->x, &vertex->y, &vertex->z, angle);
    }
}


int main(void)
{
    t_mem_list *memory;

    if(init_memory_list(&memory) == FAILURE)
        return (1);
    win = x_malloc(&memory, sizeof(*win));
    init_win(win, &memory);
    //update_window_size(win);
    signal(SIGWINCH, &handle_sigwinc);
    win->cam_z = -100.0f;
    enter_raw_mode(win); // not working yet;
    while(1)
    {
        reset_screen(win);
        //catch_input(win);
        //project_cube(win, cube);
        load_model(win, &cube);
        //load_model(win, &cuby);
        
        spin_model(&cube);
        render_screen(win);
        usleep(1000000/FPS);
    }
    exit_raw_mode(win);
    clean_memory_list(&win->memory);
}
