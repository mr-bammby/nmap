CC = gcc 
CCFLAGS = -g
DEBUG_LEVEL ?= 0
CPPFLAGS = -DDEBUG_LEVEL=$(DEBUG_LEVEL)
.DEFAULT_GOAL := all

RM = rm -f 

# Directories
ARG_PARSER_DIR		= argument_parser
MAIN_DIR			= main
PROTOCOLS_DIR		= protocols
SCANS_DIR			= scans
RESULT_PRINTER_DIR	= result_printer
THREADING_DIR		= threading
COMMON_DIR			= common

SRCD = $(ARG_PARSER_DIR)/src \
		  $(MAIN_DIR)/src \
		  $(PROTOCOLS_DIR)/src \
		  $(SCANS_DIR)/src \
		  $(RESULT_PRINTER_DIR)/src \
		  $(THREADING_DIR)/src \
		  $(COMMON_DIR)/src

SRCS	= $(filter-out threading/src/th_main.c threading/src/th_main_queue.c,$(foreach dir,$(SRCD),$(wildcard $(dir)/*.c)))

OBJD		= ./obj/
DEBUG_FLAG = $(OBJD)/.debug_level_$(DEBUG_LEVEL)

OBJF	= $(patsubst %.c,$(OBJD)%.o,$(SRCS))
HDRS	= $(foreach dir,$(SRCD),$(wildcard $(dir)/../inc/*.h $(dir)/../inc_priv/*.h))
TEST_OBJF = ./obj/main/src/multi_thread_test_main.o

# Include Flags
INCLUDES = -I$(ARG_PARSER_DIR)/inc -I$(ARG_PARSER_DIR)/inc_priv \
           -I$(MAIN_DIR)/inc -I$(PROTOCOLS_DIR)/inc -I$(SCANS_DIR)/inc \
		   -I$(RESULT_PRINTER_DIR)/inc -I$(RESULT_PRINTER_DIR)/inc_priv \
		   -I$(COMMON_DIR)/inc -I$(THREADING_DIR)/inc

LIBS = -lpcap -pthread

NAME = ft_nmap.out
TEST_MAIN = multi_thread_test.out

$(DEBUG_FLAG):
	@mkdir -p $(OBJD)
	@rm -f $(OBJD)/.debug_level_*
	@touch $@

$(OBJD)%.o: %.c $(HDRS) $(DEBUG_FLAG)
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CCFLAGS) $(INCLUDES) -c -o $@ $<

$(NAME): $(filter-out $(TEST_OBJF),$(OBJF))
	$(CC) $(CPPFLAGS) $(CCFLAGS) $(INCLUDES) -o $(NAME) $(filter-out $(TEST_OBJF),$(OBJF)) $(LIBS)

$(TEST_MAIN): $(filter-out ./obj/main/src/main.o ./obj/main/src/multi_thread_test_main.o,$(OBJF)) $(TEST_OBJF)
	$(CC) $(CPPFLAGS) $(CCFLAGS) $(INCLUDES) -o $(TEST_MAIN) $(filter-out ./obj/main/src/main.o ./obj/main/src/multi_thread_test_main.o,$(OBJF)) $(TEST_OBJF) $(LIBS)

all: ${NAME} 

clean:
	${RM} -r ${OBJD}

fclean: clean
	${RM} ${NAME} ${TEST_MAIN}

debug:
	$(MAKE) DEBUG_LEVEL=4 $(NAME)

re: fclean all 

.PHONY: all clean fclean re