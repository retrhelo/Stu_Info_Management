/* written by joel retrhelo */
/* finish time: Jan 13, 2019 */

/* includes the functions for storage */

#ifndef _STORAGE_H
#define _STORAGE_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SUBJECT_NUM 4
#define TEXT_LENGTH 32

typedef struct stu_info {
	char name[TEXT_LENGTH];		/* name of student */
	char id[TEXT_LENGTH];		/* id number of student */
	int scores[SUBJECT_NUM];	/* scores of student */
	int total;					/* sum of scores */
	double average;				/* average score */
	struct stu_info *next;		/* pointer to next student */
} s_stu;

extern char subject_names[SUBJECT_NUM][TEXT_LENGTH];

/* the number of students stored */
extern int stu_num;

/* the head of student linked list */
extern s_stu *head;

/* create student file */
s_stu *create_stu(void);

/* remove student file */
void remove_stu(s_stu *stu);

/* edit student file */
void edit_stu(s_stu *stu);

/* search student and return the index of student */
/* info can be either name of id of student */
/* search_stu() will check info, distinguish whether it 
 * is a name or an id, and then compare it with the 
 * information stored, if successfully, it returns the pointer
 * of the student, otherwise returns NULL
 */
s_stu *search_stu(char *info);

#define DEFAULT_FILE "storage.txt"
#define LINE "--------------------\n"		/* the line used for seperating */

/* save student info into a file
 * save_stu() creates or overwrite files in STORE_DIRECTORY,
 * write all the information into the file in text form
 * it returns 0 if successfully written, -1 if failed
 */
int write_stu(void);

#include "interface.h"

#endif
