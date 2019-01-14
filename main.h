/* written by joel retrhelo
 * finish time: Jan 13, 2019
 */

#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include "storage.h"
#include "interface.h"

/* the list of commands */
extern char *command_list[];

/* recognise input choose the command to execute */
int execute_input(char *str);

#endif
