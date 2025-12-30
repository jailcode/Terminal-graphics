#include "../includes/header.h"

void    update_window_size(t_win *win)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    win->cols = w.ws_col;
    win->rows = w.ws_row;
}

int     ft_strlen(const char *s)
{
    int i;

    i = -1;
    while(s[++i]);
    return (i);
}

char    *ft_strdup(t_win *win, const char *s)
{
    int len;
    int i;
    char    *des;

    if (!s)
        return (NULL);
    len = ft_strlen(s);
    des = x_malloc(&win->memory, sizeof(*des) * (len + 1));
    if (!des)
        return (NULL);
    i = -1;
    while(++i < len)
        des[i] = s[i];
    des[i] = '\0';
    return (des);
}

int ft_strcpy(const char *src, char *dst)
{
    int i;
    if (!src || !dst)
        return (0);
    i = 0;
    while(src[i++])
    {
        dst[i] = src[i];
    }
    return (i);
}