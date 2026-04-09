CC = gcc 
CCFLAGS = -g

RM = rm -f 

# Directories
ARG_PARSER_DIR		= argument_parser
MAIN_DIR			= main
PROTOCOLS_DIR		= protocols
SCANS_DIR			= scans

# Include Flags
INCLUDES = -I$(ARG_PARSER_DIR)/inc -I$(ARG_PARSER_DIR)/inc_priv \
           -I$(MAIN_DIR)/inc -I$(PROTOCOLS_DIR)/inc -I$(SCANS_DIR)/inc

LIBS = -lpcap

NAME = ft_nmap.out

$(NAME):
	${CC} ${CCFLAGS} ${INCLUDES} -o ${NAME} \
	${ARG_PARSER_DIR}/src/*.c \
	${MAIN_DIR}/src/*.c \
	${PROTOCOLS_DIR}/src/*.c \
	${LIBS} 

all: fclean ${NAME} 

clean:
	${RM} *.o 

fclean: clean
	${RM} ${NAME} 

re: fclean all 

.PHONY: all clean fclean re