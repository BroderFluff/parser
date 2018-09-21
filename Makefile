BIN := parser
SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=obj/%.o)
#OBJ := $(addprefix obj/, $(notdir $(SRC)))
# Pre-processor flags
CPPFLAGS += \
	-Iinclude/
# Compiler flags
CFLAGS += \
	-Wall \
	-O2
# Linker flags
LDFLAGS += 
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
