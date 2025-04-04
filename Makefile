
NAME = infinite_metro


SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/UIManager/UIManager.cpp \
       $(SRC_DIR)/Station/Station.cpp

OBJS = $(SRCS:.cpp=.o)

CXX = g++
CXXFLAGS = -I$(INC_DIR) -std=c++17 -Wall -Wextra -Werror
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system


all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
