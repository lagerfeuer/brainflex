MFLAGS := --no-print-directory

all:
	$(MAKE) $(MFLAGS) -C src/

debug:
	$(MAKE) $(MFLAGS) -C src/ debug
.PHONY: debug

clean:
	rm -rf brainflex
.PHONY: clean
