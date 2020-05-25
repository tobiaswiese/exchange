INSTALL = install

VERSION = $(shell git describe --dirty --always)

CFLAGS  += -Wall -DVERSION="\"$(VERSION)\""
LDFLAGS +=

TARGETS := exchange
MAINS   := $(addsuffix .o, $(TARGETS))
OBJ     := $(MAINS)

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGETS)

.PHONY: install
install: $(TARGETS)
	$(INSTALL) -Dt "$(DESTDIR)$(prefix)/bin" $(TARGETS)

.PHONY: uninstall
uninstall:
	cd $(DESTDIR)$(prefix)/bin && rm -f $(TARGETS)


$(TARGETS): % : %.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
