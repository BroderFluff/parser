BIN := parser
SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=obj/%.o)

# Pre-processor flags
CPPFLAGS += \
	-Iinclude/

# Compiler flags
CFLAGS += \
	-O3 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Wformat \
	-Wwrite-strings \
	-Werror \
	-Wconversion \
	-Wpointer-arith \
	-Wshadow \
	-DNDEBUG

# Linker flags
LDFLAGS += 

# External libs
LDLIBS +=

.PHONY: all clean

all: $(BIN)

debug: CFLAGS += \
	-O3 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Wformat \
	-Wwrite-strings \
	-Werror \
	-Wconversion \
	-Wpointer-arith \
	-Wshadow \
	-Og \
	-g \
	-DDEBUG \
	-fsanitize=address \
	-fsanitize=signed-integer-overflow
debug: LDFLAGS += \
	-fsanitize=address \
	-fsanitize=signed-integer-overflow
debug: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

obj/%.o: src/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) obj/*
