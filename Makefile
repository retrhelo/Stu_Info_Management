# written by joel rethelo
# finish time: Jan 13, 2019

# path for the final release
RELEASE_PATH = ../release

# target name
TARGET_NAME = stu_info

# compiler
CC = gcc

install: main.o storage.o interface.o
	$(CC) main.o storage.o interface.o -o $(RELEASE_PATH)/$(TARGET_NAME)
	make clean

# compile each file
.o: *.c
	$(CC) -c *.c

# remove the object files
clean: *.o
	rm *.o
