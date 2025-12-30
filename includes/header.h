#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

# define FAILURE 1
# define SUCCESS 0

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

typedef struct s_win
{
	char	*color;
	char	*opacity;
	int	rows;
	int	cols;
	t_screen *screen;
	t_mem_list *memory;
}	t_win	;


void	*x_malloc(t_mem_list **mem, size_t size);
int	init_memory_list(t_mem_list **m);
void	clean_memory_list(t_mem_list **mem);


void    init_win(t_win *win, t_mem_list **memory);
void    update_window_size(t_win *win);
t_screen    *init_screen(t_win *win);
void    print_to_terminal(int row, int col, char* msg);

char    *ft_strdup(t_win *win, const char *s);
int ft_strcpy(const char *src, char *dst);