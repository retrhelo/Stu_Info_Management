# written by joel rethelo
# finish time: Jan 13, 2019
# modification
# Dec 29, 2021: retrhelo <artyomliu@foxmail.com>: modify rules.

# path for the final release
RELEASE_PATH ?= .

# target name
TARGET_NAME = stu_info

# compiler
CC = gcc

install: main.o storage.o interface.o
	$(CC) main.o storage.o interface.o -o $(RELEASE_PATH)/$(TARGET_NAME)

# compile each file
.o: *.c
	$(CC) -c *.c

# remove the object files
clean:
	rm *.o $(RELEASE_PATH)/$(TARGET_NAME)
