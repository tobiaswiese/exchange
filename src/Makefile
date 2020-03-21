CC      := gcc
CFLAGS  := -Wall
LDFLAGS :=

CFLAGS  += -DVERSIN="\"$(shell git describe --dirty --always)\""

TARGETS := exchange
MAINS   := $(addsuffix .o, $(TARGETS))
OBJ     := $(MAINS)

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -rf $(OBJ) $(TARGETS)

$(TARGETS): % : %.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
