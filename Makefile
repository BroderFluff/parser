BIN := parser
SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=obj/%.o)

# Pre-processor flags
CPPFLAGS += \
	-Iinclude/

# Compiler flags
CFLAGS += \
	-O \
	-g \
	-fsanitize=address \
	-Wall \
	-Wextra \
	-pedantic

# Linker flags
LDFLAGS += -fsanitize=address

# External libs
LDLIBS +=

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

obj/%.o: src/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) obj/*
