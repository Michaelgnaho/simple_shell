#include "shell.h"
#include <unistd.h>
/**
 * dis_prompt - func that display prompt
 * Return : 0
 */

void dis_prompt(void)
{
	write(1, "md_shell$  ", 10);

}
