#include "minishell.h"

int msh_read_line(char **line)
{
    int     status;

    status = 0;
    status = get_next_line(1, line);
    return (status);
}
