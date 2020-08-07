VERSION = $(shell git describe --dirty --always)
DATE_FMT = +%b %d %Y %H:%M:%S UTC

ifdef SOURCE_DATE_EPOCH
        BUILD_DATE ?= $(shell \
                date -u -d "@$(SOURCE_DATE_EPOCH)" "$(DATE_FMT)" 2>/dev/null \
                || date -u -r "@$(SOURCE_DATE_EPOCH)" "$(DATE_FMT)" 2>/dev/null \
                || date -u "$(DATE_FMT)")
else
        BUILD_DATE ?= $(shell date -u "$(DATE_FMT)")
endif

INSTALL = install

CFLAGS += -Wall -DVERSION="\"$(VERSION)\"" -DBUILD_DATE="\"$(BUILD_DATE)\""
LDFLAGS +=

TARGETS := exchange
MAINS := $(addsuffix .o, $(TARGETS))
OBJ := $(MAINS)

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
