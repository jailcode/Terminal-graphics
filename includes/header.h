#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <stdlib.h>

# define FAILURE 1
# define SUCCESS 0

typedef struct s_mem_list
{
	void	*address;
	struct s_mem_list *next;
	struct s_mem_list *prev;
}	t_mem_list;

typedef struct s_win
{
	char	*color;
	char	*opacity;
	int	rows;
	int	cols;
	t_mem_list *memory;
}	t_win	;


typedef	struct s_coord
{
	int	row;
	int	col;
}	t_coord;



void	init_win(t_win *win);

void	*x_malloc(t_mem_list **mem, size_t size);
int	init_memory_list(t_mem_list **m);
void	clean_memory_list(t_mem_list **mem);

void	update_window_size(t_win *win, int fd);