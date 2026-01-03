#include "../includes/header.h"



int buffer_len(int *buffer)
{
    int i;

    if (!buffer)
        return (FAILURE);
    i = -1;
    while (buffer[++i]) ;
    return (i);
}

int verify_model(t_mesh *mesh)
{
    if (!mesh || !mesh->Vbuffer || !mesh->indexBuffer)
        return (FAILURE);
    if (buffer_len(mesh->indexBuffer) % 3 != 0)
        return (FAILURE);
    return (SUCCESS);
}



void load_mesh_to_screen(t_win *win, t_mesh *mesh)
{
    int i;
    t_vertex *buf;
    float x, y, z;

    if (!win || !mesh)
        return ;
    i = -1;
    while(++i < mesh->VertexCount)
    {
        buf = mesh->Vbuffer + i;
        // Apply camera offset - subtract camera position to move mesh relative to camera
        x = buf->x - win->cam_x;
        y = buf->y - win->cam_y; // this is imp as it allows me to move around
        z = buf->z - win->cam_z + win->cam_distance;
        project_pixel_3d(win, x, y, z, buf->color);
    }

}

int    load_model(t_win *win, t_mesh *mesh)
{
    if (verify_model(mesh) == FAILURE)
        return (FAILURE);
    load_mesh_to_screen(win , mesh);
    return (SUCCESS);
}