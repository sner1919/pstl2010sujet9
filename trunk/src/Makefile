CC = g++
CFLAGS = -Wall
LDFLAGS =
LDLIBS =
INCLUDES =
PREPROCESS_AND_COMPIL = $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $*.o
LINK = $(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
PROGS = run

all : $(PROGS)

clean :
	rm -f $(PROGS) *.o

run : Main.o Matrix.o
	$(LINK)

%.o : %.cpp
	$(PREPROCESS_AND_COMPIL)

.PHONY: all clean