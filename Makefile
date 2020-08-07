SHELL = /bin/sh
prefix = /usr/local

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

INSTALL	= install

CFLAGS += -Wall -DVERSION="\"$(VERSION)\"" -DBUILD_DATE="\"$(BUILD_DATE)\""
LDFLAGS +=

TARGETS := exchange
MAINS := $(addsuffix .o, $(TARGETS))
OBJ := $(MAINS)

MAN1 := exchange.1
MAN1_GZ := $(addsuffix .gz, $(MAN1))

.PHONY: all
all: $(TARGETS) $(MAN1_GZ)

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGETS) $(MAN1_GZ)

.PHONY: distclean
distclean: clean

.PHONY: install
install: $(TARGETS) $(MAN1_GZ)
	$(INSTALL) -Dt "$(DESTDIR)$(prefix)/bin" $(TARGETS)
	$(INSTALL) -Dt "$(DESTDIR)$(prefix)/share/man/man1" $(MAN1_GZ)

.PHONY: uninstall
uninstall:
	cd $(DESTDIR)$(prefix)/bin && rm -f $(TARGETS)
	cd $(DESTDIR)$(prefix)/share/man/man1 && rm -f $(MAN1_GZ)


$(TARGETS): % : %.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(MAN1_GZ): %.gz : %
	gzip -9 -k -f $^
