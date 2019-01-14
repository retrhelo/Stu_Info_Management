#include "main.h"

int main(void)
{
	/* if everything works fin, status is 1
	 * if something wrong was entered, status is -1
	 * if user types "exit", then status is 0
	 */
	int status = 1;
	show_menu();
	while (status) {
		printf("> ");
		read_line(NULL);
		status = execute_input(buf);
		if (status == -1) {
			printf("\e[31;1merror\e[0m: invalid input!\n");
		}
	}

	printf("Thanks for using :)\n");

	return 0;
}

char *command_list[] = {
	"add", "edit", "remove", "save", "show", "clear", "exit", "help"
};

int execute_input(char *str)
{
	char arg[2][TEXT_LENGTH];
	int i, j;
	int num;

	/* initialize */
	arg[0][0] = arg[1][0] = '\0';

	i = 0;
	while (*str) {
		j = 0;
		if (*str == ' ') 	/* skip the space characters */
			str ++;
		while (*str != ' ' && *str != '\0') 
			arg[i][j ++] = *str ++;
		arg[i ++][j] = '\0';
	}
	
	i = j = 0;

	/* compare the command with the list */

	/* add */
	if (!strcmp(arg[0], "add")) {
		char info[2][TEXT_LENGTH];
		int scores[SUBJECT_NUM];
		/* if "add" comes with argument */
		if (arg[1][0] != '\0') 
			num = atoi(arg[1]);
		else 	/* if "add" has no argument, then by default create one student */
			num = 1;

		for (i = 0; i < num; i ++) 
			create_stu();
		return 1;
	}

	/* edit */
	if (!strcmp(arg[0], "edit")) {
		s_stu *tmp;
		if (arg[1][0] == '\0') 		/* if "edit" has no argument */
			return -1;
		tmp = search_stu(arg[1]);
		if (tmp == NULL) {
			printf("%s not found\n", arg[1]);
		}
		else {
			edit_stu(tmp);
		}
		return 1;
	}

	/* remove */
	if (!strcmp(arg[0], "remove")) {
		s_stu *tmp;
		if (arg[1][0] == '\0') 		/* if "remove" has no argument */
			return -1;
		tmp = search_stu(arg[1]);
		if (tmp == NULL) 
			printf("%s not found\n", arg[1]);
		else {
			remove_stu(tmp);
		}

		return 1;
	}

	/* save */
	if (!strcmp(arg[0], "save")) {
		write_stu();
		return 1;
	}

	/* show */
	if (!strcmp(arg[0], "show")) {
		int flag_all = 0;			/* whether show all students */
		s_stu *tmp = head;
		if (arg[1][0] == '\0') 		/* if "show" has no argument */
			flag_all = 1;
		else {
			if (!strcmp(arg[1], "all")) 
				flag_all = 1;
		}
		if (flag_all) {
			while (tmp != NULL) {
				show_stu_info(tmp);
				tmp = tmp->next;
			}
		}
		else {
			tmp = search_stu(arg[1]);
			if (tmp == NULL) 
				printf("%s not found\n", arg[1]);
			else 
				show_stu_info(tmp);
		}
		putchar('\n');

		return 1;
	}

	/* clear */
	if (!strcmp(arg[0], "clear")) {
		if (arg[1][0] != '\0') 
			return -1;
		show_menu();
		return 1;
	}

	/* exit */
	if (!strcmp(arg[0], "exit")) {
		if (arg[1][0] != '\0') 
			return -1;
		return 0;
	}

	/* help */
	if (!strcmp(arg[0], "help")) {
		if (arg[1][0] != '\0') 
			return -1;
		for (i = 0; strcmp(command_list[i], "help"); i ++) {
			printf("%s", command_list[i]);
			if ((i + 1) % 4 == 0) 
				putchar('\n');
			else 
				printf("\t\t");
		}
		printf("help\n");
		
		return 1;
	}

	return -1;
}
