# **************************************************************************** #
#                                                                              #
#                Makefile for GlobalBanksters United                           #
#                                                                              #
# **************************************************************************** #

NAME		= account

# CXX, not CC: CC conventionally names the C compiler, and a peer typing the
# entirely ordinary `make CC=gcc` would otherwise link C++ objects with the C
# driver. A command-line override beats a makefile assignment.
CXX			= c++

# -std=c++98 is REQUIRED here, not decorative. The provided tests.cpp uses
# std::mem_fun_ref, deprecated in C++11 and removed in C++17; with -Werror any
# default standard >= C++11 turns that into a hard build failure. Removing this
# flag breaks the build even though Account.cpp itself is standard-clean.
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
RM			= rm -f

SRCS		= Account.cpp \
			  tests.cpp

OBJS		= $(SRCS:.cpp=.o)

HEADERS		= Account.hpp

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o:		%.cpp $(HEADERS)
			$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
