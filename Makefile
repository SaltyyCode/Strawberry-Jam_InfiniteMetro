CC = g++
CFLAGS = -Wall
EXEC_NAME = my_executable
OBJ_FILES = main.o hellofunc.o

all: $(EXEC_NAME)

$(EXEC_NAME): $(OBJ_FILES)
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@