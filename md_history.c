#include "shell.h"

#include "shell.h"

/**
 * md_get_history_file - Retrieves the history file path
 * @md_info: Shell information struct
 *
 * Return: Allocated string containing the history file path
 */
char *md_get_history_file(md_info_t *md_info)
{
    char *buf, *dir;

    dir = md_getenv(md_info, "HOME=");
    if (!dir)
        return (NULL);

    buf = md_malloc(sizeof(char) * (md_strlen(dir) + md_strlen(HIST_FILE) + 2));
    if (!buf)
        return (NULL);

    buf[0] = 0;
    md_strcpy(buf, dir);
    md_strcat(buf, "/");
    md_strcat(buf, HIST_FILE);

    return (buf);
}

/**
 * md_write_history - Creates or appends to the history file
 * @md_info: Shell information struct
 *
 * Return: 1 on success, else -1
 */
int md_write_history(md_info_t *md_info)
{
    ssize_t fd;
    char *filename = md_get_history_file(md_info);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    md_free(filename);

    if (fd == -1)
        return (-1);

    for (node = md_info->history; node; node = node->next)
    {
        md_putsfd(node->str, fd);
        md_putfd('\n', fd);
    }

    md_putfd(BUF_FLUSH, fd);
    close(fd);

    return (1);
}

/**
 * md_read_history - Reads history from the file
 * @md_info: Shell information struct
 *
 * Return: Histcount on success, 0 otherwise
 */
int md_read_history(md_info_t *md_info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = md_get_history_file(md_info);

    if (!filename)
        return (0);

    fd = open(filename, O_RDONLY);
    md_free(filename);

    if (fd == -1)
        return (0);

    if (!fstat(fd, &st))
        fsize = st.st_size;

    if (fsize < 2)
        return (0);

    buf = md_malloc(sizeof(char) * (fsize + 1));
    if (!buf)
        return (0);

    rdlen = read(fd, buf, fsize);
    buf[fsize] = 0;

    if (rdlen <= 0)
        return (md_free(buf), 0);

    close(fd);

    for (i = 0; i < fsize; i++)
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            md_build_history_list(md_info, buf + last, linecount++);
            last = i + 1;
        }

    if (last != i)
        md_build_history_list(md_info, buf + last, linecount++);

    md_free(buf);
    md_info->histcount = linecount;

    while (md_info->histcount-- >= HIST_MAX)
        md_delete_node_at_index(&(md_info->history), 0);

    md_renumber_history(md_info);
    return (md_info->histcount);
}

/**
 * md_build_history_list - Adds an entry to the history linked list
 * @md_info: Shell information struct
 * @buf: Buffer
 * @linecount: History line count
 *
 * Return: Always 0
 */
int md_build_history_list(md_info_t *md_info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (md_info->history)
        node = md_info->history;

    md_add_node_end(&node, buf, linecount);

    if (!md_info->history)
        md_info->history = node;

    return (0);
}

/**
 * md_renumber_history - Renumbers the history linked list after changes
 * @md_info: Shell information struct
 *
 * Return: The new histcount
 */
int md_renumber_history(md_info_t *md_info)
{
    list_t *node = md_info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return (md_info->histcount = i);
}
