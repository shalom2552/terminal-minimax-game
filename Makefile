CFLAGS = -std=c99 -Wall -Wextra -pedantic -g

TARGET = game

SRC = main.c game_display.c game_logic.c game_random.c
SRC += game_input.c game_ai.c game_menu.c game_main_menu.c

OBJECTS = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	gcc $(CFLAGS) -o $(TARGET) $(OBJECTS) -lm

clean:
	rm -f  $(OBJECTS) $(TARGET)

.PHONY: all clean
