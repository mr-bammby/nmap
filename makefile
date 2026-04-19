CC = gcc 
CCFLAGS = -g

RM = rm -f 

# Directories
ARG_PARSER_DIR		= argument_parser
MAIN_DIR			= main
PROTOCOLS_DIR		= protocols
SCANS_DIR			= scans

SRCD = $(ARG_PARSER_DIR)/src \
		  $(MAIN_DIR)/src \
		  $(PROTOCOLS_DIR)/src \

SRCS	= $(foreach dir,$(SRCD),$(wildcard $(dir)/*.c))

OBJD		= ./obj/

OBJF	= $(patsubst %.c,$(OBJD)%.o,$(SRCS))
HDRS	= $(foreach dir,$(SRCD),$(wildcard $(dir)/../inc/*.h $(dir)/../inc_priv/*.h))

# Include Flags
INCLUDES = -I$(ARG_PARSER_DIR)/inc -I$(ARG_PARSER_DIR)/inc_priv \
           -I$(MAIN_DIR)/inc -I$(PROTOCOLS_DIR)/inc -I$(SCANS_DIR)/inc

LIBS = -lpcap

NAME = ft_nmap.out

$(OBJD)%.o: %.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) $(INCLUDES) -c -o $@ $<

$(NAME): $(OBJF)
	$(CC) $(CCFLAGS) $(INCLUDES) -o $(NAME) $(OBJF) $(LIBS)

all: fclean ${NAME} 

clean:
	${RM} -r ${OBJD}

fclean: clean
	${RM} ${NAME} 

re: fclean all 

.PHONY: all clean fclean re