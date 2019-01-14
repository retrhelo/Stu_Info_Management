/* written by joel retrhelo */

#include "interface.h"

char buf[BUF_SIZE];

void read_line(char *str)
{
	int i = 0;

	while ((buf[i] = getchar()) != '\n') 
		i ++;
	buf[i] = '\0';

	/* if str != NULL, then copy the data into str */
	if (str != NULL) {
		i = 0;
		while (buf[i]) {
			*str++ = buf[i++];
		}
		*str = '\0';
	}
}

/* show the menu */
void show_menu(void)
{
	system(CLEAR);		/* clear the screen first */
	printf("Welcome to the Student Information Management System\n");
	printf("You may enter \"help\" for a list of commands available\n");
	printf("total: %d student(s)\n", stu_num);
}

void show_stu_info(s_stu *stu)
{
	int i;

	putchar('\n');
	printf("%-8s: %s\n", "name", stu->name);
	printf("%-8s: %s\n", "id", stu->id);
	/* print scores */
	for (i = 0; i < SUBJECT_NUM; i ++) {
		printf("%-8s: %d", subject_names[i], stu->scores[i]);
		if ((i + 1) % 2 == 0) 
			putchar('\n');
		else 
			printf("\t\t");
	}
	printf("%-8s: %d\n", "total", stu->total);
	printf("%-8s: %.2lf\n", "average", stu->average);
}
