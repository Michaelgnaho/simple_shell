#include "shell.h"


/**
 * md_get_environ - returns the string array copy of the environment
 * @md_info: Structure containing potential arguments. Used to maintain
 *           constant function prototype.
 * Return: Always 0
 */
char **md_get_environ(md_info_t *md_info)
{
    if (!md_info->environ || md_info->env_changed)
    {
        md_info->environ = list_to_strings(md_info->env);
        md_info->env_changed = 0;
    }

    return (md_info->environ);
}

/**
 * md_unsetenv - Remove an environment variable
 * @md_info: Structure containing potential arguments. Used to maintain
 *            constant function prototype.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int md_unsetenv(md_info_t *md_info, char *var)
{
    list_t *node = md_info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            md_info->env_changed = delete_node_at_index(&(md_info->env), i);
            i = 0;
            node = md_info->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return (md_info->env_changed);
}

/**
 * md_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @md_info: Structure containing potential arguments. Used to maintain
 *           constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int md_setenv(md_info_t *md_info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return (0);

    buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return (1);
    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = md_info->env;
    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            md_info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    add_node_end(&(md_info->env), buf, 0);
    free(buf);
    md_info->env_changed = 1;
    return (0);
}
 