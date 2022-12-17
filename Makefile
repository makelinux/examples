all:
	$(MAKE) -C cpp
	$(MAKE) -C c
	$(MAKE) -C js

check:
	$(MAKE) $@ -C cpp
	$(MAKE) $@ -C c
