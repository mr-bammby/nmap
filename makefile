CC = gcc 
CCFLAGS = -g
CPPFLAGS =

RM = rm -f 

# Directories
ARG_PARSER_DIR		= argument_parser
MAIN_DIR			= main
PROTOCOLS_DIR		= protocols
SCANS_DIR			= scans
RESULT_PRINTER_DIR	= result_printer
THREADING_DIR		= threading
SRCD = $(ARG_PARSER_DIR)/src \
		  $(MAIN_DIR)/src \
		  $(PROTOCOLS_DIR)/src \
		  $(SCANS_DIR)/src \
		  $(RESULT_PRINTER_DIR)/src \
		  $(THREADING_DIR)/src \

SRCS	= $(foreach dir,$(SRCD),$(wildcard $(dir)/*.c))

OBJD		= ./obj/

OBJF	= $(patsubst %.c,$(OBJD)%.o,$(SRCS))
HDRS	= $(foreach dir,$(SRCD),$(wildcard $(dir)/../inc/*.h $(dir)/../inc_priv/*.h))

# Include Flags
INCLUDES = -I$(ARG_PARSER_DIR)/inc -I$(ARG_PARSER_DIR)/inc_priv \
           -I$(MAIN_DIR)/inc -I$(PROTOCOLS_DIR)/inc -I$(SCANS_DIR)/inc \
		   -I$(RESULT_PRINTER_DIR)/inc -I$(RESULT_PRINTER_DIR)/inc_priv

LIBS = -lpcap -pthread

NAME = ft_nmap.out

$(OBJD)%.o: %.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CCFLAGS) $(INCLUDES) -c -o $@ $<

$(NAME): $(OBJF)
	$(CC) $(CPPFLAGS) $(CCFLAGS) $(INCLUDES) -o $(NAME) $(OBJF) $(LIBS)

all: fclean ${NAME} 

clean:
	${RM} -r ${OBJD}

fclean: clean
	${RM} ${NAME}

debug: CPPFLAGS += -DDEBUG=1
debug: fclean $(NAME)

re: fclean all 

.PHONY: all clean fclean re