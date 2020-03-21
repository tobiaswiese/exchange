SHELL   = /bin/sh

.PHONY: all clean

all:
	@$(MAKE) -C src/

clean:
	@$(MAKE) -C src/ $@
