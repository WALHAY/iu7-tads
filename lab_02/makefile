CC := gcc

CFLAGS := -Werror -Wextra -Wpedantic -Wall -std=c99 -g3

SRCS := $(wildcard *.c)

OBJS := $(SRCS:.c=.o)

app.exe : $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c *.h
	$(CC) $(CFLAGS) -c $<

clean :
	rm *.o *.exe


