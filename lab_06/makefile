CC := gcc

CFLAGS := -Wextra -Wpedantic -Wall -std=gnu99 -g3 -O0
ifeq ($(mode), time)
	CFLAGS += -DALGCOMP
else
endif

SRC_PATH := ./src
OUT_PATH := ./out
INC_PATH := ./inc
IMG_PATH := ./img

SRCS := $(wildcard $(SRC_PATH)/*.c)
OBJS := $(subst $(SRC_PATH), $(OUT_PATH), $(SRCS:.c=.o))

app.exe : $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

$(OUT_PATH)/%.o : $(SRC_PATH)/%.c $(INC_PATH)/*.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean

clean :
	rm $(OUT_PATH)/*.o *.exe *.txt
	rm $(IMG_PATH)/*
