#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <termios.h>


# define FAILURE 1
# define SUCCESS 0
# define CLEAR_SCREEN printf("\033[2J")
# define RESET printf("\033[0m")
# define FPS 60
# define FOCAL_LENGTH 150  // Increase this to reduce FOV (zoom in), decrease to increase FOV

typedef struct s_mem_list
{
	void	*address;
	struct s_mem_list *next;
	struct s_mem_list *prev;
}	t_mem_list;

typedef	struct s_screen
{
	int	row;
	int	col;
	char	*settings;
}	t_screen;

typedef	struct s_vertex
{
	float x;
	float y;
	float z;
	char *color;

}	t_vertex;

typedef struct s_mesh
{
	int 		VertexCount;
	int			IndexCount;
	t_vertex	*Vbuffer;
	int			*indexBuffer;
} t_mesh;

typedef struct s_win
{
	char	*color;
	char	*opacity;
	int		rows;
	int		cols;
	t_screen 	*screen;
	t_mem_list	*memory;
	float	cam_x;
	float	cam_y;
	float	cam_z;
	float	cam_distance;
	struct termios old_tio;
}	t_win;


void	*x_malloc(t_mem_list **mem, size_t size);
int	init_memory_list(t_mem_list **m);
void	clean_memory_list(t_mem_list **mem);


void    init_win(t_win *win, t_mem_list **memory);
void    update_window_size(t_win *win);
t_screen    *init_screen(t_win *win);
void    print_to_terminal(int row, int col, char* msg);

char    *ft_strdup(t_win *win, const char *s);
int ft_strcpy(const char *src, char *dst);
void    project_pixel_3d(t_win *win, int x, int y, int z, char *settings);
void    project_pixel_2d(t_win *win, int row, int col, char *settings);

void    cvt_3d_to_2d(float *x, float *y, float *z);
void  transform_coord(t_win *win, int *row, int *col);
void    reset_screen(t_win *win);
void    render_screen(t_win *win);

void    rotate_xz(float *x, float *y, float *z, float angle);
int    load_model(t_win *win, t_mesh *mesh);

void    handle_sigwinc(int sig);


/* enter and exit canoinical mode in terminal*/

void    exit_raw_mode(t_win *win);
void	enter_raw_mode(t_win *win);
