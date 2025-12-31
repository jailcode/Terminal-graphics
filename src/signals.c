#include "../includes/header.h"

extern t_win *win;
void    handle_sigwinc(int sig)
{
    (void)sig;
    if (win)
        update_window_size(win);
}