/* writthe by joel retrhelo
 * finish time: Jan 13, 2019
 */

/* interface.h is for user interface, including some functions 
 * to show students' information, the menu and read user's input
 */

#ifndef _INTERFACE_H
#define _INTERFACE_H

#include <stdlib.h>
#include <stdio.h>
#include "storage.h"

/* the system command for clearing the screen */
#define CLEAR "clear"

/* size of buf */
#define BUF_SIZE 32

extern char buf[BUF_SIZE];

/* read a line from the input, first store the input into buf,
 * if str != NULL, copy the content of buf into str
 */
void read_line(char *str);

/* display the menu */
void show_menu(void);

/* display student info */
void show_stu_info(s_stu *stu);

#endif
