SHELL   = /bin/sh
prefix  = /usr/local

.PHONY: all clean
all clean:
	@$(MAKE) -C src/ $@

.PHONY: distclean
distclean: clean

.PHONY: install uninstall
install uninstall:
	$(eval dd := $(shell test -z "$(DESTDIR)" || realpath -m "$(DESTDIR)"))
	@$(MAKE) -C src/ $@ DESTDIR=$(dd) prefix=$(prefix)
