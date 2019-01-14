/* written by joel retrhelo */

#include "storage.h"


char subject_names[SUBJECT_NUM][TEXT_LENGTH] = {
	"Math", "English", "Chinese", "Physics"
};

/* the size of memory required for each student */
static const size_t UNIT_SIZE = sizeof(s_stu);

int stu_num = 0;

s_stu *head = NULL;

s_stu *create_stu(void)
{
	s_stu *tmp;
	int i, j;
	int flag_num;

	/* if it is the first item of linked list */
	if (head == NULL) {
		head = (s_stu*)malloc(UNIT_SIZE);
		tmp = head;
	}
	else {	/* otherwise */
		tmp = head;
		while (tmp->next != NULL) 
			tmp = tmp->next;
		tmp->next = (s_stu*)malloc(UNIT_SIZE);
		tmp = tmp->next;
	}
	/* write information onto the structure */
	printf("student name: ");
	read_line(NULL);
	strcpy(tmp->name, buf);
	printf("student id: ");
	read_line(NULL);
	strcpy(tmp->id, buf);
	for (i = tmp->total = 0; i < SUBJECT_NUM; i ++) {
		printf("%s: ", subject_names[i]);
		do {	/* make sure the input was valid */
			read_line(NULL);
			for (flag_num = j = 0; buf[j]; j ++) {
				if (!isdigit(buf[j])) {
					printf("invalid input, please enter again: ");
					flag_num = 1;
					break;
				}
			}
		} while (flag_num);
		tmp->scores[i] = atoi(buf);
		tmp->total += tmp->scores[i];
	}
	tmp->average = (double)(tmp->total) / SUBJECT_NUM;
	tmp->next = NULL;
	stu_num ++;

	return tmp;
}

void remove_stu(s_stu *stu)
{
	s_stu *tmp = head;
	s_stu *last;

	if (stu == head) {
		head = stu->next;
		free(stu);
	}
	else {
		while (tmp != stu) {
			last = tmp;
			tmp = tmp->next;
		}
		last->next = tmp->next;
		free(tmp);
	}
	stu_num --;
}

void edit_stu(s_stu *stu)
{
	int i, j;
	int flag_num;			/* if number is inputed correctly */

	/* name and id */
	printf("student name: ");
	read_line(NULL);
	if (buf[0] != '\0') 
		strcpy(stu->name, buf);
	printf("student id: ");
	read_line(NULL);
	if (buf[0] != '\0') 
		strcpy(stu->id, buf);
	/* enter scores */
	for (i = 0; i < SUBJECT_NUM; i ++) {
		printf("%s: ", subject_names[i]);
		do {
			read_line(NULL);
			if (buf[0] == '\0') break;
			for (j = flag_num = 0; buf[j]; j ++) {
				if (!isdigit(buf[j])) {
					printf("invalid input, please enter again: ");
					flag_num = 1;
					break;
				}
			}
		} while (flag_num);
		if (buf[0] != '\0') 
			stu->scores[i] = atoi(buf);
	}
	
	/* calculating the total score and average score */
	stu->total = 0;
	for (i = 0; i < SUBJECT_NUM; i ++) 
		stu->total += stu->scores[i];
	stu->average = (double)(stu->total) / SUBJECT_NUM;
}

s_stu *search_stu(char *info)
{
	int i;
	int flag_id;		/* if flag_id is 0, then search by name, if is non-zero, then search by id */
	s_stu *tmp = head;

	if (tmp == NULL) {
		printf("\e[31;1merror\e[0m: no item in the list!\n");
		return NULL;
	}
	/* determine the search mode */
	for (flag_id = i = 0; info[i]; i ++) {
		if (isdigit(info[i])) {
			flag_id = 1;
			break;
		}
	}

	/* start searching */
	while (tmp != NULL) {
		if (flag_id) {
			if (!strcmp(info, tmp->id)) 
				return tmp;
		}
		else {
			if (!strcmp(info, tmp->name)) 
				return tmp;
		}
		tmp = tmp->next;
	}

	return NULL;
}

int write_stu(void)
{
	FILE *store_p;
	char filename[TEXT_LENGTH];
	int i;
	s_stu *tmp = head;
	
	if (tmp == NULL) {
		printf("\e[31;1merror\e[m: no item in the list!\n");
		return -1;
	}
	printf("file name: ");
	read_line(NULL);
	if (buf[0] == '\0') 	/* if nothing was entered, then use the default name */
		strcpy(filename, DEFAULT_FILE);
	else 
		strcpy(filename, buf);

	/* test, see if the file already exists */
	store_p = fopen(filename, "r");
	if (store_p == NULL) 
		store_p = fopen(filename, "w");
	else {
		printf("warning: %s already exists, do you want to overwrite it? (Y/N) ", filename);
		read_line(NULL);
		if (buf[0] == 'Y' || buf[0] == 'y') 
			freopen(filename, "w", store_p);
		else 
			return -1;		/* abort writing file */
	}
	
	/* trying to write */
	if (store_p == NULL) {
		printf("\e[31;1merror\e[0m: failed to write %s!\n", filename);
		return -1;
	}
	else {
		fprintf(store_p, LINE);
		/* write the information of each student */
		while (tmp != NULL) {
			fprintf(store_p, "%-8s: %s\n", "name", tmp->name);
			fprintf(store_p, "%-8s: %s\n", "id", tmp->id);
			for (i = 0; i < SUBJECT_NUM; i ++) {
				fprintf(store_p, "%-8s: %d", subject_names[i], tmp->scores[i]);
				if ((i + 1) % 2 == 0) 
					fprintf(store_p, "\n");
				else 
					fprintf(store_p, "\t\t\t");
			}
			fprintf(store_p, "%-8s: %d\n", "total", tmp->total);
			fprintf(store_p, "%-8s: %.2lf\n", "average", tmp->average);
			fprintf(store_p, LINE);
			tmp = tmp->next;
		}
		/* finish writing and save */
		fclose(store_p);
		printf("writing finished\n");
		return 0;
	}
}
