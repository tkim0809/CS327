CC = gcc
CXX = g++
ECHO = echo
RM = rm -f

TERM = "S2023"

CFLAGS = -Wall -ggdb -funroll-loops -DTERM=$(TERM)
CXXFLAGS = -Wall -ggdb -funroll-loops -DTERM=$(TERM)

LDFLAGS = -lncurses

BIN = poke327
OBJS = poke327.o heap.o character.o io.o db_parse.o

all: $(BIN) etags

$(BIN): $(OBJS)
	@$(ECHO) Linking $@
	@$(CXX) $^ -o $@ $(LDFLAGS)

-include $(OBJS:.o=.d)

%.o: %.c
	@$(ECHO) Compiling $<
	@$(CC) $(CFLAGS) -MMD -MF $*.d -c $<

%.o: %.cpp
	@$(ECHO) Compiling $<
	@$(CXX) $(CXXFLAGS) -MMD -MF $*.d -c $<

.PHONY: all clean clobber etags

clean:
	@$(ECHO) Removing all generated files
	@$(RM) *.o $(BIN) *.d TAGS core vgcore.* gmon.out

clobber: clean
	@$(ECHO) Removing backup files
	@$(RM) *~ \#* *pgm

etags:
	@$(ECHO) Updating TAGS
	@etags *.[ch]
